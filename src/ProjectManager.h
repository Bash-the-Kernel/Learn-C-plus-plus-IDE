#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QObject>
#include <QString>

class ProjectManager : public QObject {
    Q_OBJECT

public:
    explicit ProjectManager(QObject *parent = nullptr);
    
    void setProjectPath(const QString &path);
    QString projectPath() const { return m_projectPath; }
    
    void createProject(const QString &path, const QString &templateName);

private:
    QString m_projectPath;
    QString getTemplateCode(const QString &templateName);
};

#endif
