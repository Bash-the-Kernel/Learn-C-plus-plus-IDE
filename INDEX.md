# C++ Learning IDE - Project Index

## 📚 Documentation Files

### Start Here
- **[GETTING_STARTED.md](GETTING_STARTED.md)** - Complete setup and first-time user guide
- **[QUICKSTART.md](QUICKSTART.md)** - Quick reference for getting up and running
- **[README.md](README.md)** - Main project overview and features

### Technical Documentation
- **[ARCHITECTURE.md](ARCHITECTURE.md)** - System architecture and design patterns
- **[PROJECT_SUMMARY.md](PROJECT_SUMMARY.md)** - Complete project status and deliverables
- **[CONTRIBUTING.md](CONTRIBUTING.md)** - Guidelines for contributors

### Build Files
- **[CMakeLists.txt](CMakeLists.txt)** - CMake build configuration
- **[build.bat](build.bat)** - Windows build script
- **[build.sh](build.sh)** - Linux/macOS build script
- **[.gitignore](.gitignore)** - Git ignore rules

## 💻 Source Code

### Core Application (`src/`)

#### Main Entry Point
- **[main.cpp](src/main.cpp)** - Application entry point

#### Main Window
- **[MainWindow.h](src/MainWindow.h)** - Main window header
- **[MainWindow.cpp](src/MainWindow.cpp)** - Main window implementation
  - UI setup and layout
  - Menu and toolbar
  - File operations
  - Theme management

#### Code Editor
- **[EditorWidget.h](src/EditorWidget.h)** - Editor widget header
- **[EditorWidget.cpp](src/EditorWidget.cpp)** - Editor implementation
  - Line numbers
  - Current line highlighting
  - Custom text editing

#### Syntax Highlighting
- **[SyntaxHighlighter.h](src/SyntaxHighlighter.h)** - Highlighter header
- **[SyntaxHighlighter.cpp](src/SyntaxHighlighter.cpp)** - Highlighter implementation
  - C++ keyword highlighting
  - Type highlighting
  - Comment and string highlighting

#### Build System
- **[BuildSystem.h](src/BuildSystem.h)** - Build system header
- **[BuildSystem.cpp](src/BuildSystem.cpp)** - Build system implementation
  - Compiler integration
  - Error parsing
  - Friendly error messages

#### Run Manager
- **[RunManager.h](src/RunManager.h)** - Run manager header
- **[RunManager.cpp](src/RunManager.cpp)** - Run manager implementation
  - Program execution
  - Output capture

#### Project Management
- **[ProjectManager.h](src/ProjectManager.h)** - Project manager header
- **[ProjectManager.cpp](src/ProjectManager.cpp)** - Project manager implementation
  - Project creation
  - Template system

#### Educational Panels
- **[LessonsPanel.h](src/LessonsPanel.h)** - Lessons panel header
- **[LessonsPanel.cpp](src/LessonsPanel.cpp)** - Lessons implementation
  - Tutorial system
  - Code examples

- **[ChallengesPanel.h](src/ChallengesPanel.h)** - Challenges panel header
- **[ChallengesPanel.cpp](src/ChallengesPanel.cpp)** - Challenges implementation
  - Coding challenges
  - Hints system

- **[DocsPanel.h](src/DocsPanel.h)** - Documentation panel header
- **[DocsPanel.cpp](src/DocsPanel.cpp)** - Documentation implementation
  - External documentation links

## 📖 Learning Resources

### Lessons (`resources/lessons/`)
- **[lesson1.md](resources/lessons/lesson1.md)** - Hello World
- **[lesson2.md](resources/lessons/lesson2.md)** - Variables and Types
- **[lesson3.md](resources/lessons/lesson3.md)** - Input and Output

### Challenges (`resources/challenges/`)
- **[challenge1.md](resources/challenges/challenge1.md)** - Sum Two Numbers
- **[challenge2.md](resources/challenges/challenge2.md)** - Even or Odd
- **[challenge3.md](resources/challenges/challenge3.md)** - Factorial

