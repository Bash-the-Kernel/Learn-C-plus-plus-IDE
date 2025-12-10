#include "MainWindow.h"
#include "EditorWidget.h"
#include "BuildSystem.h"
#include "RunManager.h"
#include "ProjectManager.h"
#include "DocsPanel.h"
#include "LessonsPanel.h"
#include "ChallengesPanel.h"
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QAction>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QKeyEvent>
#include <QLabel>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), isDarkTheme(true), currentEditor(nullptr) {
    
    buildSystem = std::make_unique<BuildSystem>();
    runManager = std::make_unique<RunManager>();
    projectManager = std::make_unique<ProjectManager>();
    
    setupUI();
    setupMenuBar();
    setupToolBar();
    
    connect(buildSystem.get(), &BuildSystem::outputReceived, this, &MainWindow::onBuildOutput);
    connect(runManager.get(), &RunManager::outputReceived, this, &MainWindow::onRunOutput);
    
    applyDarkTheme();
    resize(1400, 900);
}

MainWindow::~MainWindow() = default;

void MainWindow::setupUI() {
    mainSplitter = new QSplitter(Qt::Horizontal, this);
    
    setupFileExplorer();
    setupEditor();
    setupOutputPanel();
    setupSidePanels();
    
    leftSplitter = new QSplitter(Qt::Vertical);
    leftSplitter->addWidget(fileExplorer);
    leftSplitter->setStretchFactor(0, 1);
    
    rightSplitter = new QSplitter(Qt::Vertical);
    rightSplitter->addWidget(editorTabs);
    rightSplitter->addWidget(outputPanel);
    rightSplitter->setStretchFactor(0, 3);
    rightSplitter->setStretchFactor(1, 1);
    
    mainSplitter->addWidget(leftSplitter);
    mainSplitter->addWidget(rightSplitter);
    mainSplitter->addWidget(sidePanelTabs);
    mainSplitter->setStretchFactor(0, 1);
    mainSplitter->setStretchFactor(1, 4);
    mainSplitter->setStretchFactor(2, 1);
    
    setCentralWidget(mainSplitter);
    
    // Setup status bar with cursor position
    setStatusBar(new QStatusBar(this));
    cursorPositionLabel = new QLabel("Line: 1, Column: 1");
    statusBar()->addPermanentWidget(cursorPositionLabel);
}

void MainWindow::setupMenuBar() {
    QMenu *fileMenu = menuBar()->addMenu("&File");
    
    QAction *newFileAction = fileMenu->addAction("&New File");
    newFileAction->setShortcut(QKeySequence::New);
    connect(newFileAction, &QAction::triggered, this, &MainWindow::newFile);
    
    QAction *openFileAction = fileMenu->addAction("&Open File");
    openFileAction->setShortcut(QKeySequence::Open);
    connect(openFileAction, &QAction::triggered, this, &MainWindow::openFile);
    
    fileMenu->addSeparator();
    
    recentFilesMenu = fileMenu->addMenu("Recent Files");
    recentFilesMenu->setEnabled(false);
    
    QAction *saveAction = fileMenu->addAction("&Save");
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    
    QAction *saveAsAction = fileMenu->addAction("Save &As...");
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveFileAs);
    
    fileMenu->addSeparator();
    
    QAction *newProjectAction = fileMenu->addAction("New &Project...");
    connect(newProjectAction, &QAction::triggered, this, &MainWindow::newProject);
    
    QAction *openProjectAction = fileMenu->addAction("Open P&roject...");
    connect(openProjectAction, &QAction::triggered, this, &MainWindow::openProject);
    
    fileMenu->addSeparator();
    
    QAction *exitAction = fileMenu->addAction("E&xit");
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    
    QMenu *editMenu = menuBar()->addMenu("&Edit");
    QAction *undoAction = editMenu->addAction("&Undo");
    undoAction->setShortcut(QKeySequence::Undo);
    
    QAction *redoAction = editMenu->addAction("&Redo");
    redoAction->setShortcut(QKeySequence::Redo);
    
    editMenu->addSeparator();
    
    QAction *findAction = editMenu->addAction("&Find...");
    findAction->setShortcut(QKeySequence::Find);
    connect(findAction, &QAction::triggered, [this]() {
        if (currentEditor) currentEditor->showFindDialog();
    });
    
    QAction *replaceAction = editMenu->addAction("&Replace...");
    replaceAction->setShortcut(QKeySequence::Replace);
    connect(replaceAction, &QAction::triggered, [this]() {
        if (currentEditor) currentEditor->showReplaceDialog();
    });
    
    QAction *goToLineAction = editMenu->addAction("&Go to Line...");
    goToLineAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_G));
    connect(goToLineAction, &QAction::triggered, [this]() {
        if (currentEditor) currentEditor->showGoToLineDialog();
    });
    
    QMenu *viewMenu = menuBar()->addMenu("&View");
    QAction *themeAction = viewMenu->addAction("Toggle &Theme");
    connect(themeAction, &QAction::triggered, this, &MainWindow::toggleTheme);
    
    QMenu *helpMenu = menuBar()->addMenu("&Help");
    QAction *aboutAction = helpMenu->addAction("&About");
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
}

