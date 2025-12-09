#include "LessonsPanel.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QTextStream>

LessonsPanel::LessonsPanel(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    QSplitter *splitter = new QSplitter(Qt::Vertical, this);
    
    lessonsList = new QListWidget(this);
    lessonViewer = new QTextBrowser(this);
    
    splitter->addWidget(lessonsList);
    splitter->addWidget(lessonViewer);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 3);
    
    mainLayout->addWidget(splitter);
    
    loadExampleBtn = new QPushButton("Load Code Example", this);
    mainLayout->addWidget(loadExampleBtn);
    
    setupLessons();
    
    connect(lessonsList, &QListWidget::itemClicked, this, &LessonsPanel::onLessonSelected);
    connect(loadExampleBtn, &QPushButton::clicked, this, &LessonsPanel::onLoadExample);
}

void LessonsPanel::setupLessons() {
    lessonsList->addItem("1. Hello World");
    lessonsList->addItem("2. Variables and Types");
    lessonsList->addItem("3. Input and Output");
    lessonsList->addItem("4. Conditionals");
    lessonsList->addItem("5. Loops");
    lessonsList->addItem("6. Functions");
    lessonsList->addItem("7. Arrays");
    lessonsList->addItem("8. Vectors");
    lessonsList->addItem("9. Classes");
    lessonsList->addItem("10. Pointers");
}

void LessonsPanel::onLessonSelected(QListWidgetItem *item) {
    QString lessonName = item->text();
    QString content = getLessonContent(lessonName);
    lessonViewer->setHtml(content);
}

void LessonsPanel::onLoadExample() {
    if (!currentExampleCode.isEmpty()) {
        emit loadCodeExample(currentExampleCode);
    }
}
QString LessonsPanel::getLessonContent(const QString &lessonName) {
    if (lessonName.contains("Hello World")) {
        currentExampleCode = R"(#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
})";
        return "<h2>Lesson 1: Hello World</h2>"
               "<p>Every C++ program starts with a main function.</p>"
               "<p><b>Key concepts:</b></p>"
               "<ul><li>#include directive</li><li>iostream library</li><li>std::cout</li></ul>";
    }
    else if (lessonName.contains("Variables")) {
        currentExampleCode = R"(#include <iostream>

int main() {
    int age = 25;
    double price = 19.99;
    char grade = 'A';
    bool isStudent = true;
    
    std::cout << "Age: " << age << std::endl;
    return 0;
})";
        return "<h2>Lesson 2: Variables and Types</h2>"
               "<p>Variables store data. C++ has several basic types:</p>"
               "<ul><li>int - integers</li><li>double - decimals</li><li>char - characters</li><li>bool - true/false</li></ul>";
    }
    else if (lessonName.contains("Input")) {
        currentExampleCode = R"(#include <iostream>

int main() {
    int number;
    std::cout << "Enter a number: ";
    std::cin >> number;
    std::cout << "You entered: " << number << std::endl;
    return 0;
})";
        return "<h2>Lesson 3: Input and Output</h2>"
               "<p>Use std::cin to read input and std::cout to display output.</p>";
    }
    
    return "<p>Select a lesson to view content.</p>";
}
