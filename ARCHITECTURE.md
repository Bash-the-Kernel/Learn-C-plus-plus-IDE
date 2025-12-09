# Architecture Documentation

## Overview

The C++ Learning IDE follows a modular, component-based architecture using Qt 6 framework with C++20.

## Core Components

### 1. MainWindow (MainWindow.h/cpp)

**Responsibility:** Central orchestrator of the application

**Key Features:**
- Manages UI layout with splitters
- Coordinates between all components
- Handles menu and toolbar actions
- Manages theme switching
- File operations (new, open, save)

**Signals/Slots:**
- Receives build output from BuildSystem
- Receives run output from RunManager
- Sends code to editor from panels

### 2. EditorWidget (EditorWidget.h/cpp)

**Responsibility:** Custom code editor with C++ features

**Key Features:**
- Line number display
- Current line highlighting
- Syntax highlighting integration
- File path tracking
- Tab stop configuration

**Implementation:**
- Extends QPlainTextEdit
- Uses custom LineNumberArea widget
- Integrates with SyntaxHighlighter

### 3. SyntaxHighlighter (SyntaxHighlighter.h/cpp)

**Responsibility:** Real-time C++ syntax coloring

**Key Features:**
- Keywords highlighting (if, for, class, etc.)
- Type highlighting (int, double, vector, etc.)
- String and character literals
- Single and multi-line comments
- Preprocessor directives
- Number literals

**Implementation:**
- Extends QSyntaxHighlighter
- Uses QRegularExpression for pattern matching
- Configurable color schemes

### 4. BuildSystem (BuildSystem.h/cpp)

**Responsibility:** Compiler integration and build management

**Key Features:**
- Detects available compiler (clang++ or g++)
- Compiles C++ source files
- Parses compiler output
- Provides beginner-friendly error messages
- Emits build status signals

**Error Translation Examples:**
- "undefined reference" → Helpful explanation
- "expected ';'" → Points to likely location
- "was not declared" → Suggests solutions

### 5. RunManager (RunManager.h/cpp)

**Responsibility:** Execute compiled programs

**Key Features:**
- Locates compiled executable
- Runs program via QProcess
- Captures stdout and stderr
- Reports exit codes
- Cross-platform executable detection

### 6. ProjectManager (ProjectManager.h/cpp)

**Responsibility:** Project creation and templates

**Key Features:**
- Creates new projects from templates
- Generates CMakeLists.txt
- Provides 5 starter templates
- Manages project paths

**Templates:**
1. Hello World
2. Basic IO
3. Loops & Conditionals
4. Classes & Objects
5. Vectors & Strings

### 7. LessonsPanel (LessonsPanel.h/cpp)

**Responsibility:** Interactive tutorial system

**Key Features:**
- Displays lesson list
- Shows lesson content in HTML
- Provides code examples
- Loads examples into editor

**Extensibility:**
- Easy to add new lessons
- Supports rich HTML content
- Can load external lesson files

### 8. ChallengesPanel (ChallengesPanel.h/cpp)

**Responsibility:** Coding challenges with hints

**Key Features:**
- Lists available challenges
- Shows challenge descriptions
- Provides skeleton code
- Offers hints
- Loads challenges into editor

**Challenge Structure:**
- Description
- Requirements
- Expected output
- Skeleton code
- Hints

### 9. DocsPanel (DocsPanel.h/cpp)

**Responsibility:** Quick access to C++ documentation

**Key Features:**
- Links to cppreference.com
- Categorized documentation
- Opens in system browser

**Categories:**
- C++ Reference Home
- Input/Output Library
- Containers
- Algorithms
- Strings
- Memory Management
- Classes
- Functions

## Data Flow

### Build Flow
```
User clicks Build
    ↓
MainWindow::buildProject()
    ↓
BuildSystem::build()
    ↓
QProcess executes compiler
    ↓
BuildSystem::outputReceived signal
    ↓
MainWindow::onBuildOutput()
    ↓
Output displayed in panel
```