void MainWindow::setupToolBar() {
    QToolBar *toolbar = addToolBar("Main Toolbar");
    toolbar->setMovable(false);
    
    QAction *newFileBtn = toolbar->addAction("New File");
    connect(newFileBtn, &QAction::triggered, this, &MainWindow::newFile);
    
    QAction *openFileBtn = toolbar->addAction("Open File");
    connect(openFileBtn, &QAction::triggered, this, &MainWindow::openFile);
    
    QAction *saveBtn = toolbar->addAction("Save");
    connect(saveBtn, &QAction::triggered, this, &MainWindow::saveFile);
    
    toolbar->addSeparator();
    
    QAction *newProjectBtn = toolbar->addAction("New Project");
    connect(newProjectBtn, &QAction::triggered, this, &MainWindow::newProject);
    
    toolbar->addSeparator();
    
    QAction *buildBtn = toolbar->addAction("Build");
    connect(buildBtn, &QAction::triggered, this, &MainWindow::buildProject);
    
    QAction *runBtn = toolbar->addAction("Run");
    connect(runBtn, &QAction::triggered, this, &MainWindow::runProject);
}

void MainWindow::setupFileExplorer() {
    fileExplorer = new QTreeView(this);
    fileModel = new QFileSystemModel(this);
    fileModel->setRootPath(QDir::homePath());
    fileExplorer->setModel(fileModel);
    fileExplorer->setRootIndex(fileModel->index(QDir::homePath()));
    fileExplorer->setColumnWidth(0, 200);
    fileExplorer->setHeaderHidden(false);
    
    connect(fileExplorer, &QTreeView::doubleClicked, [this](const QModelIndex &index) {
        QString filePath = fileModel->filePath(index);
        if (QFileInfo(filePath).isFile()) {
            loadFile(filePath);
        }
    });
}

void MainWindow::setupEditor() {
    editorTabs = new QTabWidget(this);
    editorTabs->setTabsClosable(true);
    editorTabs->setMovable(true);
    editorTabs->setContextMenuPolicy(Qt::CustomContextMenu);
    
    connect(editorTabs, &QTabWidget::tabCloseRequested, [this](int index) {
        QWidget *widget = editorTabs->widget(index);
        editorTabs->removeTab(index);
        delete widget;
        if (editorTabs->count() == 0) {
            currentEditor = nullptr;
            cursorPositionLabel->setText("Line: 1, Column: 1");
        }
    });
    
    connect(editorTabs, &QTabWidget::currentChanged, [this](int index) {
        if (index >= 0) {
            currentEditor = qobject_cast<EditorWidget*>(editorTabs->widget(index));
            if (currentEditor) {
                connect(currentEditor, &EditorWidget::cursorPositionUpdated, 
                       this, &MainWindow::onCursorPositionUpdated, Qt::UniqueConnection);
                connect(currentEditor, &EditorWidget::modificationChanged,
                       this, &MainWindow::onModificationChanged, Qt::UniqueConnection);
            }
        } else {
            currentEditor = nullptr;
        }
    });
    
    connect(editorTabs, &QTabWidget::customContextMenuRequested, 
           this, &MainWindow::onTabContextMenu);
}

