# Lesson 3: Input and Output

## Output with cout

The `std::cout` object sends data to the console.

```cpp
#include <iostream>

std::cout << "Hello!";           // Print text
std::cout << 42;                 // Print number
std::cout << "Age: " << 25;      // Chain multiple items
std::cout << "Line 1" << std::endl;  // New line
```

## Input with cin

The `std::cin` object reads data from the keyboard.

```cpp
#include <iostream>

int age;
std::cout << "Enter your age: ";
std::cin >> age;
std::cout << "You are " << age << " years old." << std::endl;
```

## Reading Strings

```cpp
#include <iostream>
#include <string>

std::string name;
std::cout << "Enter your name: ";
std::cin >> name;  // Reads until space

// To read full line with spaces:
std::getline(std::cin, name);
```

## Multiple Inputs

```cpp
int x, y;
std::cout << "Enter two numbers: ";
std::cin >> x >> y;
std::cout << "Sum: " << (x + y) << std::endl;
```

## Formatting Output

```cpp
#include <iomanip>

double price = 19.99;
std::cout << std::fixed << std::setprecision(2);
std::cout << "Price: $" << price << std::endl;
```

## Common Mistakes

1. **Forgetting std::**
   ```cpp
   cout << "Hello";  // Error!
   std::cout << "Hello";  // Correct
   ```

2. **Wrong direction of arrows**
   ```cpp
   std::cin << x;  // Wrong!
   std::cin >> x;  // Correct
   ```

## Practice

Write a program that:
1. Asks for your name
2. Asks for your favorite number
3. Prints a message using both