### Templates (`resources/templates/`)
- **[hello_world.cpp](resources/templates/hello_world.cpp)** - Hello World template
- **[basic_io.cpp](resources/templates/basic_io.cpp)** - Basic I/O template

## 🗂️ Directory Structure

```
Learn-C-plus-plus-IDE/
├── 📄 Documentation
│   ├── README.md
│   ├── GETTING_STARTED.md
│   ├── QUICKSTART.md
│   ├── ARCHITECTURE.md
│   ├── PROJECT_SUMMARY.md
│   ├── CONTRIBUTING.md
│   └── INDEX.md (this file)
│
├── 🔧 Build Configuration
│   ├── CMakeLists.txt
│   ├── build.bat
│   ├── build.sh
│   └── .gitignore
│
├── 💻 Source Code (src/)
│   ├── main.cpp
│   ├── MainWindow.h/cpp
│   ├── EditorWidget.h/cpp
│   ├── SyntaxHighlighter.h/cpp
│   ├── BuildSystem.h/cpp
│   ├── RunManager.h/cpp
│   ├── ProjectManager.h/cpp
│   ├── LessonsPanel.h/cpp
│   ├── ChallengesPanel.h/cpp
│   └── DocsPanel.h/cpp
│
└── 📚 Resources (resources/)
    ├── lessons/
    │   ├── lesson1.md
    │   ├── lesson2.md
    │   └── lesson3.md
    ├── challenges/
    │   ├── challenge1.md
    │   ├── challenge2.md
    │   └── challenge3.md
    ├── templates/
    │   ├── hello_world.cpp
    │   └── basic_io.cpp
    └── icons/ (empty, for future use)
```

## 🎯 Quick Navigation by Task

### I want to...