void MainWindow::setupOutputPanel() {
    outputPanel = new QTextEdit(this);
    outputPanel->setReadOnly(true);
    outputPanel->setPlaceholderText("Build and run output will appear here...");
}

void MainWindow::setupSidePanels() {
    sidePanelTabs = new QTabWidget(this);
    
    docsPanel = new DocsPanel(this);
    lessonsPanel = new LessonsPanel(this);
    challengesPanel = new ChallengesPanel(this);
    
    sidePanelTabs->addTab(lessonsPanel, "Lessons");
    sidePanelTabs->addTab(challengesPanel, "Challenges");
    sidePanelTabs->addTab(docsPanel, "Docs");
    
    connect(lessonsPanel, &LessonsPanel::loadCodeExample, [this](const QString &code) {
        EditorWidget *editor = new EditorWidget(this);
        editor->setPlainText(code);
        int index = editorTabs->addTab(editor, "example.cpp");
        editorTabs->setCurrentIndex(index);
        currentEditor = editor;
    });
    
    connect(challengesPanel, &ChallengesPanel::loadChallenge, [this](const QString &code) {
        EditorWidget *editor = new EditorWidget(this);
        editor->setPlainText(code);
        int index = editorTabs->addTab(editor, "challenge.cpp");
        editorTabs->setCurrentIndex(index);
        currentEditor = editor;
    });
}

void MainWindow::newFile() {
    EditorWidget *editor = new EditorWidget(this);
    int index = editorTabs->addTab(editor, "untitled.cpp");
    editorTabs->setCurrentIndex(index);
    currentEditor = editor;
    
    connect(editor, &EditorWidget::cursorPositionUpdated, 
           this, &MainWindow::onCursorPositionUpdated);
    connect(editor, &EditorWidget::modificationChanged,
           this, &MainWindow::onModificationChanged);
}

void MainWindow::openFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", QDir::homePath(),
                                                     "C++ Files (*.cpp *.h *.hpp *.cc *.cxx);;All Files (*)");
    if (!filePath.isEmpty()) {
        loadFile(filePath);
    }
}

void MainWindow::loadFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open file: " + filePath);
        return;
    }
    
    QTextStream in(&file);
    QString content = in.readAll();
    file.close();
    
    EditorWidget *editor = new EditorWidget(this);
    editor->setPlainText(content);
    editor->setFilePath(filePath);
    editor->setModified(false);
    
    connect(editor, &EditorWidget::cursorPositionUpdated, 
           this, &MainWindow::onCursorPositionUpdated);
    connect(editor, &EditorWidget::modificationChanged,
           this, &MainWindow::onModificationChanged);
    
    QFileInfo fileInfo(filePath);
    int index = editorTabs->addTab(editor, fileInfo.fileName());
    editorTabs->setCurrentIndex(index);
    currentEditor = editor;
    currentFilePath = filePath;
    
    // Add to recent files
    recentFiles.removeAll(filePath);
    recentFiles.prepend(filePath);
    if (recentFiles.size() > 10) recentFiles.removeLast();
    updateRecentFilesMenu();
    
    statusBar()->showMessage("Opened: " + filePath, 3000);
}

void MainWindow::saveFile() {
    if (!currentEditor) return;
    
    QString filePath = currentEditor->filePath();
    if (filePath.isEmpty()) {
        saveFileAs();
        return;
    }
    
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not save file: " + filePath);
        return;
    }
    
    QTextStream out(&file);
    out << currentEditor->toPlainText();
    file.close();
    
    statusBar()->showMessage("Saved: " + filePath, 3000);
}

void MainWindow::saveFileAs() {
    if (!currentEditor) return;
    
    QString filePath = QFileDialog::getSaveFileName(this, "Save File As", QDir::homePath(),
                                                     "C++ Files (*.cpp *.h *.hpp);;All Files (*)");
    if (filePath.isEmpty()) return;
    
    currentEditor->setFilePath(filePath);
    QFileInfo fileInfo(filePath);
    editorTabs->setTabText(editorTabs->currentIndex(), fileInfo.fileName());
    saveFile();
}

