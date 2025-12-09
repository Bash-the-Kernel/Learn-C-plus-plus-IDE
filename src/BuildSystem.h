#ifndef BUILDSYSTEM_H
#define BUILDSYSTEM_H

#include <QObject>
#include <QProcess>
#include <QString>
#include <memory>

class BuildSystem : public QObject {
    Q_OBJECT

public:
    explicit BuildSystem(QObject *parent = nullptr);
    void build(const QString &sourceFile);
    QString parseFriendlyError(const QString &error);

signals:
    void outputReceived(const QString &output, bool isError);

private:
    std::unique_ptr<QProcess> process;
    QString getOutputPath(const QString &sourceFile);
};

#endif
