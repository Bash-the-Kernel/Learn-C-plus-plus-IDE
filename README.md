# C++ Learning IDE

A beginner-friendly desktop IDE specifically designed for learning C++. Built with Qt 6 and C++20.

## Features

- **Custom Code Editor** with syntax highlighting for C++
- **Line numbers** and current line highlighting
- **File Explorer** for project navigation
- **Build System** integration with g++/clang++
- **Run Manager** to execute compiled programs
- **Beginner-Friendly Error Messages** that explain common compiler errors
- **Built-in Lessons** with interactive tutorials
- **Coding Challenges** with hints and skeleton code
- **Documentation Links** to cppreference.com
- **Dark/Light Theme** support
- **Project Templates** (Hello World, Basic IO, Loops, Classes, Vectors)

## Requirements

- Qt 6.x
- CMake 3.16+
- C++20 compatible compiler (g++ or clang++)
- Windows/Linux/macOS

## Build Instructions

### Windows

```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

### Linux/macOS

```bash
mkdir build
cd build
cmake ..
make
```

## Running the IDE

After building, run the executable:

```bash
# Windows
.\CppLearningIDE.exe

# Linux/macOS
./CppLearningIDE
```

## Project Structure

```
cpp-learning-ide/
├── src/
│   ├── main.cpp                 # Entry point
│   ├── MainWindow.h/cpp         # Main application window
│   ├── EditorWidget.h/cpp       # Code editor with line numbers
│   ├── SyntaxHighlighter.h/cpp  # C++ syntax highlighting
│   ├── BuildSystem.h/cpp        # Compiler integration
│   ├── RunManager.h/cpp         # Program execution
│   ├── ProjectManager.h/cpp     # Project templates
│   ├── DocsPanel.h/cpp          # Documentation links
│   ├── LessonsPanel.h/cpp       # Tutorial system
│   └── ChallengesPanel.h/cpp    # Coding challenges
├── resources/
│   ├── lessons/                 # Lesson files
│   ├── challenges/              # Challenge files
│   ├── templates/               # Project templates
│   └── icons/                   # UI icons
├── CMakeLists.txt
└── README.md
```

## Usage Guide

### Creating a New File

1. Click **File → New File** or use the toolbar
2. Write your C++ code
3. Save with **File → Save** (Ctrl+S)

### Creating a New Project

1. Click **File → New Project**
2. Select a directory
3. Choose a template (Hello World, Basic IO, etc.)
4. The IDE will generate a main.cpp file

### Building and Running

1. Open or create a C++ file
2. Click **Build** to compile
3. Check the output panel for errors
4. Click **Run** to execute the program
5. View output in the bottom panel

### Using Lessons

1. Click the **Lessons** tab on the right panel
2. Select a lesson from the list
3. Read the tutorial content
4. Click **Load Code Example** to insert example code

### Using Challenges

1. Click the **Challenges** tab
2. Select a challenge
3. Click **Load Challenge** to get skeleton code
4. Click **Show Hint** if you need help
5. Write your solution and test it

### Accessing Documentation

1. Click the **Docs** tab
2. Select a topic (Containers, Algorithms, etc.)
3. The link opens in your default browser

## Extending the IDE

### Adding New Lessons

Edit `src/LessonsPanel.cpp` and add entries to the `setupLessons()` and `getLessonContent()` methods:

```cpp
void LessonsPanel::setupLessons() {
    lessonsList->addItem("11. Your New Lesson");
}

QString LessonsPanel::getLessonContent(const QString &lessonName) {
    if (lessonName.contains("Your New Lesson")) {
        currentExampleCode = R"(// Your code here)";
        return "<h2>Your Lesson Title</h2><p>Content...</p>";
    }
}
```

### Adding New Challenges

Edit `src/ChallengesPanel.cpp` similarly:

```cpp
void ChallengesPanel::setupChallenges() {
    challengesList->addItem("Challenge 6: Your Challenge");
}
```

### Adding New Project Templates

Edit `src/ProjectManager.cpp` in the `getTemplateCode()` method:

```cpp
QString ProjectManager::getTemplateCode(const QString &templateName) {
    if (templateName == "Your Template") {
        return R"(// Template code)";
    }
}
```

### Modifying Syntax Highlighting

Edit `src/SyntaxHighlighter.cpp` to add new keywords or change colors:

```cpp
// Add new keywords
QStringList keywordPatterns = {
    "\\byour_keyword\\b",
    // ...
};

// Change colors
keywordFormat.setForeground(QColor(86, 156, 214));
```

## Keyboard Shortcuts

- **Ctrl+N** - New File
- **Ctrl+O** - Open File
- **Ctrl+S** - Save File
- **Ctrl+Shift+S** - Save As
- **Ctrl+Q** - Quit

## Beginner-Friendly Error Messages

The IDE translates common compiler errors into helpful hints:

- **undefined reference** → "Did you forget to define a function?"
- **expected ';'** → "Missing semicolon at the end of the previous line"
- **was not declared** → "Variable not declared. Did you forget to include a header?"
- **no matching function** → "Function call doesn't match any definition"

## Architecture

The IDE follows a modular design:

- **MainWindow**: Orchestrates all components
- **EditorWidget**: Custom text editor with line numbers
- **SyntaxHighlighter**: Real-time C++ syntax coloring
- **BuildSystem**: Manages compilation via QProcess
- **RunManager**: Executes compiled binaries
- **ProjectManager**: Handles project creation and templates
- **Panels**: Separate UI components for lessons, challenges, and docs

All components communicate via Qt signals/slots for loose coupling.

## Future Enhancements

Potential additions:

- Debugging support (gdb integration)
- Code formatting (clang-format)
- More lessons and challenges
- Export/import projects
- User progress tracking
- Interactive code validation
- Multi-file project support

## License

This project is open source and available for educational purposes.

## Contributing

To contribute:

1. Fork the repository
2. Create a feature branch
3. Add your changes
4. Test thoroughly
5. Submit a pull request

## Support

For issues or questions, please open an issue on the project repository.

---

**Happy Learning C++!** 🚀