void MainWindow::openProject() {
    QString dirPath = QFileDialog::getExistingDirectory(this, "Open Project", QDir::homePath());
    if (!dirPath.isEmpty()) {
        projectManager->setProjectPath(dirPath);
        fileExplorer->setRootIndex(fileModel->index(dirPath));
        statusBar()->showMessage("Opened project: " + dirPath, 3000);
    }
}

void MainWindow::newProject() {
    QString dirPath = QFileDialog::getExistingDirectory(this, "Select Project Directory", QDir::homePath());
    if (dirPath.isEmpty()) return;
    
    QStringList templates = {"Hello World", "Basic IO", "Loops & Conditionals", "Classes & Objects", "Vectors & Strings"};
    bool ok;
    QString templateName = QMessageBox::question(this, "Select Template", 
                                                  "Choose a project template:", 
                                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes 
                           ? templates[0] : "";
    
    projectManager->createProject(dirPath, templateName);
    fileExplorer->setRootIndex(fileModel->index(dirPath));
    
    QString mainFile = dirPath + "/main.cpp";
    if (QFile::exists(mainFile)) {
        loadFile(mainFile);
    }
    
    statusBar()->showMessage("Created project: " + dirPath, 3000);
}

void MainWindow::buildProject() {
    if (!currentEditor) {
        outputPanel->append("No file open to build.");
        return;
    }
    
    saveFile();
    outputPanel->clear();
    outputPanel->append("=== Building ===");
    
    QString filePath = currentEditor->filePath();
    if (filePath.isEmpty()) {
        outputPanel->append("Error: File not saved. Please save before building.");
        return;
    }
    
    buildSystem->build(filePath);
}

void MainWindow::runProject() {
    if (!currentEditor) {
        outputPanel->append("No file to run.");
        return;
    }
    
    QString filePath = currentEditor->filePath();
    if (filePath.isEmpty()) {
        outputPanel->append("Error: File not saved. Please save before running.");
        return;
    }
    
    outputPanel->append("\n=== Running ===");
    runManager->run(filePath);
}

void MainWindow::onBuildOutput(const QString &output, bool isError) {
    if (isError) {
        outputPanel->setTextColor(Qt::red);
        outputPanel->append(buildSystem->parseFriendlyError(output));
        outputPanel->setTextColor(isDarkTheme ? Qt::white : Qt::black);
    } else {
        outputPanel->append(output);
    }
}

void MainWindow::onRunOutput(const QString &output) {
    outputPanel->append(output);
}

void MainWindow::toggleTheme() {
    isDarkTheme = !isDarkTheme;
    if (isDarkTheme) {
        applyDarkTheme();
    } else {
        applyLightTheme();
    }
}

void MainWindow::applyDarkTheme() {
    qobject_cast<QApplication*>(qApp)->setStyleSheet(R"(
        QMainWindow, QWidget { background-color: #1e1e1e; color: #d4d4d4; }
        QTextEdit, QPlainTextEdit { background-color: #252526; color: #d4d4d4; border: 1px solid #3e3e42; }
        QTreeView { background-color: #252526; color: #d4d4d4; border: 1px solid #3e3e42; }
        QTabWidget::pane { border: 1px solid #3e3e42; }
        QTabBar::tab { background-color: #2d2d30; color: #d4d4d4; padding: 8px 16px; }
        QTabBar::tab:selected { background-color: #1e1e1e; }
        QMenuBar { background-color: #2d2d30; color: #d4d4d4; }
        QMenuBar::item:selected { background-color: #3e3e42; }
        QMenu { background-color: #252526; color: #d4d4d4; border: 1px solid #3e3e42; }
        QMenu::item:selected { background-color: #3e3e42; }
        QToolBar { background-color: #2d2d30; border: none; spacing: 5px; }
        QStatusBar { background-color: #007acc; color: white; }
    )");
}

void MainWindow::applyLightTheme() {
    qobject_cast<QApplication*>(qApp)->setStyleSheet(R"(
        QMainWindow, QWidget { background-color: #ffffff; color: #000000; }
        QTextEdit, QPlainTextEdit { background-color: #ffffff; color: #000000; border: 1px solid #cccccc; }
        QTreeView { background-color: #ffffff; color: #000000; border: 1px solid #cccccc; }
        QTabWidget::pane { border: 1px solid #cccccc; }
        QTabBar::tab { background-color: #f3f3f3; color: #000000; padding: 8px 16px; }
        QTabBar::tab:selected { background-color: #ffffff; }
        QMenuBar { background-color: #f3f3f3; color: #000000; }
        QMenuBar::item:selected { background-color: #e5e5e5; }
        QMenu { background-color: #ffffff; color: #000000; border: 1px solid #cccccc; }
        QMenu::item:selected { background-color: #e5e5e5; }
        QToolBar { background-color: #f3f3f3; border: none; spacing: 5px; }
        QStatusBar { background-color: #007acc; color: white; }
    )");
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->modifiers() & Qt::ControlModifier) {
        if (event->key() == Qt::Key_Tab) {
            // Cycle through tabs
            int currentIndex = editorTabs->currentIndex();
            int nextIndex = (currentIndex + 1) % editorTabs->count();
            if (editorTabs->count() > 0) {
                editorTabs->setCurrentIndex(nextIndex);
            }
            return;
        }
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::onTabContextMenu(const QPoint &pos) {
    int tabIndex = editorTabs->tabBar()->tabAt(pos);
    if (tabIndex < 0) return;
    
    QMenu contextMenu(this);
    contextMenu.addAction("Close", [this, tabIndex]() {
        QWidget *widget = editorTabs->widget(tabIndex);
        editorTabs->removeTab(tabIndex);
        delete widget;
    });
    contextMenu.addAction("Close Others", this, &MainWindow::closeOtherTabs);
    contextMenu.addAction("Close All", this, &MainWindow::closeAllTabs);
    
    contextMenu.exec(editorTabs->tabBar()->mapToGlobal(pos));
}

void MainWindow::closeCurrentTab() {
    int index = editorTabs->currentIndex();
    if (index >= 0) {
        QWidget *widget = editorTabs->widget(index);
        editorTabs->removeTab(index);
        delete widget;
    }
}

void MainWindow::closeOtherTabs() {
    int currentIndex = editorTabs->currentIndex();
    for (int i = editorTabs->count() - 1; i >= 0; --i) {
        if (i != currentIndex) {
            QWidget *widget = editorTabs->widget(i);
            editorTabs->removeTab(i);
            delete widget;
        }
    }
}

void MainWindow::closeAllTabs() {
    while (editorTabs->count() > 0) {
        QWidget *widget = editorTabs->widget(0);
        editorTabs->removeTab(0);
        delete widget;
    }
    currentEditor = nullptr;
}

void MainWindow::onCursorPositionUpdated(int line, int column) {
    cursorPositionLabel->setText(QString("Line: %1, Column: %2").arg(line).arg(column));
}

void MainWindow::onModificationChanged() {
    EditorWidget *editor = qobject_cast<EditorWidget*>(sender());
    if (!editor) return;
    
    int index = editorTabs->indexOf(editor);
    if (index >= 0) {
        QString tabText = editorTabs->tabText(index);
        if (editor->isModified()) {
            if (!tabText.endsWith("*")) {
                editorTabs->setTabText(index, tabText + "*");
            }
        } else {
            if (tabText.endsWith("*")) {
                editorTabs->setTabText(index, tabText.chopped(1));
            }
        }
    }
}

void MainWindow::updateRecentFilesMenu() {
    recentFilesMenu->clear();
    recentFilesMenu->setEnabled(!recentFiles.isEmpty());
    
    for (const QString &filePath : recentFiles) {
        QAction *action = recentFilesMenu->addAction(QFileInfo(filePath).fileName());
        action->setToolTip(filePath);
        connect(action, &QAction::triggered, [this, filePath]() {
            loadFile(filePath);
        });
    }
}

void MainWindow::showAbout() {
    QMessageBox::about(this, "About C++ Learning IDE",
                       "C++ Learning IDE v1.0\n\n"
                       "A beginner-friendly IDE for learning C++\n"
                       "Built with Qt 6 and C++20\n\n"
                       "Features:\n"
                       "• Code folding (Ctrl+Shift+[/])\n"
                       "• Bracket matching and auto-close\n"
                       "• Go to line (Ctrl+G)\n"
                       "• Find/Replace (Ctrl+F/H)\n"
                       "• Enhanced tabs with context menu");
}
