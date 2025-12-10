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
    // Basic Challenges (1-10)
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
    
    // Open-Ended Projects
    challengesList->addItem("Project 1: Personal Budget Tracker [Project]");
    challengesList->addItem("Project 2: Text-Based Adventure Game [Project]");
    challengesList->addItem("Project 3: Library Management System [Project]");
    challengesList->addItem("Project 4: Weather Data Analyzer [Project]");
    challengesList->addItem("Project 5: Simple Banking System [Project]");
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
    // Challenge 7-10 (add skeleton code for remaining basic challenges)
    else if (challengeName.contains("Challenge 7:")) {
        currentChallengeCode = R"(#include <iostream>

int main() {
    // TODO: Display multiplication table for a given number
    int number;
    
    std::cout << "Enter a number: ";
    // Your code here - use a for loop to display table
    
    return 0;
})";
        currentHint = "Use a for loop from 1 to 10, multiply the number by each value and display the result.";
        return "<h2>Challenge 7: Multiplication Table [Beginner]</h2>"
               "<p><b>Task:</b> Display multiplication table for a given number (1-10)</p>";
    }
    else if (challengeName.contains("Challenge 8:")) {
        currentChallengeCode = R"(#include <iostream>

int main() {
    // TODO: Create a simple calculator (+, -, *, /)
    double num1, num2;
    char operation;
    
    std::cout << "Enter first number: ";
    // Your code here
    
    return 0;
})";
        currentHint = "Read two numbers and an operator, use if-else or switch statement to perform the operation.";
        return "<h2>Challenge 8: Simple Calculator [Beginner]</h2>"
               "<p><b>Task:</b> Create calculator for basic operations (+, -, *, /)</p>";
    }
    else if (challengeName.contains("Challenge 9:")) {
        currentChallengeCode = R"(#include <iostream>

int main() {
    // TODO: Check if a year is a leap year
    // Rules: Divisible by 4, but not by 100, unless also divisible by 400
    int year;
    
    std::cout << "Enter a year: ";
    // Your code here
    
    return 0;
})";
        currentHint = "A year is leap if: (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)";
        return "<h2>Challenge 9: Leap Year Checker [Beginner]</h2>"
               "<p><b>Task:</b> Determine if a year is a leap year using the leap year rules</p>";
    }
    else if (challengeName.contains("Challenge 10:")) {
        currentChallengeCode = R"(#include <iostream>

int main() {
    // TODO: Check if a number is prime
    // Prime: only divisible by 1 and itself
    int number;
    
    std::cout << "Enter a number: ";
    // Your code here
    
    return 0;
})";
        currentHint = "Check divisibility from 2 to sqrt(number). If any divides evenly, it's not prime.";
        return "<h2>Challenge 10: Prime Number Checker [Beginner]</h2>"
               "<p><b>Task:</b> Determine if a number is prime (only divisible by 1 and itself)</p>";
    }
    
    // Open-Ended Projects
    else if (challengeName.contains("Project 1:")) {
        currentChallengeCode = R"(#include <iostream>
#include <vector>
#include <string>

// TODO: Create a Personal Budget Tracker
// Features to implement:
// - Add income/expense entries
// - Categorize transactions
// - Calculate monthly totals
// - Show spending by category
// - Display budget summary

struct Transaction {
    // Add: amount, category, description, date
};

int main() {
    // Your creative implementation here!
    // This is an open-ended project - be creative!
    
    return 0;
})";
        currentHint = "Start with a Transaction struct, use vectors to store data, create a menu system for user interaction.";
        return "<h2>Project 1: Personal Budget Tracker [Project]</h2>"
               "<p><b>Type:</b> 🚀 Open-Ended Project</p>"
               "<p><b>Goal:</b> Build a complete budget tracking application</p>"
               "<p><b>Core Features:</b></p>"
               "<ul><li>Add income and expense entries</li>"
               "<li>Categorize transactions (food, transport, entertainment, etc.)</li>"
               "<li>Calculate monthly totals and balances</li>"
               "<li>Show spending breakdown by category</li>"
               "<li>Display budget summary and warnings</li></ul>"
               "<p><b>Advanced Features:</b> Save/load data, budget limits, spending trends</p>"
               "<p><b>Real-world Skills:</b> Data structures, file I/O, user interfaces</p>";
    }
    else if (challengeName.contains("Project 2:")) {
        currentChallengeCode = R"(#include <iostream>
#include <string>
#include <map>

// TODO: Create a Text-Based Adventure Game
// Features to implement:
// - Multiple rooms/locations
// - Player inventory system
// - Interactive story with choices
// - Combat or puzzle mechanics
// - Win/lose conditions

class Player {
    // Add: health, inventory, location, etc.
};

class Room {
    // Add: description, exits, items, etc.
};

int main() {
    // Your creative game implementation here!
    // Tell an engaging story with player choices
    
    return 0;
})";
        currentHint = "Design your story first, then create classes for Player and Room. Use maps for room connections and inventory.";
        return "<h2>Project 2: Text-Based Adventure Game [Project]</h2>"
               "<p><b>Type:</b> 🎮 Open-Ended Project</p>"
               "<p><b>Goal:</b> Create an interactive story-driven game</p>"
               "<p><b>Core Features:</b></p>"
               "<ul><li>Multiple connected rooms/locations</li>"
               "<li>Player character with inventory</li>"
               "<li>Interactive story with meaningful choices</li>"
               "<li>Items to collect and use</li>"
               "<li>Clear win/lose conditions</li></ul>"
               "<p><b>Creative Elements:</b> Unique story, puzzles, character interactions</p>"
               "<p><b>Skills:</b> Game design, state management, storytelling</p>";
    }
    else if (challengeName.contains("Project 3:")) {
        currentChallengeCode = R"(#include <iostream>
#include <vector>
#include <string>

// TODO: Create a Library Management System
// Features to implement:
// - Book catalog with search
// - Member registration
// - Check-out/check-in system
// - Due date tracking
// - Fine calculation

class Book {
    // Add: title, author, ISBN, availability, etc.
};

class Member {
    // Add: name, ID, borrowed books, fines, etc.
};

class Library {
    // Add: books collection, members, management methods
};

int main() {
    // Your library system implementation here!
    
    return 0;
})";
        currentHint = "Start with Book and Member classes, create a Library class to manage everything. Use vectors for collections.";
        return "<h2>Project 3: Library Management System [Project]</h2>"
               "<p><b>Type:</b> 📚 Open-Ended Project</p>"
               "<p><b>Goal:</b> Build a complete library management application</p>"
               "<p><b>Core Features:</b></p>"
               "<ul><li>Book catalog with search functionality</li>"
               "<li>Member registration and profiles</li>"
               "<li>Check-out and check-in system</li>"
               "<li>Due date tracking and notifications</li>"
               "<li>Fine calculation for overdue books</li></ul>"
               "<p><b>Advanced Features:</b> Book reservations, reading history, reports</p>"
               "<p><b>Skills:</b> Database design, business logic, user management</p>";
    }
    else if (challengeName.contains("Project 4:")) {
        currentChallengeCode = R"(#include <iostream>
#include <vector>
#include <string>

// TODO: Create a Weather Data Analyzer
// Features to implement:
// - Store daily weather data
// - Calculate statistics (avg, min, max)
// - Identify weather patterns
// - Generate weather reports
// - Predict trends

struct WeatherData {
    // Add: date, temperature, humidity, precipitation, etc.
};

class WeatherAnalyzer {
    // Add: data storage, analysis methods
};

int main() {
    // Your weather analysis system here!
    
    return 0;
})";
        currentHint = "Create a WeatherData struct, use vectors for time series data, implement statistical functions for analysis.";
        return "<h2>Project 4: Weather Data Analyzer [Project]</h2>"
               "<p><b>Type:</b> 🌤️ Open-Ended Project</p>"
               "<p><b>Goal:</b> Build a weather data analysis system</p>"
               "<p><b>Core Features:</b></p>"
               "<ul><li>Store and manage daily weather data</li>"
               "<li>Calculate statistics (averages, extremes, trends)</li>"
               "<li>Identify weather patterns and anomalies</li>"
               "<li>Generate comprehensive weather reports</li>"
               "<li>Simple trend prediction</li></ul>"
               "<p><b>Data Points:</b> Temperature, humidity, precipitation, wind speed</p>"
               "<p><b>Skills:</b> Data analysis, statistics, scientific computing</p>";
    }
    else if (challengeName.contains("Project 5:")) {
        currentChallengeCode = R"(#include <iostream>
#include <vector>
#include <string>

// TODO: Create a Simple Banking System
// Features to implement:
// - Account creation and management
// - Deposit and withdrawal operations
// - Transfer between accounts
// - Transaction history
// - Interest calculation

class Account {
    // Add: account number, balance, owner, transaction history
};

class Bank {
    // Add: accounts management, operations
};

int main() {
    // Your banking system implementation here!
    
    return 0;
})";
        currentHint = "Design Account class with balance and history, create Bank class to manage multiple accounts and operations.";
        return "<h2>Project 5: Simple Banking System [Project]</h2>"
               "<p><b>Type:</b> 🏦 Open-Ended Project</p>"
               "<p><b>Goal:</b> Build a functional banking system simulation</p>"
               "<p><b>Core Features:</b></p>"
               "<ul><li>Account creation with unique numbers</li>"
               "<li>Secure deposit and withdrawal operations</li>"
               "<li>Money transfer between accounts</li>"
               "<li>Complete transaction history</li>"
               "<li>Interest calculation and application</li></ul>"
               "<p><b>Security:</b> Input validation, balance checks, error handling</p>"
               "<p><b>Skills:</b> Financial systems, security, data integrity</p>";
    }
    
    return "<p>Select a challenge to view details. 10 basic challenges + 5 open-ended projects available!</p>";
}