# Lesson 4: Conditionals (if/else)

## Making Decisions

Programs need to make decisions based on different conditions. This is where conditional statements come in.

## Basic if Statement

```cpp
if (condition) {
    // code runs if condition is true
}
```

## if-else Statement

```cpp
if (condition) {
    // runs if true
} else {
    // runs if false
}
```

## Multiple Conditions (if-else if)

```cpp
if (score >= 90) {
    cout << "Grade A";
} else if (score >= 80) {
    cout << "Grade B";
} else if (score >= 70) {
    cout << "Grade C";
} else {
    cout << "Grade F";
}
```

## Comparison Operators

- `==` equal to
- `!=` not equal to
- `>` greater than
- `<` less than
- `>=` greater than or equal
- `<=` less than or equal

## Logical Operators

- `&&` AND (both conditions must be true)
- `||` OR (at least one condition must be true)
- `!` NOT (reverses the condition)

## Example

```cpp
int age = 18;
bool hasLicense = true;

if (age >= 18 && hasLicense) {
    cout << "Can drive!";
} else {
    cout << "Cannot drive";
}
```

## Practice

Try writing conditions for:
- Checking if a number is positive, negative, or zero
- Determining if someone can vote (age >= 18)
- Checking if a year is a leap year