### Run Flow
```
User clicks Run
    ↓
MainWindow::runProject()
    ↓
RunManager::run()
    ↓
QProcess executes binary
    ↓
RunManager::outputReceived signal
    ↓
MainWindow::onRunOutput()
    ↓
Output displayed in panel
```

### Lesson Flow
```
User selects lesson
    ↓
LessonsPanel::onLessonSelected()
    ↓
Display lesson content
    ↓
User clicks "Load Example"
    ↓
LessonsPanel::loadCodeExample signal
    ↓
MainWindow receives signal
    ↓
Code inserted into current editor
```

## Design Patterns

### 1. Observer Pattern
- Qt signals/slots for component communication
- Loose coupling between components

### 2. Strategy Pattern
- Different syntax highlighting rules
- Multiple project templates

### 3. Facade Pattern
- MainWindow provides simplified interface
- Hides complexity of subsystems

### 4. Factory Pattern
- ProjectManager creates projects from templates
- Template selection creates appropriate code

## Threading Model

- **Main Thread:** All UI operations
- **QProcess:** Separate process for compilation and execution
- **No explicit threading:** Qt handles process management

## Memory Management

- **Smart Pointers:** std::unique_ptr for owned objects
- **Qt Parent-Child:** Automatic cleanup of widgets
- **RAII:** Resource acquisition in constructors

## Extension Points

### Adding New Features

1. **New Lesson:**
   - Edit LessonsPanel::setupLessons()
   - Add content in getLessonContent()

2. **New Challenge:**
   - Edit ChallengesPanel::setupChallenges()
   - Add content in getChallengeContent()

3. **New Template:**
   - Edit ProjectManager::getTemplateCode()
   - Add template name to UI

4. **New Syntax Rules:**
   - Edit SyntaxHighlighter constructor
   - Add patterns and formats

5. **New Error Messages:**
   - Edit BuildSystem::parseFriendlyError()
   - Add pattern matching and hints

## File Organization

```
src/
├── main.cpp              # Entry point
├── MainWindow.*          # Main window
├── EditorWidget.*        # Code editor
├── SyntaxHighlighter.*   # Syntax coloring
├── BuildSystem.*         # Compilation
├── RunManager.*          # Execution
├── ProjectManager.*      # Projects
├── DocsPanel.*           # Documentation
├── LessonsPanel.*        # Tutorials
└── ChallengesPanel.*     # Challenges
```

## Dependencies

- **Qt6::Core** - Core Qt functionality
- **Qt6::Widgets** - GUI widgets
- **System Compiler** - g++ or clang++

## Build System

- **CMake 3.16+** - Build configuration
- **AUTOMOC** - Meta-object compilation
- **AUTORCC** - Resource compilation
- **AUTOUIC** - UI file compilation

## Future Architecture Considerations

### Potential Additions

1. **Plugin System:**
   - Dynamic loading of lessons
   - Custom syntax highlighters
   - Third-party integrations

2. **Debugging Layer:**
   - GDB integration
   - Breakpoint management
   - Variable inspection

3. **Code Analysis:**
   - Static analysis integration
   - Code metrics
   - Complexity warnings

4. **Persistence Layer:**
   - User progress tracking
   - Settings management
   - Recent files

5. **Network Layer:**
   - Online lesson updates
   - Community challenges
   - Code sharing

## Performance Considerations

- **Syntax Highlighting:** Incremental updates only
- **File Loading:** Lazy loading of large files
- **Process Management:** Non-blocking execution
- **UI Updates:** Throttled output updates

## Security Considerations

- **Code Execution:** Runs in user context
- **File Access:** Limited to user permissions
- **No Network:** Offline by default
- **No Eval:** No dynamic code evaluation

---

This architecture provides a solid foundation for a beginner-friendly C++ learning environment while remaining extensible for future enhancements.
