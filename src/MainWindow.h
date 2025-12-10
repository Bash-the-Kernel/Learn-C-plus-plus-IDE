#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QTabWidget>
#include <QTextEdit>
#include <QTreeView>
#include <QFileSystemModel>
#include <QToolBar>
#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>
#include <QMenu>
#include <memory>

class EditorWidget;
class BuildSystem;
class RunManager;
class ProjectManager;
class DocsPanel;
class LessonsPanel;
class ChallengesPanel;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void openProject();
    void newProject();
    void buildProject();
    void runProject();
    void toggleTheme();
    void showAbout();
    void onBuildOutput(const QString &output, bool isError);
    void onRunOutput(const QString &output);
    void onTabContextMenu(const QPoint &pos);
    void closeCurrentTab();
    void closeOtherTabs();
    void closeAllTabs();
    void onCursorPositionUpdated(int line, int column);
    void onModificationChanged();

private:
    void setupUI();
    void setupMenuBar();
    void setupToolBar();
    void setupFileExplorer();
    void setupEditor();
    void setupOutputPanel();
    void setupSidePanels();
    void applyDarkTheme();
    void applyLightTheme();
    void loadFile(const QString &filePath);
    void updateRecentFilesMenu();

    QSplitter *mainSplitter;
    QSplitter *leftSplitter;
    QSplitter *rightSplitter;
    
    QTreeView *fileExplorer;
    QFileSystemModel *fileModel;
    
    QTabWidget *editorTabs;
    EditorWidget *currentEditor;
    
    QTextEdit *outputPanel;
    QTabWidget *sidePanelTabs;
    
    DocsPanel *docsPanel;
    LessonsPanel *lessonsPanel;
    ChallengesPanel *challengesPanel;
    
    std::unique_ptr<BuildSystem> buildSystem;
    std::unique_ptr<RunManager> runManager;
    std::unique_ptr<ProjectManager> projectManager;
    
    bool isDarkTheme;
    QString currentFilePath;
    
    QLabel *cursorPositionLabel;
    QStringList recentFiles;
    QMenu *recentFilesMenu;
};

#endif
