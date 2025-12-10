#include "RunManager.h"
#include <QFileInfo>

RunManager::RunManager(QObject *parent) : QObject(parent) {
    process = std::make_unique<QProcess>(this);
}

void RunManager::run(const QString &sourceFile) {
    QString execPath = getExecutablePath(sourceFile);
    
    QFileInfo fileInfo(execPath);
    if (!fileInfo.exists()) {
        emit outputReceived("Error: Executable not found. Please build first.");
        return;
    }
    
    process->start(execPath);
    process->waitForFinished();
    
    QString output = process->readAllStandardOutput();
    QString error = process->readAllStandardError();
    
    if (!output.isEmpty()) {
        emit outputReceived(output);
    }
    
    if (!error.isEmpty()) {
        emit outputReceived("Error: " + error);
    }
    
    if (process->exitCode() != 0) {
        emit outputReceived("Program exited with code: " + QString::number(process->exitCode()));
    }
}

QString RunManager::getExecutablePath(const QString &sourceFile) {
    QFileInfo fileInfo(sourceFile);
    QString baseName = fileInfo.completeBaseName();
    QString dir = fileInfo.absolutePath();
    
#ifdef Q_OS_WIN
    QString exePath = dir + "/" + baseName + ".exe";
#else
    QString exePath = dir + "/" + baseName;
#endif
    
    // Debug: Check if file exists
    QFileInfo exeInfo(exePath);
    if (!exeInfo.exists()) {
        // Try alternative paths
        QString altPath = dir + "/" + baseName;
        if (QFileInfo(altPath).exists()) {
            return altPath;
        }
    }
    
    return exePath;
}