#### Build the Project
→ See [GETTING_STARTED.md](GETTING_STARTED.md#building-the-ide)
→ Or run `build.bat` (Windows) or `build.sh` (Linux/macOS)

#### Understand the Architecture
→ Read [ARCHITECTURE.md](ARCHITECTURE.md)
→ Check [PROJECT_SUMMARY.md](PROJECT_SUMMARY.md#key-features-breakdown)

#### Add a New Lesson
→ See [CONTRIBUTING.md](CONTRIBUTING.md#adding-a-lesson)
→ Edit [LessonsPanel.cpp](src/LessonsPanel.cpp)

#### Add a New Challenge
→ See [CONTRIBUTING.md](CONTRIBUTING.md#adding-a-challenge)
→ Edit [ChallengesPanel.cpp](src/ChallengesPanel.cpp)

#### Modify Syntax Highlighting
→ See [CONTRIBUTING.md](CONTRIBUTING.md#adding-syntax-highlighting)
→ Edit [SyntaxHighlighter.cpp](src/SyntaxHighlighter.cpp)

#### Add Error Messages
→ See [CONTRIBUTING.md](CONTRIBUTING.md#adding-error-messages)
→ Edit [BuildSystem.cpp](src/BuildSystem.cpp)

#### Add Project Template
→ See [CONTRIBUTING.md](CONTRIBUTING.md#adding-a-template)
→ Edit [ProjectManager.cpp](src/ProjectManager.cpp)

#### Understand the UI Layout
→ Check [MainWindow.cpp](src/MainWindow.cpp) `setupUI()` method
→ Read [ARCHITECTURE.md](ARCHITECTURE.md#core-components)

#### Learn About the Editor
→ See [EditorWidget.cpp](src/EditorWidget.cpp)
→ Read [ARCHITECTURE.md](ARCHITECTURE.md#1-editor-editorwidget)

## 📊 File Statistics

### Source Code
- **Total Files:** 18 (.h and .cpp)
- **Lines of Code:** ~2,500+
- **Language:** C++20
- **Framework:** Qt 6

### Documentation
- **Total Files:** 7 markdown files
- **Total Words:** ~15,000+
- **Coverage:** Complete

### Resources
- **Lessons:** 3 (expandable to 10+)
- **Challenges:** 3 (expandable to 5+)
- **Templates:** 2 (expandable to 5+)

## 🔍 Component Dependencies

```
main.cpp
  └── MainWindow
      ├── EditorWidget
      │   └── SyntaxHighlighter
      ├── BuildSystem
      ├── RunManager
      ├── ProjectManager
      ├── LessonsPanel
      ├── ChallengesPanel
      └── DocsPanel
```

## 🚀 Getting Started Paths

### For Users
1. Read [GETTING_STARTED.md](GETTING_STARTED.md)
2. Build the project
3. Run the IDE
4. Start with Lesson 1

### For Developers
1. Read [ARCHITECTURE.md](ARCHITECTURE.md)
2. Review [PROJECT_SUMMARY.md](PROJECT_SUMMARY.md)
3. Check [CONTRIBUTING.md](CONTRIBUTING.md)
4. Explore source code in `src/`

### For Contributors
1. Read [CONTRIBUTING.md](CONTRIBUTING.md)
2. Set up development environment
3. Pick an area to contribute
4. Submit pull request

## 📝 Key Concepts

### Educational Features
- **Lessons:** Interactive tutorials with code examples
- **Challenges:** Coding exercises with hints
- **Friendly Errors:** Beginner-friendly compiler messages
- **Documentation:** Quick links to C++ reference

### Technical Features
- **Syntax Highlighting:** Real-time C++ code coloring
- **Line Numbers:** Custom line number area
- **Build System:** Integrated compiler support
- **Project Templates:** Quick-start code templates

## 🎓 Learning Resources in Order

1. **Lesson 1:** Hello World → [lesson1.md](resources/lessons/lesson1.md)
2. **Lesson 2:** Variables → [lesson2.md](resources/lessons/lesson2.md)
3. **Lesson 3:** Input/Output → [lesson3.md](resources/lessons/lesson3.md)
4. **Challenge 1:** Sum Numbers → [challenge1.md](resources/challenges/challenge1.md)
5. **Challenge 2:** Even/Odd → [challenge2.md](resources/challenges/challenge2.md)
6. **Challenge 3:** Factorial → [challenge3.md](resources/challenges/challenge3.md)

## 🔧 Build System Files

### CMake Configuration
- **[CMakeLists.txt](CMakeLists.txt)** - Main build configuration
  - Sets C++20 standard
  - Links Qt6 libraries
  - Copies resources

### Build Scripts
- **[build.bat](build.bat)** - Windows automated build
- **[build.sh](build.sh)** - Linux/macOS automated build

## 📦 External Dependencies

- **Qt 6.x** - GUI framework
- **CMake 3.16+** - Build system
- **g++/clang++** - C++ compiler

## 🎨 UI Components

### Main Window Layout
```
┌─────────────────────────────────────────────────┐
│ Menu Bar: File | Edit | View | Help             │
├─────────────────────────────────────────────────┤
│ Toolbar: [New] [Open] [Save] [Build] [Run]     │
├──────────┬──────────────────────┬───────────────┤
│          │                      │               │
│  File    │   Code Editor        │   Lessons     │
│ Explorer │   (with line #s)     │  Challenges   │
│          │                      │     Docs      │
│          ├──────────────────────┤               │
│          │   Output Panel       │               │
└──────────┴──────────────────────┴───────────────┘
```

## 🏆 Project Milestones

- ✅ Core IDE functionality
- ✅ Syntax highlighting
- ✅ Build system integration
- ✅ Educational content
- ✅ Documentation
- ✅ Cross-platform support

## 📞 Support

- **Issues:** Check documentation first
- **Questions:** See [GETTING_STARTED.md](GETTING_STARTED.md)
- **Contributions:** Read [CONTRIBUTING.md](CONTRIBUTING.md)

---

**Last Updated:** 2024
**Version:** 1.0.0
**Status:** ✅ Complete and Ready

This index provides a complete map of the C++ Learning IDE project. Use it to navigate and understand the codebase efficiently!
