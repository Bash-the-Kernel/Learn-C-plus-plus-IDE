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
    // Core Fundamentals (1-10)
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
    
    // Intermediate Topics (11-20)
    lessonsList->addItem("11. Function Parameters & Return");
    lessonsList->addItem("12. Arrays Introduction");
    lessonsList->addItem("13. Strings (std::string)");
    lessonsList->addItem("14. Vectors (std::vector)");
    lessonsList->addItem("15. References & Pass by Reference");
    lessonsList->addItem("16. Pointers Basics");
    lessonsList->addItem("17. Classes & Objects");
    lessonsList->addItem("18. Constructors & Destructors");
    lessonsList->addItem("19. Member Functions & Encapsulation");
    lessonsList->addItem("20. File I/O");
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
    else if (lessonName.contains("6.")) {
        currentExampleCode = R"(#include <iostream>

int main() {
    int score;
    std::cout << "Enter your test score: ";
    std::cin >> score;
    
    if (score >= 90) {
        std::cout << "Grade: A - Excellent!" << std::endl;
    }
    else if (score >= 80) {
        std::cout << "Grade: B - Good job!" << std::endl;
    }
    else if (score >= 70) {
        std::cout << "Grade: C - Not bad" << std::endl;
    }
    else if (score >= 60) {
        std::cout << "Grade: D - Need improvement" << std::endl;
    }
    else {
        std::cout << "Grade: F - Study harder!" << std::endl;
    }
    
    return 0;
})";
        return "<h2>Lesson 6: Conditionals & Comparisons</h2>"
               "<p>Make decisions with if/else statements.</p>"
               "<p><b>Comparison Operators:</b> ==, !=, &gt;, &lt;, &gt;=, &lt;=</p>"
               "<p><b>Structure:</b> if (condition) { code } else { code }</p>";
    }
    else if (lessonName.contains("7.")) {
        currentExampleCode = R"(#include <iostream>

int main() {
    bool isRaining = true;
    bool hasUmbrella = false;
    int temperature = 75;
    
    // Logical AND (&&)
    if (isRaining && hasUmbrella) {
        std::cout << "Go outside with umbrella" << std::endl;
    }
    
    // Logical OR (||)
    if (temperature > 80 || temperature < 32) {
        std::cout << "Extreme weather!" << std::endl;
    }
    
    // Logical NOT (!)
    if (!isRaining) {
        std::cout << "No umbrella needed" << std::endl;
    }
    
    return 0;
})";
        return "<h2>Lesson 7: Logical Operators</h2>"
               "<p>Combine multiple conditions with logical operators.</p>"
               "<p><b>Operators:</b> && (AND), || (OR), ! (NOT)</p>";
    }
    else if (lessonName.contains("8.")) {
        currentExampleCode = R"(#include <iostream>

int main() {
    // Basic for loop
    for (int i = 1; i <= 5; i++) {
        std::cout << "Count: " << i << std::endl;
    }
    
    // Loop with different step
    std::cout << "Even numbers:" << std::endl;
    for (int i = 2; i <= 10; i += 2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    return 0;
})";
        return "<h2>Lesson 8: For Loops</h2>"
               "<p>Repeat code a specific number of times.</p>"
               "<p><b>Syntax:</b> for (init; condition; increment) { code }</p>";
    }
    else if (lessonName.contains("9.")) {
        currentExampleCode = R"(#include <iostream>

int main() {
    // While loop
    int count = 1;
    while (count <= 3) {
        std::cout << "While count: " << count << std::endl;
        count++;
    }
    
    // Do-while loop (executes at least once)
    int num;
    do {
        std::cout << "Enter a positive number: ";
        std::cin >> num;
    } while (num <= 0);
    
    std::cout << "You entered: " << num << std::endl;
    
    return 0;
})";
        return "<h2>Lesson 9: While & Do-While Loops</h2>"
               "<p>Repeat code based on conditions.</p>"
               "<p><b>While:</b> Check condition first</p>"
               "<p><b>Do-While:</b> Execute once, then check condition</p>";
    }
    else if (lessonName.contains("10.")) {
        currentExampleCode = R"(#include <iostream>

void sayHello() {
    std::cout << "Hello from function!" << std::endl;
}

int main() {
    std::cout << "Before function call" << std::endl;
    sayHello();
    std::cout << "After function call" << std::endl;
    
    return 0;
})";
        return "<h2>Lesson 10: Functions Basics</h2>"
               "<p>Create reusable blocks of code.</p>"
               "<p><b>Syntax:</b> returnType functionName() { code }</p>";
    }
    else if (lessonName.contains("11.")) {
        currentExampleCode = R"(#include <iostream>

// Function with parameters
int add(int a, int b) {
    return a + b;
}

// Function with multiple parameters
double calculateArea(double width, double height) {
    return width * height;
}

// Function returning bool
bool isEven(int number) {
    return number % 2 == 0;
}

int main() {
    int sum = add(5, 3);
    std::cout << "5 + 3 = " << sum << std::endl;
    
    double area = calculateArea(4.5, 2.0);
    std::cout << "Area: " << area << std::endl;
    
    if (isEven(10)) {
        std::cout << "10 is even" << std::endl;
    }
    
    return 0;
})";
        return "<h2>Lesson 11: Function Parameters & Return</h2>"
               "<p>Functions can accept input (parameters) and return output.</p>"
               "<p><b>Parameters:</b> Variables passed to functions</p>"
               "<p><b>Return:</b> Send a value back to the caller</p>"
               "<p><b>Syntax:</b> returnType name(type param1, type param2)</p>"
               "<p><b>void:</b> Use when function doesn't return anything</p>";
    }
    else if (lessonName.contains("12.")) {
        currentExampleCode = R"(#include <iostream>

int main() {
    // Declare array of 5 integers
    int numbers[5] = {10, 20, 30, 40, 50};
    
    // Access elements by index (starts at 0)
    std::cout << "First element: " << numbers[0] << std::endl;
    std::cout << "Third element: " << numbers[2] << std::endl;
    
    // Modify elements
    numbers[1] = 25;
    
    // Loop through array
    std::cout << "All elements: ";
    for (int i = 0; i < 5; i++) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;
    
    // Array size must be known at compile time
    const int SIZE = 3;
    double prices[SIZE] = {9.99, 14.50, 7.25};
    
    return 0;
})";
        return "<h2>Lesson 12: Arrays Introduction</h2>"
               "<p>Arrays store multiple values of the same type in contiguous memory.</p>"
               "<p><b>Declaration:</b> type name[size] = {values};</p>"
               "<p><b>Indexing:</b> Access elements with [0] to [size-1]</p>"
               "<p><b>Fixed Size:</b> Array size cannot change after declaration</p>"
               "<p><b>Warning:</b> No bounds checking - accessing out of range is undefined behavior</p>";
    }
    else if (lessonName.contains("13.")) {
        currentExampleCode = R"(#include <iostream>
#include <string>

int main() {
    // Create strings
    std::string name = "Alice";
    std::string greeting = "Hello, " + name + "!";
    
    std::cout << greeting << std::endl;
    
    // String methods
    std::cout << "Length: " << name.length() << std::endl;
    std::cout << "First char: " << name[0] << std::endl;
    
    // String input
    std::string city;
    std::cout << "Enter city: ";
    std::getline(std::cin, city);  // Reads entire line
    
    // String comparison
    if (name == "Alice") {
        std::cout << "Name matches!" << std::endl;
    }
    
    // Substring
    std::string sub = name.substr(0, 3);  // "Ali"
    
    return 0;
})";
        return "<h2>Lesson 13: Strings (std::string)</h2>"
               "<p>std::string is a class for handling text in C++.</p>"
               "<p><b>Include:</b> #include &lt;string&gt;</p>"
               "<p><b>Concatenation:</b> Use + to join strings</p>"
               "<p><b>Methods:</b> length(), substr(), find(), etc.</p>"
               "<p><b>Input:</b> Use std::getline() for strings with spaces</p>"
               "<p><b>Comparison:</b> Use ==, !=, &lt;, &gt; operators</p>";
    }
    else if (lessonName.contains("14.")) {
        currentExampleCode = R"(#include <iostream>
#include <vector>

int main() {
    // Create vector
    std::vector<int> numbers = {10, 20, 30};
    
    // Add elements
    numbers.push_back(40);
    numbers.push_back(50);
    
    std::cout << "Size: " << numbers.size() << std::endl;
    
    // Access elements
    std::cout << "First: " << numbers[0] << std::endl;
    std::cout << "Last: " << numbers[numbers.size() - 1] << std::endl;
    
    // Loop through vector
    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;
    
    // Range-based for loop (C++11)
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Remove last element
    numbers.pop_back();
    
    return 0;
})";
        return "<h2>Lesson 14: Vectors (std::vector)</h2>"
               "<p>Vectors are dynamic arrays that can grow and shrink.</p>"
               "<p><b>Include:</b> #include &lt;vector&gt;</p>"
               "<p><b>Declaration:</b> std::vector&lt;type&gt; name;</p>"
               "<p><b>Key Methods:</b></p>"
               "<ul><li>push_back() - Add element at end</li>"
               "<li>pop_back() - Remove last element</li>"
               "<li>size() - Get number of elements</li>"
               "<li>clear() - Remove all elements</li></ul>"
               "<p><b>Advantage:</b> Automatic memory management</p>";
    }
    else if (lessonName.contains("15.")) {
        currentExampleCode = R"(#include <iostream>

// Pass by value (makes a copy)
void incrementValue(int x) {
    x = x + 1;  // Only changes local copy
}

// Pass by reference (modifies original)
void incrementReference(int& x) {
    x = x + 1;  // Changes original variable
}

int main() {
    int num = 10;
    
    incrementValue(num);
    std::cout << "After value: " << num << std::endl;  // Still 10
    
    incrementReference(num);
    std::cout << "After reference: " << num << std::endl;  // Now 11
    
    // Reference as alias
    int original = 5;
    int& ref = original;  // ref is another name for original
    ref = 10;  // Changes original to 10
    
    std::cout << "Original: " << original << std::endl;  // 10
    
    return 0;
})";
        return "<h2>Lesson 15: References & Pass by Reference</h2>"
               "<p>References are aliases to existing variables.</p>"
               "<p><b>Pass by Value:</b> Function gets a copy (default)</p>"
               "<p><b>Pass by Reference:</b> Function gets the original (use &)</p>"
               "<p><b>Syntax:</b> type& refName = variable;</p>"
               "<p><b>Use Cases:</b></p>"
               "<ul><li>Modify function arguments</li>"
               "<li>Avoid copying large objects</li>"
               "<li>Return multiple values</li></ul>"
               "<p><b>Note:</b> References must be initialized and cannot be reassigned</p>";
    }
    else if (lessonName.contains("16.")) {
        currentExampleCode = R"(#include <iostream>

int main() {
    int number = 42;
    int* ptr = &number;  // Pointer stores address
    
    std::cout << "Value: " << number << std::endl;
    std::cout << "Address: " << &number << std::endl;
    std::cout << "Pointer: " << ptr << std::endl;
    std::cout << "Value via pointer: " << *ptr << std::endl;
    
    // Modify via pointer
    *ptr = 100;
    std::cout << "New value: " << number << std::endl;
    
    // Pointer arithmetic
    int arr[3] = {10, 20, 30};
    int* p = arr;  // Points to first element
    std::cout << *p << std::endl;      // 10
    std::cout << *(p + 1) << std::endl;  // 20
    std::cout << *(p + 2) << std::endl;  // 30
    
    return 0;
})";
        return "<h2>Lesson 16: Pointers Basics</h2>"
               "<p>Pointers store memory addresses of variables.</p>"
               "<p><b>Declaration:</b> type* ptrName;</p>"
               "<p><b>& operator:</b> Gets address of variable</p>"
               "<p><b>* operator:</b> Dereferences pointer (gets value)</p>"
               "<p><b>nullptr:</b> Pointer that points to nothing</p>"
               "<p><b>Use Cases:</b> Dynamic memory, arrays, data structures</p>"
               "<p><b>Warning:</b> Dereferencing null/invalid pointers causes crashes</p>";
    }
    else if (lessonName.contains("17.")) {
        currentExampleCode = R"(#include <iostream>
#include <string>

class Student {
public:
    std::string name;
    int age;
    double gpa;
    
    void introduce() {
        std::cout << "Hi, I'm " << name << ", age " << age << std::endl;
    }
    
    void study() {
        std::cout << name << " is studying..." << std::endl;
    }
};

int main() {
    // Create object
    Student student1;
    student1.name = "Alice";
    student1.age = 20;
    student1.gpa = 3.8;
    
    // Call methods
    student1.introduce();
    student1.study();
    
    // Create another object
    Student student2;
    student2.name = "Bob";
    student2.age = 21;
    student2.gpa = 3.5;
    
    student2.introduce();
    
    return 0;
})";
        return "<h2>Lesson 17: Classes & Objects</h2>"
               "<p>Classes are blueprints for creating objects.</p>"
               "<p><b>Class:</b> Defines structure and behavior</p>"
               "<p><b>Object:</b> Instance of a class</p>"
               "<p><b>Members:</b> Variables (data) and functions (methods)</p>"
               "<p><b>public:</b> Accessible from outside the class</p>"
               "<p><b>Syntax:</b> class Name { public: members; };</p>"
               "<p><b>Access:</b> Use dot operator (object.member)</p>";
    }
    else if (lessonName.contains("18.")) {
        currentExampleCode = R"(#include <iostream>
#include <string>

class BankAccount {
public:
    std::string owner;
    double balance;
    
    // Constructor - called when object is created
    BankAccount(std::string name, double initial) {
        owner = name;
        balance = initial;
        std::cout << "Account created for " << owner << std::endl;
    }
    
    // Destructor - called when object is destroyed
    ~BankAccount() {
        std::cout << "Account closed for " << owner << std::endl;
    }
    
    void deposit(double amount) {
        balance += amount;
    }
};

int main() {
    // Constructor is called automatically
    BankAccount account("Alice", 1000.0);
    
    account.deposit(500);
    std::cout << "Balance: $" << account.balance << std::endl;
    
    // Destructor called automatically when main() ends
    return 0;
})";
        return "<h2>Lesson 18: Constructors & Destructors</h2>"
               "<p>Special functions that initialize and clean up objects.</p>"
               "<p><b>Constructor:</b> Same name as class, no return type</p>"
               "<p><b>Called:</b> Automatically when object is created</p>"
               "<p><b>Purpose:</b> Initialize member variables</p>"
               "<p><b>Destructor:</b> ~ClassName(), called when object is destroyed</p>"
               "<p><b>Use:</b> Clean up resources (files, memory, etc.)</p>";
    }
    else if (lessonName.contains("19.")) {
        currentExampleCode = R"(#include <iostream>
#include <string>

class Rectangle {
private:
    double width;
    double height;
    
public:
    // Constructor
    Rectangle(double w, double h) : width(w), height(h) {}
    
    // Getter methods
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    
    // Setter methods
    void setWidth(double w) {
        if (w > 0) width = w;
    }
    
    void setHeight(double h) {
        if (h > 0) height = h;
    }
    
    // Member function
    double getArea() const {
        return width * height;
    }
};

int main() {
    Rectangle rect(5.0, 3.0);
    
    std::cout << "Area: " << rect.getArea() << std::endl;
    
    rect.setWidth(10.0);
    std::cout << "New area: " << rect.getArea() << std::endl;
    
    return 0;
})";
        return "<h2>Lesson 19: Member Functions & Encapsulation</h2>"
               "<p>Encapsulation hides internal details and provides controlled access.</p>"
               "<p><b>private:</b> Only accessible within the class</p>"
               "<p><b>public:</b> Accessible from anywhere</p>"
               "<p><b>Getters:</b> Functions that return private data</p>"
               "<p><b>Setters:</b> Functions that modify private data with validation</p>"
               "<p><b>const:</b> Member functions that don't modify the object</p>"
               "<p><b>Benefits:</b> Data protection, validation, flexibility</p>";
    }
    else if (lessonName.contains("20.")) {
        currentExampleCode = R"(#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Write to file
    std::ofstream outFile("data.txt");
    if (outFile.is_open()) {
        outFile << "Hello, File!" << std::endl;
        outFile << "Line 2" << std::endl;
        outFile << 42 << std::endl;
        outFile.close();
        std::cout << "File written successfully" << std::endl;
    }
    
    // Read from file
    std::ifstream inFile("data.txt");
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            std::cout << line << std::endl;
        }
        inFile.close();
    } else {
        std::cout << "Could not open file" << std::endl;
    }
    
    return 0;
})";
        return "<h2>Lesson 20: File I/O</h2>"
               "<p>Read from and write to files using file streams.</p>"
               "<p><b>Include:</b> #include &lt;fstream&gt;</p>"
               "<p><b>ofstream:</b> Output file stream (writing)</p>"
               "<p><b>ifstream:</b> Input file stream (reading)</p>"
               "<p><b>Writing:</b> Use &lt;&lt; operator like cout</p>"
               "<p><b>Reading:</b> Use &gt;&gt; or getline()</p>"
               "<p><b>Always:</b> Check if file opened successfully</p>"
               "<p><b>Remember:</b> Close files when done</p>";
    }

    
    return "<p>Select a lesson to view content. 20 comprehensive lessons available!</p>";
}