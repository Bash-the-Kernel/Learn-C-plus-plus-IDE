# Challenge 15: Fibonacci Sequence [Intermediate]

## Objective

Generate and display the Fibonacci sequence up to a specified number of terms.

## What is Fibonacci Sequence?

The Fibonacci sequence is a series of numbers where each number is the sum of the two preceding ones:

**Sequence:** 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144...

**Formula:** F(n) = F(n-1) + F(n-2)
- F(0) = 0
- F(1) = 1

## Requirements

1. Ask user how many Fibonacci numbers to generate
2. Calculate and display the sequence
3. Handle edge cases (n = 0, n = 1)
4. Use efficient algorithm

## Sample Input/Output

```
How many Fibonacci numbers? 10

Fibonacci sequence (10 terms):
0, 1, 1, 2, 3, 5, 8, 13, 21, 34
```

## Algorithm Approaches

### 1. Iterative Approach (Recommended)
```cpp
int a = 0, b = 1;
for (int i = 0; i < n; i++) {
    // Print current number
    // Calculate next: next = a + b
    // Update: a = b, b = next
}
```

### 2. Recursive Approach (Educational)
```cpp
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}
```

## Bonus Challenges

1. **Performance Comparison:** Implement both iterative and recursive versions, compare speed
2. **Large Numbers:** Handle large Fibonacci numbers (use `long long`)
3. **Golden Ratio:** Calculate and display the ratio between consecutive terms
4. **Fibonacci Checker:** Check if a given number is in the Fibonacci sequence
5. **Visualization:** Display the sequence in a formatted table with indices

## Mathematical Properties

- **Golden Ratio:** As n increases, F(n+1)/F(n) approaches φ ≈ 1.618
- **Nature:** Appears in flower petals, pine cones, spiral shells
- **Art:** Used in architecture and design for pleasing proportions

## Real-World Applications

- **Computer Science:** Algorithm analysis, data structures
- **Nature:** Modeling population growth, plant growth patterns
- **Finance:** Technical analysis in trading
- **Art & Design:** Composition and proportions

## Hints

1. **Start Simple:** Handle n=0 and n=1 as special cases
2. **Iterative is Better:** More efficient than recursion for this problem
3. **Variable Management:** Keep track of previous two numbers
4. **Output Formatting:** Consider how to display the sequence nicely

## Testing Cases

- n = 0: Should handle gracefully
- n = 1: Should display "0"
- n = 2: Should display "0, 1"
- n = 10: Should display first 10 terms
- Large n: Test performance and accuracy

## Extension Ideas

1. Create a Fibonacci calculator that finds the nth term
2. Build a Fibonacci spiral visualizer (text-based)
3. Implement Fibonacci search algorithm
4. Create a Fibonacci number validator

This challenge combines mathematical concepts with programming logic, making it perfect for understanding iterative algorithms and number sequences!