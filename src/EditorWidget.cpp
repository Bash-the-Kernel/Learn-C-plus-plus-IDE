#include "EditorWidget.h"
#include "SyntaxHighlighter.h"
#include <QPainter>
#include <QTextBlock>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextCursor>
#include <QTextDocument>

EditorWidget::EditorWidget(QWidget *parent) : QPlainTextEdit(parent) {
    lineNumberArea = new LineNumberArea(this);
    highlighter = new SyntaxHighlighter(document());
    findReplaceDialog = nullptr;
    
    QFont font("Consolas", 11);
    font.setStyleHint(QFont::Monospace);
    setFont(font);
    
    setTabStopDistance(fontMetrics().horizontalAdvance(' ') * 4);
    
    connect(this, &EditorWidget::blockCountChanged, this, &EditorWidget::updateLineNumberAreaWidth);
    connect(this, &EditorWidget::updateRequest, this, &EditorWidget::updateLineNumberArea);
    connect(this, &EditorWidget::cursorPositionChanged, this, &EditorWidget::highlightCurrentLine);
    
    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

int EditorWidget::lineNumberAreaWidth() {
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }
    
    int space = 10 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
    return space;
}

void EditorWidget::updateLineNumberAreaWidth(int) {
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void EditorWidget::updateLineNumberArea(const QRect &rect, int dy) {
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
    
    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void EditorWidget::resizeEvent(QResizeEvent *e) {
    QPlainTextEdit::resizeEvent(e);
    
    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void EditorWidget::highlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extraSelections;
    
    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        
        QColor lineColor = QColor(Qt::yellow).lighter(160);
        lineColor.setAlpha(30);
        
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }
    
    setExtraSelections(extraSelections);
}

void EditorWidget::keyPressEvent(QKeyEvent *event) {
    if (event->modifiers() & Qt::ControlModifier) {
        if (event->key() == Qt::Key_F) {
            showFindDialog();
            return;
        } else if (event->key() == Qt::Key_H) {
            showReplaceDialog();
            return;
        }
    }
    QPlainTextEdit::keyPressEvent(event);
}

void EditorWidget::showFindDialog() {
    if (!findReplaceDialog) {
        findReplaceDialog = new FindReplaceDialog(this, this);
    }
    findReplaceDialog->showFind();
}

void EditorWidget::showReplaceDialog() {
    if (!findReplaceDialog) {
        findReplaceDialog = new FindReplaceDialog(this, this);
    }
    findReplaceDialog->showReplace();
}

void EditorWidget::lineNumberAreaPaintEvent(QPaintEvent *event) {
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), QColor(30, 30, 30));
    
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());
    
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(QColor(100, 100, 100));
            painter.drawText(0, top, lineNumberArea->width() - 5, fontMetrics().height(),
                           Qt::AlignRight, number);
        }
        
        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

// FindReplaceDialog Implementation
FindReplaceDialog::FindReplaceDialog(EditorWidget *editor, QWidget *parent)
    : QDialog(parent), editor(editor) {
    setWindowTitle("Find and Replace");
    setModal(false);
    resize(400, 150);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Find section
    QHBoxLayout *findLayout = new QHBoxLayout();
    findLayout->addWidget(new QLabel("Find:"));
    findLineEdit = new QLineEdit();
    findLayout->addWidget(findLineEdit);
    mainLayout->addLayout(findLayout);
    
    // Replace section
    QHBoxLayout *replaceLayout = new QHBoxLayout();
    replaceLayout->addWidget(new QLabel("Replace:"));
    replaceLineEdit = new QLineEdit();
    replaceLayout->addWidget(replaceLineEdit);
    mainLayout->addLayout(replaceLayout);
    
    // Options
    QHBoxLayout *optionsLayout = new QHBoxLayout();
    caseSensitiveBox = new QCheckBox("Case sensitive");
    wholeWordsBox = new QCheckBox("Whole words");
    optionsLayout->addWidget(caseSensitiveBox);
    optionsLayout->addWidget(wholeWordsBox);
    mainLayout->addLayout(optionsLayout);
    
    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    findNextBtn = new QPushButton("Find Next");
    findPrevBtn = new QPushButton("Find Previous");
    replaceBtn = new QPushButton("Replace");
    replaceAllBtn = new QPushButton("Replace All");
    
    buttonLayout->addWidget(findNextBtn);
    buttonLayout->addWidget(findPrevBtn);
    buttonLayout->addWidget(replaceBtn);
    buttonLayout->addWidget(replaceAllBtn);
    mainLayout->addLayout(buttonLayout);
    
    connect(findNextBtn, &QPushButton::clicked, this, &FindReplaceDialog::findNext);
    connect(findPrevBtn, &QPushButton::clicked, this, &FindReplaceDialog::findPrevious);
    connect(replaceBtn, &QPushButton::clicked, this, &FindReplaceDialog::replace);
    connect(replaceAllBtn, &QPushButton::clicked, this, &FindReplaceDialog::replaceAll);
    connect(findLineEdit, &QLineEdit::returnPressed, this, &FindReplaceDialog::findNext);
}

