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
    // Beginner Challenges (1-10)
    challengesList->addItem("Challenge 1: Sum Two Numbers [Beginner]");
    challengesList->addItem("Challenge 2: Even or Odd [Beginner]");
    challengesList->addItem("Challenge 3: Temperature Converter [Beginner]");
    challengesList->addItem("Challenge 4: Grade Calculator [Beginner]");
    challengesList->addItem("Challenge 5: Factorial Calculator [Beginner]");
    challengesList->addItem("Challenge 6: Number Guessing Game [Beginner]");
    challengesList->addItem("Challenge 7: Multiplication Table [Beginner]");
    challengesList->addItem("Challenge 8: Simple Calculator [Beginner]");
    challengesList->addItem("Challenge 9: Leap Year Checker [Beginner]");
    challengesList->addItem("Challenge 10: Prime Number Checker [Beginner]");
    
    // Intermediate Challenges (11-20)
    challengesList->addItem("Challenge 11: Palindrome Checker [Intermediate]");
    challengesList->addItem("Challenge 12: Word Counter [Intermediate]");
    challengesList->addItem("Challenge 13: Array Statistics [Intermediate]");
    challengesList->addItem("Challenge 14: String Reverser [Intermediate]");
    challengesList->addItem("Challenge 15: Fibonacci Sequence [Intermediate]");
    challengesList->addItem("Challenge 16: Password Validator [Intermediate]");
    challengesList->addItem("Challenge 17: Text Analyzer [Intermediate]");
    challengesList->addItem("Challenge 18: Number Pattern [Intermediate]");
    challengesList->addItem("Challenge 19: Matrix Operations [Intermediate]");
    challengesList->addItem("Challenge 20: Banking System [Intermediate]");
    
    // Advanced Challenges (21-30)
    challengesList->addItem("Challenge 21: Student Management [Advanced]");
    challengesList->addItem("Challenge 22: Inventory System [Advanced]");
    challengesList->addItem("Challenge 23: Sorting Algorithms [Advanced]");
    challengesList->addItem("Challenge 24: Binary Search [Advanced]");
    challengesList->addItem("Challenge 25: Linked List [Advanced]");
    challengesList->addItem("Challenge 26: Stack Implementation [Advanced]");
    challengesList->addItem("Challenge 27: Queue Implementation [Advanced]");
    challengesList->addItem("Challenge 28: File Processing [Advanced]");
    challengesList->addItem("Challenge 29: Game Character System [Advanced]");
    challengesList->addItem("Challenge 30: Mini Text Editor [Advanced]");
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
    // Beginner Challenges
    if (challengeName.contains("Challenge 1:")) {
        currentChallengeCode = R"(#include <iostream>

int main() {
    // TODO: Read two numbers from user and display their sum
    int num1, num2;
    
    // Your code here
    
    return 0;
})";
        currentHint = "Use std::cin to read two integers, add them with +, then use std::cout to display the result.";
        return "<h2>Challenge 1: Sum Two Numbers [Beginner]</h2>"
               "<p><b>Difficulty:</b> ⭐ Beginner</p>"
               "<p><b>Concepts:</b> Variables, Input/Output, Arithmetic</p>"
               "<p><b>Task:</b> Write a program that reads two integers and prints their sum.</p>"
               "<p><b>Example:</b></p>"
               "<pre>Enter first number: 15\nEnter second number: 25\nSum: 40</pre>"
               "<p><b>Learning Goals:</b> Basic I/O operations and arithmetic</p>";
    }
    else if (challengeName.contains("Challenge 2:")) {
        currentChallengeCode = R"(#include <iostream>

int main() {
    // TODO: Check if a number is even or odd
    int number;
    
    std::cout << "Enter a number: ";
    // Your code here
    
    return 0;
})";
        currentHint = "Use the modulo operator (%). If number % 2 == 0, it's even, otherwise it's odd.";
        return "<h2>Challenge 2: Even or Odd [Beginner]</h2>"
               "<p><b>Difficulty:</b> ⭐ Beginner</p>"
               "<p><b>Concepts:</b> Conditionals, Modulo operator</p>"
               "<p><b>Task:</b> Determine if a number is even or odd.</p>"
               "<p><b>Example:</b></p>"
               "<pre>Enter a number: 7\n7 is odd</pre>"
               "<p><b>Hint:</b> Even numbers are divisible by 2 (remainder = 0)</p>";
    }
    else if (challengeName.contains("Challenge 3:")) {
        currentChallengeCode = R"(#include <iostream>

int main() {
    // TODO: Convert Celsius to Fahrenheit
    // Formula: F = (C * 9/5) + 32
    double celsius;
    
    std::cout << "Enter temperature in Celsius: ";
    // Your code here
    
    return 0;
})";
        currentHint = "Read Celsius temperature, apply formula F = (C * 9.0/5.0) + 32, display result. Use double for precision.";
        return "<h2>Challenge 3: Temperature Converter [Beginner]</h2>"
               "<p><b>Difficulty:</b> ⭐ Beginner</p>"
               "<p><b>Concepts:</b> Arithmetic, Data types, Formulas</p>"
               "<p><b>Task:</b> Convert Celsius to Fahrenheit using the formula F = (C × 9/5) + 32</p>"
               "<p><b>Example:</b></p>"
               "<pre>Enter temperature in Celsius: 25\n25°C = 77°F</pre>"
               "<p><b>Real-world:</b> Weather apps, cooking, science</p>";
    }
    else if (challengeName.contains("Challenge 4:")) {
        currentChallengeCode = R"(#include <iostream>

int main() {
    // TODO: Calculate average of 5 test scores and assign letter grade
    double score1, score2, score3, score4, score5;
    
    std::cout << "Enter 5 test scores:\n";
    // Your code here
    // Calculate average
    // Assign grade: A(90+), B(80-89), C(70-79), D(60-69), F(<60)
    
    return 0;
})";
        currentHint = "Read 5 scores, calculate average = (sum of all scores) / 5, then use if-else statements for letter grades.";
        return "<h2>Challenge 4: Grade Calculator [Beginner]</h2>"
               "<p><b>Difficulty:</b> ⭐ Beginner</p>"
               "<p><b>Concepts:</b> Loops/Multiple inputs, Arithmetic, Conditionals</p>"
               "<p><b>Task:</b> Calculate average of 5 test scores and assign letter grade</p>"
               "<p><b>Grading Scale:</b> A(90+), B(80-89), C(70-79), D(60-69), F(<60)</p>"
               "<p><b>Example:</b></p>"
               "<pre>Scores: 85, 92, 78, 95, 88\nAverage: 87.6\nGrade: B</pre>";
    }
    else if (challengeName.contains("Challenge 5:")) {
        currentChallengeCode = R"(#include <iostream>

int main() {
    // TODO: Calculate factorial of a number
    // Factorial: n! = n × (n-1) × (n-2) × ... × 1
    // Example: 5! = 5 × 4 × 3 × 2 × 1 = 120
    int number;
    
    std::cout << "Enter a number: ";
    // Your code here
    
    return 0;
})";
        currentHint = "Use a for loop from 1 to n, multiply all numbers together. Start with result = 1, then result *= i for each i.";
        return "<h2>Challenge 5: Factorial Calculator [Beginner]</h2>"
               "<p><b>Difficulty:</b> ⭐⭐ Beginner+</p>"
               "<p><b>Concepts:</b> Loops, Multiplication, Mathematical concepts</p>"
               "<p><b>Task:</b> Calculate factorial (n!) of a number</p>"
               "<p><b>Formula:</b> n! = n × (n-1) × (n-2) × ... × 1</p>"
               "<p><b>Example:</b> 5! = 5 × 4 × 3 × 2 × 1 = 120</p>"
               "<p><b>Special case:</b> 0! = 1 by definition</p>";
    }
    else if (challengeName.contains("Challenge 6:")) {
        currentChallengeCode = R"(#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // TODO: Number guessing game
    // Generate random number 1-100
    // Let user guess with hints (too high/low)
    
    srand(time(0));  // Seed random number generator
    // int secretNumber = rand() % 100 + 1;  // Random 1-100
    
    // Your code here
    
    return 0;
})";
        currentHint = "Use while loop for guessing. Compare guess to secret number, give 'too high' or 'too low' hints. Break when correct.";
        return "<h2>Challenge 6: Number Guessing Game [Beginner]</h2>"
               "<p><b>Difficulty:</b> ⭐⭐ Beginner+</p>"
               "<p><b>Concepts:</b> Loops, Random numbers, Conditionals, Game logic</p>"
               "<p><b>Task:</b> Create a guessing game where user guesses a random number 1-100</p>"
               "<p><b>Features:</b></p>"
               "<ul><li>Generate random number</li><li>Give 'too high' or 'too low' hints</li>"
               "<li>Count number of guesses</li><li>Congratulate on correct guess</li></ul>"
               "<p><b>Fun factor:</b> Your first interactive game!</p>";
    }
    else if (challengeName.contains("Challenge 11:")) {
        currentChallengeCode = R"(#include <iostream>
#include <string>

int main() {
    // TODO: Check if a word/phrase is a palindrome
    // Palindrome reads the same forwards and backwards
    // Examples: "racecar", "A man a plan a canal Panama"
    
    std::string text;
    std::cout << "Enter text to check: ";
    // Your code here
    
    return 0;
})";
        currentHint = "Convert to lowercase, remove spaces. Compare characters from start and end moving inward. Use two pointers or reverse string.";
        return "<h2>Challenge 11: Palindrome Checker [Intermediate]</h2>"
               "<p><b>Difficulty:</b> ⭐⭐⭐ Intermediate</p>"
               "<p><b>Concepts:</b> Strings, Loops, Character manipulation</p>"
               "<p><b>Task:</b> Check if text reads the same forwards and backwards</p>"
               "<p><b>Examples:</b> 'racecar', 'A man a plan a canal Panama'</p>"
               "<p><b>Challenges:</b> Handle spaces, punctuation, case sensitivity</p>"
               "<p><b>Algorithm:</b> Two-pointer technique or string reversal</p>";
    }
    else if (challengeName.contains("Challenge 21:")) {
        currentChallengeCode = R"(#include <iostream>
#include <string>
#include <vector>

// TODO: Create a Student class and management system
class Student {
private:
    // Add member variables: name, id, grades vector
    
public:
    // Add constructor, methods for adding grades, calculating average
};

int main() {
    // TODO: Create student management system
    // Features: Add students, add grades, display info, calculate class average
    
    return 0;
})";
        currentHint = "Create Student class with name, ID, grades vector. Add methods: addGrade(), getAverage(), display(). Use vector<Student> for multiple students.";
        return "<h2>Challenge 21: Student Management System [Advanced]</h2>"
               "<p><b>Difficulty:</b> ⭐⭐⭐⭐ Advanced</p>"
               "<p><b>Concepts:</b> Classes, Objects, Vectors, Encapsulation</p>"
               "<p><b>Task:</b> Build a complete student management system</p>"
               "<p><b>Features:</b></p>"
               "<ul><li>Student class with name, ID, grades</li>"
               "<li>Add/remove students</li><li>Add grades to students</li>"
               "<li>Calculate individual and class averages</li><li>Display student information</li></ul>"
               "<p><b>Real-world:</b> School management systems, gradebooks</p>";
    }
    
    return "<p>Select a challenge to view details. 30 challenges available from Beginner to Advanced!</p>";
}