# Lesson 6: Conditionals & Comparisons

## Making Decisions in Code

Programs need to make decisions based on different conditions. Conditional statements allow your program to execute different code paths.

## Basic if Statement

```cpp
if (condition) {
    // Code executes if condition is true
}
```

## if-else Statement

```cpp
if (condition) {
    // Executes if condition is true
} else {
    // Executes if condition is false
}
```

## Multiple Conditions (if-else if-else)

```cpp
int score = 85;

if (score >= 90) {
    cout << "Grade: A";
} else if (score >= 80) {
    cout << "Grade: B";
} else if (score >= 70) {
    cout << "Grade: C";
} else if (score >= 60) {
    cout << "Grade: D";
} else {
    cout << "Grade: F";
}
```

## Comparison Operators

| Operator | Meaning | Example |
|----------|---------|---------|
| `==` | Equal to | `x == 5` |
| `!=` | Not equal to | `x != 0` |
| `>` | Greater than | `age > 18` |
| `<` | Less than | `score < 60` |
| `>=` | Greater than or equal | `grade >= 90` |
| `<=` | Less than or equal | `temp <= 32` |

## Common Mistakes

1. **Assignment vs Comparison**
   ```cpp
   if (x = 5)    // Wrong! This assigns 5 to x
   if (x == 5)   // Correct! This compares x to 5
   ```

2. **Floating-point Comparison**
   ```cpp
   double x = 0.1 + 0.2;
   if (x == 0.3)  // May fail due to precision
   if (abs(x - 0.3) < 0.0001)  // Better approach
   ```

## Nested Conditionals

```cpp
if (weather == "sunny") {
    if (temperature > 75) {
        cout << "Perfect beach day!";
    } else {
        cout << "Nice day for a walk";
    }
} else {
    cout << "Maybe stay inside";
}
```

## Practice Exercises

1. Write a program to check if a number is positive, negative, or zero
2. Create a simple calculator that handles division by zero
3. Build a grade classifier that handles invalid scores
4. Make a program that determines if someone can vote based on age and citizenship

## Real-World Applications

- User authentication systems
- Game logic (health checks, level progression)
- Financial software (credit approval, transaction validation)
- Safety systems (temperature monitoring, security checks)