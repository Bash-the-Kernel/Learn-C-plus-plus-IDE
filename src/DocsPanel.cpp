#include "DocsPanel.h"
#include <QDesktopServices>
#include <QUrl>

DocsPanel::DocsPanel(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    docsList = new QListWidget(this);
    layout->addWidget(docsList);
    
    setupDocsList();
    
    connect(docsList, &QListWidget::itemClicked, this, &DocsPanel::onItemClicked);
}

void DocsPanel::setupDocsList() {
    QListWidgetItem *item;
    
    item = new QListWidgetItem("C++ Reference Home");
    item->setData(Qt::UserRole, "https://en.cppreference.com/w/cpp");
    docsList->addItem(item);
    
    item = new QListWidgetItem("Input/Output Library");
    item->setData(Qt::UserRole, "https://en.cppreference.com/w/cpp/io");
    docsList->addItem(item);
    
    item = new QListWidgetItem("Containers (vector, map, etc.)");
    item->setData(Qt::UserRole, "https://en.cppreference.com/w/cpp/container");
    docsList->addItem(item);
    
    item = new QListWidgetItem("Algorithms");
    item->setData(Qt::UserRole, "https://en.cppreference.com/w/cpp/algorithm");
    docsList->addItem(item);
    
    item = new QListWidgetItem("Strings");
    item->setData(Qt::UserRole, "https://en.cppreference.com/w/cpp/string");
    docsList->addItem(item);
    
    item = new QListWidgetItem("Memory Management");
    item->setData(Qt::UserRole, "https://en.cppreference.com/w/cpp/memory");
    docsList->addItem(item);
    
    item = new QListWidgetItem("Classes");
    item->setData(Qt::UserRole, "https://en.cppreference.com/w/cpp/language/classes");
    docsList->addItem(item);
    
    item = new QListWidgetItem("Functions");
    item->setData(Qt::UserRole, "https://en.cppreference.com/w/cpp/language/functions");
    docsList->addItem(item);
}

void DocsPanel::onItemClicked(QListWidgetItem *item) {
    QString url = item->data(Qt::UserRole).toString();
    QDesktopServices::openUrl(QUrl(url));
}
