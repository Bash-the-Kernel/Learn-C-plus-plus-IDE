# Quick Start Guide

## Installation

### Prerequisites

1. **Qt 6** - Download from https://www.qt.io/download
2. **CMake 3.16+** - Download from https://cmake.org/download/
3. **C++ Compiler:**
   - Windows: MinGW-w64 or MSVC
   - Linux: g++ (usually pre-installed)
   - macOS: Xcode Command Line Tools

### Building the IDE

#### Windows

```bash
# Run the build script
build.bat

# Or manually:
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

#### Linux/macOS

```bash
# Make the script executable
chmod +x build.sh

# Run the build script
./build.sh

# Or manually:
mkdir build
cd build
cmake ..
make
```

## First Steps

### 1. Launch the IDE

```bash
# Windows
cd build
CppLearningIDE.exe

# Linux/macOS
cd build
./CppLearningIDE
```

### 2. Create Your First Program

1. Click **File → New File** (or Ctrl+N)
2. Type this code:

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, C++!" << std::endl;
    return 0;
}
```

3. Click **File → Save** (or Ctrl+S)
4. Save as `hello.cpp`

### 3. Build and Run

1. Click the **Build** button in the toolbar
2. Check the output panel for compilation messages
3. If successful, click the **Run** button
4. See your output in the bottom panel!

## Learning Path

### Step 1: Complete the Lessons

1. Click the **Lessons** tab on the right
2. Start with "1. Hello World"
3. Read the lesson content
4. Click **Load Code Example**
5. Modify and experiment with the code
6. Build and run to see results

### Step 2: Try the Challenges

1. Click the **Challenges** tab
2. Select "Challenge 1: Sum Two Numbers"
3. Click **Load Challenge** to get skeleton code
4. Write your solution
5. Click **Show Hint** if you get stuck
6. Test your solution by building and running

### Step 3: Explore Documentation

1. Click the **Docs** tab
2. Browse C++ reference topics
3. Click any topic to open in your browser
4. Learn about standard library features

## Common Tasks

### Creating a New Project

1. Click **File → New Project**
2. Select a folder for your project
3. Choose a template:
   - **Hello World** - Basic program structure
   - **Basic IO** - Input and output
   - **Loops & Conditionals** - Control flow
   - **Classes & Objects** - Object-oriented programming
   - **Vectors & Strings** - STL containers
4. The IDE creates a `main.cpp` and `CMakeLists.txt`

### Opening an Existing Project

1. Click **File → Open Project**
2. Select the project folder
3. The file explorer shows all files
4. Double-click any file to open it

### Working with Multiple Files

1. Open multiple files using **File → Open File**
2. Each file opens in a new tab
3. Click tabs to switch between files
4. Close tabs with the X button

### Switching Themes

1. Click **View → Toggle Theme**
2. Switch between dark and light modes
3. Theme applies immediately

## Tips for Beginners

### Understanding Compiler Errors

The IDE translates cryptic compiler errors into friendly messages:

**Example 1:**
```
error: expected ';' before 'return'
```
**Friendly hint:** "Missing semicolon. Check the end of the previous line."

**Example 2:**
```
error: 'cout' was not declared in this scope
```
**Friendly hint:** "Variable or function not declared. Did you forget to include a header or declare it?"

### Best Practices

1. **Save Often** - Use Ctrl+S frequently
2. **Build Regularly** - Catch errors early
3. **Read Error Messages** - They tell you what's wrong
4. **Experiment** - Modify examples to learn
5. **Use Lessons** - Follow the structured path

### Keyboard Shortcuts

- **Ctrl+N** - New File
- **Ctrl+O** - Open File
- **Ctrl+S** - Save File
- **Ctrl+Shift+S** - Save As
- **Ctrl+Z** - Undo
- **Ctrl+Y** - Redo
- **Ctrl+Q** - Quit

## Troubleshooting

### Build Fails

**Problem:** "g++ not found" or "clang++ not found"

**Solution:** Install a C++ compiler:
- Windows: Install MinGW-w64
- Linux: `sudo apt install g++` or `sudo yum install gcc-c++`
- macOS: `xcode-select --install`

### Qt Not Found

**Problem:** CMake can't find Qt

**Solution:** Set Qt path:
```bash
# Windows
set CMAKE_PREFIX_PATH=C:\Qt\6.x.x\mingw_64

# Linux/macOS
export CMAKE_PREFIX_PATH=/path/to/Qt/6.x.x/gcc_64
```

### Program Doesn't Run

**Problem:** "Executable not found"

**Solution:** Build the program first using the Build button

### Output Panel Empty

**Problem:** No output when running

**Solution:** Make sure your program uses `std::cout` to print output

## Next Steps

### After Completing Lessons

1. **Modify Examples** - Change the code and see what happens
2. **Combine Concepts** - Use loops with vectors, classes with functions
3. **Create Projects** - Build small programs from scratch
4. **Read Documentation** - Explore the C++ standard library
5. **Challenge Yourself** - Try harder problems

### Learning Resources

- **cppreference.com** - Comprehensive C++ reference
- **learncpp.com** - Detailed tutorials
- **C++ Core Guidelines** - Best practices
- **Stack Overflow** - Community Q&A

### Project Ideas

1. **Calculator** - Basic arithmetic operations
2. **Number Guessing Game** - Random numbers and loops
3. **To-Do List** - Vectors and file I/O
4. **Student Grade Manager** - Classes and data structures
5. **Text Adventure** - Functions and control flow

## Getting Help

### Within the IDE

1. Use the **Lessons** tab for tutorials
2. Click **Show Hint** in challenges
3. Check the **Docs** tab for reference
4. Read friendly error messages

### External Resources

1. Search error messages online
2. Ask on Stack Overflow
3. Join C++ communities
4. Read the C++ documentation

---

**Happy Coding!** Start with Lesson 1 and work your way through. Remember: everyone starts as a beginner! 🚀
