# Lesson 2: Variables and Data Types

## What are Variables?

Variables are containers that store data. Think of them as labeled boxes where you can put different types of information.

## Basic Data Types

### Integer Types
```cpp
int age = 25;           // Whole numbers
short smallNum = 100;   // Smaller range
long bigNum = 1000000;  // Larger range
```

### Floating-Point Types
```cpp
float price = 19.99f;      // Single precision
double distance = 384400.0; // Double precision
```

### Character and Boolean
```cpp
char grade = 'A';       // Single character
bool isPassing = true;  // true or false
```

### String Type
```cpp
#include <string>
std::string name = "Alice";  // Text
```

## Variable Declaration

```cpp
// Declare and initialize
int score = 100;

// Declare first, assign later
int lives;
lives = 3;

// Multiple declarations
int x = 5, y = 10, z = 15;
```

## Type Inference with auto

```cpp
auto number = 42;        // int
auto pi = 3.14159;       // double
auto letter = 'X';       // char
auto message = "Hello";  // const char*
```

## Constants

```cpp
const int MAX_LIVES = 3;
const double PI = 3.14159;
```

## Practice

Try declaring variables for:
- Your age
- Your height in meters
- Your first initial
- Whether you like programming
