#include "BuildSystem.h"
#include <QFileInfo>
#include <QDir>

BuildSystem::BuildSystem(QObject *parent) : QObject(parent) {
    process = std::make_unique<QProcess>(this);
}

void BuildSystem::build(const QString &sourceFile) {
    QFileInfo fileInfo(sourceFile);
    QString outputPath = getOutputPath(sourceFile);
    
    QStringList args;
    args << sourceFile << "-o" << outputPath << "-std=c++20" << "-Wall";
    
    QString compiler = "g++";
    if (QProcess::execute("clang++", QStringList() << "--version") == 0) {
        compiler = "clang++";
    }
    
    process->start(compiler, args);
    process->waitForFinished();
    
    QString output = process->readAllStandardOutput();
    QString error = process->readAllStandardError();
    
    if (!output.isEmpty()) {
        emit outputReceived(output, false);
    }
    
    if (!error.isEmpty()) {
        emit outputReceived(error, true);
    }
    
    if (process->exitCode() == 0) {
        emit outputReceived("Build successful: " + outputPath, false);
        // Check if file actually exists
        QFileInfo checkFile(outputPath);
        if (!checkFile.exists()) {
            emit outputReceived("Warning: Expected output file not found at: " + outputPath, true);
        }
    } else {
        emit outputReceived("Build failed with exit code: " + QString::number(process->exitCode()), true);
    }
}

QString BuildSystem::getOutputPath(const QString &sourceFile) {
    QFileInfo fileInfo(sourceFile);
    QString baseName = fileInfo.completeBaseName();
    QString dir = fileInfo.absolutePath();
    
#ifdef Q_OS_WIN
    return dir + "/" + baseName + ".exe";
#else
    return dir + "/" + baseName;
#endif
}

QString BuildSystem::parseFriendlyError(const QString &error) {
    QString friendly = error;
    
    if (error.contains("undefined reference")) {
        friendly += "\n💡 Friendly hint: You have an undefined reference. Did you forget to define a function or link a library?";
    }
    else if (error.contains("expected ';'")) {
        friendly += "\n💡 Friendly hint: Missing semicolon. Check the end of the previous line.";
    }
    else if (error.contains("was not declared")) {
        friendly += "\n💡 Friendly hint: Variable or function not declared. Did you forget to include a header or declare it?";
    }
    else if (error.contains("no matching function")) {
        friendly += "\n💡 Friendly hint: Function call doesn't match any definition. Check your parameters.";
    }
    else if (error.contains("expected ')'") || error.contains("expected '}'")) {
        friendly += "\n💡 Friendly hint: Missing closing bracket. Check your parentheses or braces.";
    }
    else if (error.contains("invalid conversion")) {
        friendly += "\n💡 Friendly hint: Type mismatch. You're trying to assign incompatible types.";
    }
    
    return friendly;
}
