#include "ChallengesPanel.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QMessageBox>

ChallengesPanel::ChallengesPanel(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    QSplitter *splitter = new QSplitter(Qt::Vertical, this);
    
    challengesList = new QListWidget(this);
    challengeViewer = new QTextBrowser(this);
    
    splitter->addWidget(challengesList);
    splitter->addWidget(challengeViewer);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 3);
    
    mainLayout->addWidget(splitter);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    loadChallengeBtn = new QPushButton("Load Challenge", this);
    showHintBtn = new QPushButton("Show Hint", this);
    
    buttonLayout->addWidget(loadChallengeBtn);
    buttonLayout->addWidget(showHintBtn);
    mainLayout->addLayout(buttonLayout);
    
    setupChallenges();
    
    connect(challengesList, &QListWidget::itemClicked, this, &ChallengesPanel::onChallengeSelected);
    connect(loadChallengeBtn, &QPushButton::clicked, this, &ChallengesPanel::onLoadChallenge);
    connect(showHintBtn, &QPushButton::clicked, this, &ChallengesPanel::onShowHint);
}

void ChallengesPanel::setupChallenges() {
    challengesList->addItem("Challenge 1: Sum Two Numbers");
    challengesList->addItem("Challenge 2: Even or Odd");
    challengesList->addItem("Challenge 3: Factorial");
    challengesList->addItem("Challenge 4: Temperature Converter");
    challengesList->addItem("Challenge 5: Grade Calculator");
}

void ChallengesPanel::onChallengeSelected(QListWidgetItem *item) {
    QString challengeName = item->text();
    QString content = getChallengeContent(challengeName);
    challengeViewer->setHtml(content);
}

void ChallengesPanel::onLoadChallenge() {
    if (!currentChallengeCode.isEmpty()) {
        emit loadChallenge(currentChallengeCode);
    }
}

void ChallengesPanel::onShowHint() {
    if (!currentHint.isEmpty()) {
        QMessageBox::information(this, "Hint", currentHint);
    }
}

QString ChallengesPanel::getChallengeContent(const QString &challengeName) {
    if (challengeName.contains("Sum Two Numbers")) {
        currentChallengeCode = R"(#include <iostream>

int main() {
    // TODO: Read two numbers and print their sum
    
    return 0;
})";
        currentHint = "Use std::cin to read two integers, add them, and use std::cout to display the result.";
        return "<h2>Challenge 1: Sum Two Numbers</h2>"
               "<p><b>Task:</b> Write a program that reads two integers and prints their sum.</p>"
               "<p><b>Expected Output:</b> If input is 5 and 3, output should be 8</p>";
    }
    else if (challengeName.contains("Even or Odd")) {
        currentChallengeCode = R"(#include <iostream>

int main() {
    // TODO: Check if a number is even or odd
    
    return 0;
})";
        currentHint = "Use the modulo operator (%) to check if number % 2 == 0";
        return "<h2>Challenge 2: Even or Odd</h2>"
               "<p><b>Task:</b> Read a number and determine if it's even or odd.</p>";
    }
    else if (challengeName.contains("Factorial")) {
        currentChallengeCode = R"(#include <iostream>

int main() {
    // TODO: Calculate factorial of a number
    
    return 0;
})";
        currentHint = "Use a for loop to multiply numbers from 1 to n.";
        return "<h2>Challenge 3: Factorial</h2>"
               "<p><b>Task:</b> Calculate the factorial of a number.</p>"
               "<p><b>Example:</b> 5! = 5 × 4 × 3 × 2 × 1 = 120</p>";
    }
    else if (challengeName.contains("Temperature")) {
        currentChallengeCode = R"(#include <iostream>

int main() {
    // TODO: Convert Celsius to Fahrenheit
    // Formula: F = (C * 9/5) + 32
    
    return 0;
})";
        currentHint = "Read Celsius temperature, apply formula F = (C * 9/5) + 32, then display result.";
        return "<h2>Challenge 4: Temperature Converter</h2>"
               "<p><b>Task:</b> Convert Celsius to Fahrenheit</p>"
               "<p><b>Formula:</b> F = (C × 9/5) + 32</p>";
    }
    else if (challengeName.contains("Grade")) {
        currentChallengeCode = R"(#include <iostream>

int main() {
    // TODO: Calculate average of 5 test scores
    // Display the average and letter grade
    
    return 0;
})";
        currentHint = "Read 5 scores, add them up, divide by 5 for average. Use if-else for letter grades.";
        return "<h2>Challenge 5: Grade Calculator</h2>"
               "<p><b>Task:</b> Calculate average of 5 test scores and assign letter grade</p>"
               "<p><b>Grading:</b> A(90+), B(80-89), C(70-79), D(60-69), F(below 60)</p>";
    }
    
    return "<p>Select a challenge to view details.</p>";
}