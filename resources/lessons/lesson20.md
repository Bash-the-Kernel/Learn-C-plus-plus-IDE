# Lesson 20: Introduction to Object-Oriented Programming

## What is Object-Oriented Programming?

Object-Oriented Programming (OOP) is a programming paradigm that organizes code around **objects** rather than functions. It's like thinking about the real world - everything is an object with properties and behaviors.

## Real-World Analogy

Think of a **Car**:
- **Properties (Data):** color, model, year, fuel level
- **Behaviors (Functions):** start(), stop(), accelerate(), brake()

In OOP, we create a "blueprint" (class) for cars, then create individual car objects from that blueprint.

## Key OOP Concepts

### 1. Classes and Objects
- **Class:** A blueprint or template (like architectural plans)
- **Object:** An instance created from a class (like an actual house built from plans)

### 2. Encapsulation
- Bundling data and methods together
- Hiding internal details from outside access
- Like a TV remote - you press buttons without knowing internal circuits

### 3. Inheritance
- Creating new classes based on existing ones
- Child classes inherit properties and methods from parent classes
- Like how a "Sports Car" inherits from "Car" but adds specific features

### 4. Polymorphism
- Same interface, different implementations
- Like how different animals "speak" differently (dog barks, cat meows)

## Why Use OOP?

### Advantages:
- **Modularity:** Code is organized into logical units
- **Reusability:** Classes can be reused in different programs
- **Maintainability:** Easier to update and fix code
- **Scalability:** Easier to add new features
- **Real-world modeling:** Natural way to represent real-world entities

### Example: Banking System
```cpp
// Without OOP - procedural approach
double account1_balance = 1000.0;
string account1_owner = "Alice";
double account2_balance = 500.0;
string account2_owner = "Bob";

void deposit_account1(double amount) { /* ... */ }
void withdraw_account1(double amount) { /* ... */ }
// Repeat for account2... messy and hard to maintain!

// With OOP - object-oriented approach
class BankAccount {
private:
    double balance;
    string owner;
public:
    void deposit(double amount) { /* ... */ }
    void withdraw(double amount) { /* ... */ }
};

BankAccount alice_account;
BankAccount bob_account;
// Clean, organized, reusable!
```

## OOP vs Procedural Programming

| Procedural | Object-Oriented |
|------------|-----------------|
| Functions operate on data | Objects contain both data and functions |
| Data and functions are separate | Data and functions are bundled together |
| Global data can be accessed anywhere | Data is encapsulated and protected |
| Harder to model real-world entities | Natural modeling of real-world entities |

## Common OOP Languages

- **C++:** Multi-paradigm, supports both OOP and procedural
- **Java:** Pure OOP language
- **Python:** Multi-paradigm with strong OOP support
- **C#:** Microsoft's OOP language
- **JavaScript:** Prototype-based OOP

## When to Use OOP

**Good for:**
- Large, complex applications
- GUI applications
- Games with many entities
- Systems with many interacting components
- When modeling real-world entities

**Maybe overkill for:**
- Simple scripts
- Mathematical calculations
- Small utility programs

## Thinking in Objects

To design OOP solutions:

1. **Identify Objects:** What are the main "things" in your problem?
2. **Define Properties:** What data does each object need?
3. **Define Behaviors:** What can each object do?
4. **Find Relationships:** How do objects interact?

### Example: Library System
- **Objects:** Book, Member, Librarian, Library
- **Book properties:** title, author, ISBN, available
- **Book behaviors:** checkOut(), checkIn(), getInfo()
- **Relationships:** Member borrows Book, Librarian manages Library

## Next Steps

In upcoming lessons, we'll learn:
- How to create classes and objects in C++
- Constructors and destructors
- Access specifiers (public, private, protected)
- Member functions and data members
- Inheritance and polymorphism

## Practice Thinking

Before the next lesson, think about these in OOP terms:
1. A video game with players, enemies, and items
2. A school system with students, teachers, and courses
3. A social media platform with users, posts, and comments

What would be the objects, properties, and behaviors for each?