# Getting Started with C++ Learning IDE

## Welcome! 👋

This guide will help you set up and start using the C++ Learning IDE.

## Prerequisites

Before building the IDE, ensure you have:

### 1. Qt 6 Framework

**Download:** https://www.qt.io/download-open-source

**Installation:**
- Download Qt Online Installer
- Install Qt 6.x (latest version)
- Select components:
  - Qt 6.x for your platform (MinGW 64-bit for Windows, GCC for Linux, Clang for macOS)
  - Qt Creator (optional, but helpful)
  - CMake

**Set Qt Path (if needed):**
```bash
# Windows
set CMAKE_PREFIX_PATH=C:\Qt\6.5.0\mingw_64

# Linux
export CMAKE_PREFIX_PATH=/opt/Qt/6.5.0/gcc_64

# macOS
export CMAKE_PREFIX_PATH=/Users/username/Qt/6.5.0/macos
```

### 2. CMake

**Download:** https://cmake.org/download/

**Minimum Version:** 3.16

**Verify Installation:**
```bash
cmake --version
```

### 3. C++ Compiler

**Windows:**
- MinGW-w64: https://www.mingw-w64.org/
- Or MSVC (Visual Studio)

**Linux:**
```bash
sudo apt install g++        # Debian/Ubuntu
sudo yum install gcc-c++    # RedHat/CentOS
```

**macOS:**
```bash
xcode-select --install
```

**Verify Installation:**
```bash
g++ --version
# or
clang++ --version
```

## Building the IDE

### Option 1: Using Build Scripts (Recommended)

**Windows:**
```bash
cd Learn-C-plus-plus-IDE
build.bat
```

**Linux/macOS:**
```bash
cd Learn-C-plus-plus-IDE
chmod +x build.sh
./build.sh
```

### Option 2: Manual Build

**All Platforms:**
```bash
cd Learn-C-plus-plus-IDE
mkdir build
cd build

# Configure
cmake ..

# Build
cmake --build .

# Or on Linux/macOS
make
```

### Build Output

After successful build, you'll find:
- **Windows:** `build/CppLearningIDE.exe`
- **Linux:** `build/CppLearningIDE`
- **macOS:** `build/CppLearningIDE.app`

## Running the IDE

### Windows
```bash
cd build
CppLearningIDE.exe
```

### Linux/macOS
```bash
cd build
./CppLearningIDE
```

## First Time Setup

### 1. Verify Compiler

The IDE will automatically detect your compiler (clang++ or g++). To verify:

1. Create a new file (Ctrl+N)
2. Type:
   ```cpp
   #include <iostream>
   int main() {
       std::cout << "Hello!" << std::endl;
       return 0;
   }
   ```
3. Save the file (Ctrl+S)
4. Click "Build"
5. Check output panel for success message

### 2. Explore the Interface

**Left Panel:** File Explorer
- Browse your files
- Double-click to open

**Center:** Code Editor
- Write your C++ code
- Syntax highlighting active
- Line numbers visible

**Bottom Panel:** Output
- Build messages
- Program output
- Error messages

**Right Panel:** Learning Resources
- **Lessons Tab:** Tutorials
- **Challenges Tab:** Coding exercises
- **Docs Tab:** Reference links

## Your First Program

### Step 1: Create a New File

1. Click **File → New File** (or Ctrl+N)
2. A new tab opens with an empty editor

