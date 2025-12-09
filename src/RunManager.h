#ifndef RUNMANAGER_H
#define RUNMANAGER_H

#include <QObject>
#include <QProcess>
#include <memory>

class RunManager : public QObject {
    Q_OBJECT

public:
    explicit RunManager(QObject *parent = nullptr);
    void run(const QString &sourceFile);

signals:
    void outputReceived(const QString &output);

private:
    std::unique_ptr<QProcess> process;
    QString getExecutablePath(const QString &sourceFile);
};

#endif
