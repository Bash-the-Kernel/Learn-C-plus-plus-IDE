#ifndef CHALLENGESPANEL_H
#define CHALLENGESPANEL_H

#include <QWidget>
#include <QListWidget>
#include <QTextBrowser>
#include <QPushButton>

class ChallengesPanel : public QWidget {
    Q_OBJECT

public:
    explicit ChallengesPanel(QWidget *parent = nullptr);

signals:
    void loadChallenge(const QString &code);

private slots:
    void onChallengeSelected(QListWidgetItem *item);
    void onLoadChallenge();
    void onShowHint();

private:
    QListWidget *challengesList;
    QTextBrowser *challengeViewer;
    QPushButton *loadChallengeBtn;
    QPushButton *showHintBtn;
    QString currentChallengeCode;
    QString currentHint;
    
    void setupChallenges();
    QString getChallengeContent(const QString &challengeName);
};

#endif
