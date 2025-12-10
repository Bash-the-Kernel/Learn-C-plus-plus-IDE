# Lesson 5: Loops

## Repeating Code

Loops allow you to execute code multiple times without writing it repeatedly.

## For Loop

Use when you know how many times to repeat:

```cpp
for (initialization; condition; increment) {
    // code to repeat
}
```

**Example:**
```cpp
for (int i = 0; i < 5; i++) {
    cout << "Count: " << i << endl;
}
```

## While Loop

Use when you repeat based on a condition:

```cpp
while (condition) {
    // code to repeat
    // make sure to change the condition!
}
```

**Example:**
```cpp
int count = 0;
while (count < 5) {
    cout << "Count: " << count << endl;
    count++;  // Don't forget this!
}
```

## Do-While Loop

Executes at least once, then checks condition:

```cpp
do {
    // code to repeat
} while (condition);
```

## Loop Control

- `break` - Exit the loop immediately
- `continue` - Skip to next iteration

## Common Patterns

- `i++` means `i = i + 1`
- `i--` means `i = i - 1`
- `i += 2` means `i = i + 2`

## Infinite Loops (Avoid!)

```cpp
while (true) {
    // This runs forever!
    // Make sure you have a break condition
}
```

## Practice Ideas

- Count from 1 to 10
- Print even numbers from 2 to 20
- Calculate sum of numbers 1 to 100
- Print multiplication table