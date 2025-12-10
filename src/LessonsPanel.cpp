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
    // Phase 1: Fundamentals (1-15)
    lessonsList->addItem("1. Hello World & Compilation");
    lessonsList->addItem("2. Variables & Data Types");
    lessonsList->addItem("3. Constants & Literals");
    lessonsList->addItem("4. Input/Output & Operators");
    lessonsList->addItem("5. Arithmetic & Assignment");
    lessonsList->addItem("6. Conditionals & Comparisons");
    lessonsList->addItem("7. Logical Operators");
    lessonsList->addItem("8. For Loops");
    lessonsList->addItem("9. While & Do-While Loops");
    lessonsList->addItem("10. Functions Basics");
    lessonsList->addItem("11. Function Parameters");
    lessonsList->addItem("12. Return Values");
    lessonsList->addItem("13. Scope & Local Variables");
    lessonsList->addItem("14. Global Variables");
    lessonsList->addItem("15. Arrays Introduction");
    
    // Phase 2: Intermediate (16-30)
    lessonsList->addItem("16. Multidimensional Arrays");
    lessonsList->addItem("17. C-style Strings");
    lessonsList->addItem("18. std::string");
    lessonsList->addItem("19. Debugging Basics");
    lessonsList->addItem("20. Introduction to OOP");
    lessonsList->addItem("21. Classes & Objects");
    lessonsList->addItem("22. Constructors");
    lessonsList->addItem("23. Destructors");
    lessonsList->addItem("24. Member Functions");
    lessonsList->addItem("25. Access Specifiers");
    lessonsList->addItem("26. Encapsulation");
    lessonsList->addItem("27. Getters & Setters");
    lessonsList->addItem("28. Operator Overloading");
    lessonsList->addItem("29. Inheritance Basics");
    lessonsList->addItem("30. Polymorphism");
    
    // Phase 3: Advanced (31-50)
    lessonsList->addItem("31. Virtual Functions");
    lessonsList->addItem("32. Abstract Classes");
    lessonsList->addItem("33. Friend Functions");
    lessonsList->addItem("34. Pointers Introduction");
    lessonsList->addItem("35. Pointer Arithmetic");
    lessonsList->addItem("36. References");
    lessonsList->addItem("37. Dynamic Memory");
    lessonsList->addItem("38. Smart Pointers");
    lessonsList->addItem("39. STL Vector");
    lessonsList->addItem("40. STL Array & Deque");
    lessonsList->addItem("41. STL List & Forward List");
    lessonsList->addItem("42. STL Algorithms");
    lessonsList->addItem("43. Iterators");
    lessonsList->addItem("44. Exception Handling");
    lessonsList->addItem("45. File I/O");
    lessonsList->addItem("46. Streams");
    lessonsList->addItem("47. Templates Basics");
    lessonsList->addItem("48. Template Specialization");
    lessonsList->addItem("49. Lambda Expressions");
    lessonsList->addItem("50. Move Semantics");
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
    // Phase 1: Fundamentals
    if (lessonName.contains("1.")) {
        currentExampleCode = R"(#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
})";
        return "<h2>Lesson 1: Hello World & Compilation</h2>"
               "<p>Every C++ program starts with the <b>main()</b> function.</p>"
               "<p><b>Compilation Process:</b></p>"
               "<ol><li>Preprocessor handles #include directives</li>"
               "<li>Compiler converts source to object code</li>"
               "<li>Linker combines object files into executable</li></ol>"
               "<p><b>Key Components:</b></p>"
               "<ul><li><code>#include &lt;iostream&gt;</code> - Input/output stream library</li>"
               "<li><code>int main()</code> - Entry point, returns integer</li>"
               "<li><code>std::cout</code> - Standard output stream</li>"
               "<li><code>&lt;&lt;</code> - Stream insertion operator</li>"
               "<li><code>std::endl</code> - End line and flush buffer</li></ul>";
    }
    else if (lessonName.contains("2.")) {
        currentExampleCode = R"(#include <iostream>

int main() {
    // Integer types
    int age = 25;
    short year = 2024;
    long population = 8000000000L;
    
    // Floating-point types
    float price = 19.99f;
    double pi = 3.14159265359;
    
    // Character and boolean
    char grade = 'A';
    bool isStudent = true;
    
    std::cout << "Age: " << age << std::endl;
    std::cout << "Price: $" << price << std::endl;
    std::cout << "Grade: " << grade << std::endl;
    std::cout << "Is student: " << isStudent << std::endl;
    
    return 0;
})";
        return "<h2>Lesson 2: Variables & Data Types</h2>"
               "<p>Variables are named storage locations for data.</p>"
               "<p><b>Fundamental Types:</b></p>"
               "<ul><li><b>int</b> - Integers (typically 32-bit)</li>"
               "<li><b>short</b> - Short integers (typically 16-bit)</li>"
               "<li><b>long</b> - Long integers (typically 64-bit)</li>"
               "<li><b>float</b> - Single precision floating-point</li>"
               "<li><b>double</b> - Double precision floating-point</li>"
               "<li><b>char</b> - Single character (8-bit)</li>"
               "<li><b>bool</b> - Boolean (true/false)</li></ul>"
               "<p><b>Declaration Syntax:</b> <code>type variableName = value;</code></p>"
               "<p><b>Naming Rules:</b> Start with letter/underscore, no spaces, case-sensitive</p>";
    }
    else if (lessonName.contains("3.")) {
        currentExampleCode = R"(#include <iostream>

int main() {
    // Constants - cannot be changed after initialization
    const int MAX_STUDENTS = 30;
    const double PI = 3.14159;
    const char GRADE_A = 'A';
    
    // Literals
    int decimal = 42;        // Decimal literal
    int hex = 0x2A;         // Hexadecimal literal
    int octal = 052;        // Octal literal
    int binary = 0b101010;  // Binary literal (C++14)
    
    double scientific = 1.23e4;  // Scientific notation
    
    std::cout << "Max students: " << MAX_STUDENTS << std::endl;
    std::cout << "Pi: " << PI << std::endl;
    std::cout << "Decimal 42 in hex: " << hex << std::endl;
    
    return 0;
})";
        return "<h2>Lesson 3: Constants & Literals</h2>"
               "<p>Constants are values that cannot be modified after initialization.</p>"
               "<p><b>Const Keyword:</b></p>"
               "<ul><li>Must be initialized when declared</li>"
               "<li>Compiler enforces immutability</li>"
               "<li>Convention: ALL_CAPS naming</li></ul>"
               "<p><b>Literal Types:</b></p>"
               "<ul><li><b>Integer:</b> 42, 0x2A (hex), 052 (octal), 0b101010 (binary)</li>"
               "<li><b>Floating:</b> 3.14, 1.23e4 (scientific)</li>"
               "<li><b>Character:</b> 'A', '\\n' (escape sequences)</li>"
               "<li><b>String:</b> \"Hello World\"</li></ul>";
    }
    else if (lessonName.contains("4.")) {
        currentExampleCode = R"(#include <iostream>
#include <string>

int main() {
    std::string name;
    int age;
    double height;
    
    std::cout << "Enter your name: ";
    std::cin >> name;
    
    std::cout << "Enter your age: ";
    std::cin >> age;
    
    std::cout << "Enter your height (meters): ";
    std::cin >> height;
    
    std::cout << "\nHello " << name << "!" << std::endl;
    std::cout << "You are " << age << " years old" << std::endl;
    std::cout << "You are " << height << "m tall" << std::endl;
    
    // Arithmetic operations
    int nextYear = age + 1;
    double heightCm = height * 100;
    
    std::cout << "Next year you'll be " << nextYear << std::endl;
    std::cout << "Height in cm: " << heightCm << std::endl;
    
    return 0;
})";
        return "<h2>Lesson 4: Input/Output & Operators</h2>"
               "<p>Interactive programs read input and produce output.</p>"
               "<p><b>Input/Output:</b></p>"
               "<ul><li><code>std::cout &lt;&lt;</code> - Output to console</li>"
               "<li><code>std::cin &gt;&gt;</code> - Input from keyboard</li>"
               "<li><code>std::endl</code> - Newline and flush</li></ul>"
               "<p><b>Arithmetic Operators:</b></p>"
               "<ul><li><code>+</code> Addition</li><li><code>-</code> Subtraction</li>"
               "<li><code>*</code> Multiplication</li><li><code>/</code> Division</li>"
               "<li><code>%</code> Modulo (remainder)</li></ul>"
               "<p><b>Remember:</b> Include <code>&lt;string&gt;</code> for std::string</p>";
    }
    else if (lessonName.contains("5.")) {
        currentExampleCode = R"(#include <iostream>

int main() {
    int x = 10;
    int y = 3;
    
    // Arithmetic operators
    std::cout << "x + y = " << (x + y) << std::endl;  // 13
    std::cout << "x - y = " << (x - y) << std::endl;  // 7
    std::cout << "x * y = " << (x * y) << std::endl;  // 30
    std::cout << "x / y = " << (x / y) << std::endl;  // 3 (integer division)
    std::cout << "x % y = " << (x % y) << std::endl;  // 1 (remainder)
    
    // Assignment operators
    int a = 5;
    a += 3;  // a = a + 3, now a = 8
    std::cout << "a after += 3: " << a << std::endl;
    
    a -= 2;  // a = a - 2, now a = 6
    std::cout << "a after -= 2: " << a << std::endl;
    
    a *= 2;  // a = a * 2, now a = 12
    std::cout << "a after *= 2: " << a << std::endl;
    
    // Increment/Decrement
    int count = 0;
    std::cout << "count++: " << count++ << std::endl;  // Prints 0, then increments
    std::cout << "++count: " << ++count << std::endl;  // Increments, then prints 2
    
    return 0;
})";
        return "<h2>Lesson 5: Arithmetic & Assignment</h2>"
               "<p>Operators perform operations on variables and values.</p>"
               "<p><b>Arithmetic Operators:</b></p>"
               "<ul><li><code>+, -, *, /</code> - Basic math operations</li>"
               "<li><code>%</code> - Modulo (remainder after division)</li></ul>"
               "<p><b>Assignment Operators:</b></p>"
               "<ul><li><code>=</code> - Basic assignment</li>"
               "<li><code>+=, -=, *=, /=, %=</code> - Compound assignment</li></ul>"
               "<p><b>Increment/Decrement:</b></p>"
               "<ul><li><code>++var</code> - Pre-increment (increment first, then use)</li>"
               "<li><code>var++</code> - Post-increment (use first, then increment)</li>"
               "<li><code>--var, var--</code> - Pre/post-decrement</li></ul>"
               "<p><b>Integer Division:</b> 10/3 = 3 (not 3.33), use double for decimals</p>";
    }
    
    return "<p>Select a lesson to view content. More lessons available...</p>";
}