#ifndef DOCSPANEL_H
#define DOCSPANEL_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>

class DocsPanel : public QWidget {
    Q_OBJECT

public:
    explicit DocsPanel(QWidget *parent = nullptr);

private slots:
    void onItemClicked(QListWidgetItem *item);

private:
    QListWidget *docsList;
    void setupDocsList();
};

#endif
