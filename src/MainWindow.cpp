#include "MainWindow.h"
#include "EditorWidget.h"
#include "BuildSystem.h"
#include "RunManager.h"
#include "ProjectManager.h"
#include "DocsPanel.h"
#include "LessonsPanel.h"
#include "ChallengesPanel.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QAction>
#include <QFile>
#include <QTextStream>
#include <QDir>

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
    setStatusBar(new QStatusBar(this));
}
