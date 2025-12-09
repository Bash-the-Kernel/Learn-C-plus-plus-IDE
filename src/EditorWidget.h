#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QPlainTextEdit>
#include <QWidget>

class SyntaxHighlighter;
class LineNumberArea;

class EditorWidget : public QPlainTextEdit {
    Q_OBJECT

public:
    explicit EditorWidget(QWidget *parent = nullptr);
    
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    
    QString filePath() const { return m_filePath; }
    void setFilePath(const QString &path) { m_filePath = path; }

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);

private:
    SyntaxHighlighter *highlighter;
    QWidget *lineNumberArea;
    QString m_filePath;
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

private:
    EditorWidget *codeEditor;
};

#endif
