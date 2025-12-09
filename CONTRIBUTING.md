# Contributing to C++ Learning IDE

Thank you for your interest in contributing! This document provides guidelines for contributing to the project.

## How to Contribute

### Reporting Bugs

1. Check if the bug has already been reported
2. Create a new issue with:
   - Clear title
   - Steps to reproduce
   - Expected vs actual behavior
   - Your environment (OS, Qt version, compiler)

### Suggesting Features

1. Check existing feature requests
2. Create an issue describing:
   - The problem it solves
   - Proposed solution
   - Why it benefits learners

### Contributing Code

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## Development Setup

### Prerequisites

- Qt 6.x
- CMake 3.16+
- C++20 compiler
- Git

### Building

```bash
git clone <repository-url>
cd Learn-C-plus-plus-IDE
mkdir build && cd build
cmake ..
make
```

## Code Style

### C++ Guidelines

- Use C++20 features
- Follow modern C++ best practices
- Use smart pointers (std::unique_ptr, std::shared_ptr)
- Prefer const correctness
- Use RAII for resource management

### Naming Conventions

```cpp
// Classes: PascalCase
class EditorWidget {};

// Functions/Methods: camelCase
void buildProject();

// Variables: camelCase
int lineNumber;

// Constants: UPPER_SNAKE_CASE
const int MAX_LINES = 1000;

// Private members: camelCase with m_ prefix
QString m_filePath;
```

### Code Formatting

- Indentation: 4 spaces
- Braces: Same line for functions, next line for classes
- Line length: Prefer < 100 characters
- Comments: Use // for single line, /* */ for multi-line

### Example

```cpp
class MyClass {
public:
    MyClass() = default;
    
    void doSomething() {
        if (condition) {
            // Do work
        }
    }

private:
    int m_value;
};
```

## Adding New Features

### Adding a Lesson

1. Edit `src/LessonsPanel.cpp`
2. Add to `setupLessons()`:
   ```cpp
   lessonsList->addItem("11. Your Lesson");
   ```
3. Add to `getLessonContent()`:
   ```cpp
   if (lessonName.contains("Your Lesson")) {
       currentExampleCode = R"(// code)";
       return "<h2>Title</h2><p>Content</p>";
   }
   ```
4. Optionally create `resources/lessons/lesson11.md`

### Adding a Challenge

1. Edit `src/ChallengesPanel.cpp`
2. Add to `setupChallenges()`:
   ```cpp
   challengesList->addItem("Challenge 6: Title");
   ```
3. Add to `getChallengeContent()`:
   ```cpp
   if (challengeName.contains("Title")) {
       currentChallengeCode = R"(// skeleton)";
       currentHint = "Hint text";
       return "<h2>Challenge</h2><p>Description</p>";
   }
   ```
4. Create `resources/challenges/challenge6.md`

### Adding a Template

1. Edit `src/ProjectManager.cpp`
2. Add to `getTemplateCode()`:
   ```cpp
   if (templateName == "New Template") {
       return R"(// template code)";
   }
   ```
3. Update UI to include new template option

### Adding Syntax Highlighting

1. Edit `src/SyntaxHighlighter.cpp`
2. Add patterns to constructor:
   ```cpp
   QStringList newPatterns = {"\\bkeyword\\b"};
   for (const QString &pattern : newPatterns) {
       rule.pattern = QRegularExpression(pattern);
       rule.format = yourFormat;
       highlightingRules.append(rule);
   }
   ```

### Adding Error Messages

1. Edit `src/BuildSystem.cpp`
2. Add to `parseFriendlyError()`:
   ```cpp
   if (error.contains("pattern")) {
       friendly += "\n💡 Friendly hint: Explanation";
   }
   ```

## Testing

### Manual Testing

1. Build the IDE
2. Test your feature thoroughly
3. Try edge cases
4. Test on different platforms if possible

### Test Checklist

- [ ] Feature works as expected
- [ ] No crashes or memory leaks
- [ ] UI is responsive
- [ ] Error handling works
- [ ] Documentation updated
- [ ] Code follows style guide

## Documentation

### Code Comments

- Document public APIs
- Explain complex logic
- Use Doxygen-style comments for classes

```cpp
/**
 * @brief Builds the C++ source file
 * @param sourceFile Path to the source file
 */
void build(const QString &sourceFile);
```

### User Documentation

- Update README.md if needed
- Add to QUICKSTART.md for user-facing features
- Update ARCHITECTURE.md for structural changes

## Pull Request Process

1. **Create PR** with clear title and description
2. **Link Issues** that the PR addresses
3. **Describe Changes** - what and why
4. **Test Results** - what you tested
5. **Screenshots** - for UI changes
6. **Wait for Review** - address feedback

### PR Template

```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Documentation update
- [ ] Code refactoring

## Testing
How you tested the changes

## Screenshots
If applicable

## Checklist
- [ ] Code follows style guide
- [ ] Documentation updated
- [ ] Tested thoroughly
```

## Areas for Contribution

### High Priority

- More lessons and challenges
- Better error message translations
- Cross-platform testing
- Performance improvements

### Medium Priority

- Additional project templates
- More syntax highlighting rules
- UI/UX improvements
- Accessibility features

### Future Features

- Debugging support
- Code formatting integration
- Multi-file project support
- User progress tracking
- Export/import functionality

## Community Guidelines

- Be respectful and inclusive
- Help beginners learn
- Provide constructive feedback
- Focus on education value
- Keep it simple for learners

## Questions?

- Open an issue for questions
- Tag with "question" label
- Check existing discussions

## License

By contributing, you agree that your contributions will be licensed under the same license as the project.

---

Thank you for helping make C++ learning better for everyone! 🎓
