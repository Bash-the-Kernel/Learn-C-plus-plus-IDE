#ifndef LESSONSPANEL_H
#define LESSONSPANEL_H

#include <QWidget>
#include <QListWidget>
#include <QTextBrowser>
#include <QSplitter>
#include <QPushButton>

class LessonsPanel : public QWidget {
    Q_OBJECT

public:
    explicit LessonsPanel(QWidget *parent = nullptr);

signals:
    void loadCodeExample(const QString &code);

private slots:
    void onLessonSelected(QListWidgetItem *item);
    void onLoadExample();

private:
    QListWidget *lessonsList;
    QTextBrowser *lessonViewer;
    QPushButton *loadExampleBtn;
    QString currentExampleCode;
    
    void setupLessons();
    QString getLessonContent(const QString &lessonName);
};

#endif
