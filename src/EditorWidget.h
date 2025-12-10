#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QPlainTextEdit>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QTextBlock>
#include <QInputDialog>

class SyntaxHighlighter;
class LineNumberArea;
class FindReplaceDialog;

class EditorWidget : public QPlainTextEdit {
    Q_OBJECT

public:
    explicit EditorWidget(QWidget *parent = nullptr);
    
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    
    QString filePath() const { return m_filePath; }
    void setFilePath(const QString &path) { m_filePath = path; }
    
    void showFindDialog();
    void showReplaceDialog();
    void showGoToLineDialog();
    
    bool isModified() const { return document()->isModified(); }
    void setModified(bool modified) { document()->setModified(modified); }
    
    void toggleFold(int line);
    bool isBlockFolded(int blockNumber) const;
    
    // Public accessors for LineNumberArea
    QTextBlock getFirstVisibleBlock() const { return firstVisibleBlock(); }
    QRectF getBlockBoundingGeometry(const QTextBlock &block) const { return blockBoundingGeometry(block); }
    QPointF getContentOffset() const { return contentOffset(); }
    QRectF getBlockBoundingRect(const QTextBlock &block) const { return blockBoundingRect(block); }

signals:
    void modificationChanged(bool changed);
    void cursorPositionUpdated(int line, int column);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);
    void onCursorPositionChanged();
    void onModificationChanged(bool changed);

private:
    void highlightMatchingBrackets();
    void autoCloseBrackets(QKeyEvent *event);
    int findMatchingBracket(int position, QChar openBracket, QChar closeBracket, bool forward);
    
    SyntaxHighlighter *highlighter;
    QWidget *lineNumberArea;
    QString m_filePath;
    FindReplaceDialog *findReplaceDialog;
    
    QSet<int> foldedBlocks;
    QList<QTextEdit::ExtraSelection> bracketSelections;
};

class FindReplaceDialog : public QDialog {
    Q_OBJECT

public:
    explicit FindReplaceDialog(EditorWidget *editor, QWidget *parent = nullptr);
    void showFind();
    void showReplace();

private slots:
    void findNext();
    void findPrevious();
    void replace();
    void replaceAll();

private:
    EditorWidget *editor;
    QLineEdit *findLineEdit;
    QLineEdit *replaceLineEdit;
    QPushButton *findNextBtn;
    QPushButton *findPrevBtn;
    QPushButton *replaceBtn;
    QPushButton *replaceAllBtn;
    QCheckBox *caseSensitiveBox;
    QCheckBox *wholeWordsBox;
};

class LineNumberArea : public QWidget {
public:
    LineNumberArea(EditorWidget *editor) : QWidget(editor), codeEditor(editor) {}
    
    QSize sizeHint() const override {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        codeEditor->lineNumberAreaPaintEvent(event);
    }
    
    void mousePressEvent(QMouseEvent *event) override;

private:
    EditorWidget *codeEditor;
};

#endif