void FindReplaceDialog::showFind() {
    replaceLineEdit->hide();
    replaceBtn->hide();
    replaceAllBtn->hide();
    setWindowTitle("Find");
    show();
    findLineEdit->setFocus();
    findLineEdit->selectAll();
}

void FindReplaceDialog::showReplace() {
    replaceLineEdit->show();
    replaceBtn->show();
    replaceAllBtn->show();
    setWindowTitle("Find and Replace");
    show();
    findLineEdit->setFocus();
    findLineEdit->selectAll();
}

void FindReplaceDialog::findNext() {
    QString searchText = findLineEdit->text();
    if (searchText.isEmpty()) return;
    
    QTextDocument::FindFlags flags = QTextDocument::FindFlag();
    if (caseSensitiveBox->isChecked())
        flags |= QTextDocument::FindCaseSensitively;
    if (wholeWordsBox->isChecked())
        flags |= QTextDocument::FindWholeWords;
    
    if (!editor->find(searchText, flags)) {
        // Wrap around to beginning
        QTextCursor cursor = editor->textCursor();
        cursor.movePosition(QTextCursor::Start);
        editor->setTextCursor(cursor);
        editor->find(searchText, flags);
    }
}

void FindReplaceDialog::findPrevious() {
    QString searchText = findLineEdit->text();
    if (searchText.isEmpty()) return;
    
    QTextDocument::FindFlags flags = QTextDocument::FindBackward;
    if (caseSensitiveBox->isChecked())
        flags |= QTextDocument::FindCaseSensitively;
    if (wholeWordsBox->isChecked())
        flags |= QTextDocument::FindWholeWords;
    
    if (!editor->find(searchText, flags)) {
        // Wrap around to end
        QTextCursor cursor = editor->textCursor();
        cursor.movePosition(QTextCursor::End);
        editor->setTextCursor(cursor);
        editor->find(searchText, flags);
    }
}

void FindReplaceDialog::replace() {
    QTextCursor cursor = editor->textCursor();
    if (cursor.hasSelection() && cursor.selectedText() == findLineEdit->text()) {
        cursor.insertText(replaceLineEdit->text());
    }
    findNext();
}

void FindReplaceDialog::replaceAll() {
    QString searchText = findLineEdit->text();
    QString replaceText = replaceLineEdit->text();
    if (searchText.isEmpty()) return;
    
    QTextCursor cursor = editor->textCursor();
    cursor.movePosition(QTextCursor::Start);
    editor->setTextCursor(cursor);
    
    QTextDocument::FindFlags flags = QTextDocument::FindFlag();
    if (caseSensitiveBox->isChecked())
        flags |= QTextDocument::FindCaseSensitively;
    if (wholeWordsBox->isChecked())
        flags |= QTextDocument::FindWholeWords;
    
    int replacements = 0;
    while (editor->find(searchText, flags)) {
        editor->textCursor().insertText(replaceText);
        replacements++;
    }
    
    // Show result (could add status bar message)
}