### Step 2: Write Code

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, C++ Learning IDE!" << std::endl;
    return 0;
}
```

### Step 3: Save

1. Click **File → Save** (or Ctrl+S)
2. Choose location and filename (e.g., `hello.cpp`)

### Step 4: Build

1. Click the **Build** button in toolbar
2. Wait for compilation
3. Check output panel:
   - ✅ "Build successful" = Good!
   - ❌ Error messages = Read the friendly hints

### Step 5: Run

1. Click the **Run** button
2. See output in bottom panel:
   ```
   === Running ===
   Hello, C++ Learning IDE!
   ```

## Learning Path

### Week 1: Basics

**Day 1-2:** Lessons 1-3
- Hello World
- Variables and Types
- Input and Output

**Day 3-4:** Challenges 1-2
- Sum Two Numbers
- Even or Odd

**Day 5:** Create your own simple programs

### Week 2: Control Flow

**Day 1-2:** Lessons 4-5
- Conditionals
- Loops

**Day 3-4:** Challenge 3
- Factorial

**Day 5:** Experiment with loops and conditions

### Week 3: Functions and Arrays

**Day 1-2:** Lessons 6-7
- Functions
- Arrays

**Day 3-5:** Create programs using functions

### Week 4: Modern C++

**Day 1-2:** Lessons 8-9
- Vectors
- Classes

**Day 3-5:** Build a small project

## Tips for Success

### 1. Read Error Messages

The IDE translates compiler errors:
```
error: expected ';' before 'return'
💡 Friendly hint: Missing semicolon. Check the end of the previous line.
```

### 2. Use Lessons

Don't skip the lessons! They build on each other:
1. Read the lesson
2. Load the example
3. Modify and experiment
4. Try variations

### 3. Practice with Challenges

Challenges help reinforce learning:
1. Read the description
2. Try solving without hints
3. Use hints if stuck
4. Compare with expected output

### 4. Experiment

The best way to learn:
- Change values
- Add new features
- Break things (then fix them!)
- Combine concepts

### 5. Use Documentation

Click the **Docs** tab for:
- C++ reference
- Standard library
- Container documentation
- Algorithm reference

## Common Issues

### Issue: "Qt not found"

**Solution:**
```bash
# Set Qt path
export CMAKE_PREFIX_PATH=/path/to/Qt/6.x.x/gcc_64
cmake ..
```

### Issue: "Compiler not found"

**Solution:**
- Install g++ or clang++
- Add to system PATH
- Restart terminal

### Issue: "Build failed"

**Solution:**
1. Check error messages
2. Verify code syntax
3. Read friendly hints
4. Check for missing semicolons, brackets

### Issue: "Program doesn't run"

**Solution:**
1. Build first (click Build button)
2. Check for build errors
3. Verify executable exists

### Issue: "No output"

**Solution:**
- Ensure you use `std::cout` to print
- Check program logic
- Verify `return 0;` at end

## Keyboard Shortcuts

| Action | Shortcut |
|--------|----------|
| New File | Ctrl+N |
| Open File | Ctrl+O |
| Save | Ctrl+S |
| Save As | Ctrl+Shift+S |
| Undo | Ctrl+Z |
| Redo | Ctrl+Y |
| Quit | Ctrl+Q |

## Project Templates

When creating a new project, choose from:

1. **Hello World** - Basic structure
2. **Basic IO** - Input/output
3. **Loops & Conditionals** - Control flow
4. **Classes & Objects** - OOP
5. **Vectors & Strings** - STL

## Next Steps

After getting comfortable:

1. **Complete all lessons** (1-10)
2. **Solve all challenges** (1-5)
3. **Create your own projects**
4. **Explore C++ documentation**
5. **Build something fun!**

## Project Ideas for Beginners

1. **Calculator** - Basic math operations
2. **Number Guessing Game** - Random numbers
3. **Temperature Converter** - Celsius/Fahrenheit
4. **Grade Calculator** - Average grades
5. **Simple To-Do List** - Add/remove items
6. **Multiplication Table** - Nested loops
7. **Palindrome Checker** - String manipulation
8. **Prime Number Finder** - Algorithms
9. **Simple Banking System** - Classes
10. **Text-Based Adventure** - Functions and logic

## Getting Help

### Within the IDE
- Read lesson content
- Use challenge hints
- Check documentation links
- Read friendly error messages

### External Resources
- **cppreference.com** - Comprehensive reference
- **learncpp.com** - Detailed tutorials
- **Stack Overflow** - Community Q&A
- **C++ Discord/Reddit** - Community support

## Troubleshooting Build Issues

### Windows Specific

**MinGW not in PATH:**
```bash
set PATH=C:\mingw64\bin;%PATH%
```

**Qt DLLs missing:**
- Copy Qt DLLs to build directory
- Or add Qt bin to PATH

### Linux Specific

**Missing dependencies:**
```bash
sudo apt install qt6-base-dev libgl1-mesa-dev
```

### macOS Specific

**Xcode tools:**
```bash
xcode-select --install
```

**Qt permissions:**
```bash
sudo chown -R $(whoami) /path/to/Qt
```

## Performance Tips

- Close unused tabs
- Save files regularly
- Clear output panel periodically
- Restart IDE if sluggish

## Customization

### Theme
- Toggle between dark/light: **View → Toggle Theme**

### Font Size
- Edit `EditorWidget.cpp` line with `QFont("Consolas", 11)`
- Change `11` to desired size
- Rebuild

## Community

### Contributing
- See CONTRIBUTING.md
- Add lessons
- Add challenges
- Fix bugs
- Improve documentation

### Sharing
- Share your projects
- Help other learners
- Report issues
- Suggest features

## Success Metrics

Track your progress:
- [ ] Built the IDE successfully
- [ ] Ran first program
- [ ] Completed Lesson 1
- [ ] Solved Challenge 1
- [ ] Created custom program
- [ ] Completed all lessons
- [ ] Solved all challenges
- [ ] Built a personal project

## Final Words

Learning C++ takes time and practice. This IDE is designed to make that journey easier and more enjoyable. Don't rush—take your time with each lesson, experiment freely, and most importantly, have fun coding!

**Remember:** Every expert was once a beginner. You've got this! 🚀

---

**Need Help?** Check README.md, QUICKSTART.md, or ARCHITECTURE.md

**Ready to Learn?** Launch the IDE and start with Lesson 1!

**Happy Coding!** 💻✨
