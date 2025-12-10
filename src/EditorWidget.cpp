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
#include <QMouseEvent>
#include <QInputDialog>
#include <QMessageBox>
#include <QSet>
#include <QTimer>

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
    connect(this, &EditorWidget::cursorPositionChanged, this, &EditorWidget::onCursorPositionChanged);
    connect(document(), &QTextDocument::modificationChanged, this, &EditorWidget::onModificationChanged);
    
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
    
    // Add space for fold icons (20px) + line numbers
    int space = 30 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
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
    // This is now handled in highlightMatchingBrackets() to combine selections
    highlightMatchingBrackets();
}

void EditorWidget::keyPressEvent(QKeyEvent *event) {
    if (event->modifiers() & Qt::ControlModifier) {
        if (event->key() == Qt::Key_F) {
            showFindDialog();
            return;
        } else if (event->key() == Qt::Key_H) {
            showReplaceDialog();
            return;
        } else if (event->key() == Qt::Key_G) {
            showGoToLineDialog();
            return;
        } else if (event->modifiers() & Qt::ShiftModifier) {
            if (event->key() == Qt::Key_BracketLeft) {
                // Fold current block
                QTextCursor cursor = textCursor();
                toggleFold(cursor.blockNumber());
                return;
            } else if (event->key() == Qt::Key_BracketRight) {
                // Unfold current block
                QTextCursor cursor = textCursor();
                toggleFold(cursor.blockNumber());
                return;
            }
        }
    }
    
    // Auto-close brackets
    autoCloseBrackets(event);
    
    QPlainTextEdit::keyPressEvent(event);
    
    // Update bracket highlighting after key press
    highlightMatchingBrackets();
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

void EditorWidget::showGoToLineDialog() {
    bool ok;
    int currentLine = textCursor().blockNumber() + 1;
    int line = QInputDialog::getInt(this, "Go to Line", "Line number:", 
                                   currentLine, 1, blockCount(), 1, &ok);
    if (ok) {
        QTextCursor cursor(document()->findBlockByLineNumber(line - 1));
        setTextCursor(cursor);
        centerCursor();
    }
}

void EditorWidget::mousePressEvent(QMouseEvent *event) {
    QPlainTextEdit::mousePressEvent(event);
    highlightMatchingBrackets();
}

void EditorWidget::paintEvent(QPaintEvent *event) {
    // Just use default paint - visibility is managed in toggleFold
    QPlainTextEdit::paintEvent(event);
}

void EditorWidget::onCursorPositionChanged() {
    QTextCursor cursor = textCursor();
    int line = cursor.blockNumber() + 1;
    int column = cursor.columnNumber() + 1;
    emit cursorPositionUpdated(line, column);
    highlightMatchingBrackets();
}

void EditorWidget::onModificationChanged(bool changed) {
    emit modificationChanged(changed);
}

void EditorWidget::toggleFold(int line) {
    QTextBlock startBlock = document()->findBlockByLineNumber(line);
    if (!startBlock.isValid()) return;
    
    QString text = startBlock.text().trimmed();
    if (!text.contains('{')) return;
    
    if (foldedBlocks.contains(line)) {
        // Unfold - restore original visibility
        QList<int> hiddenLines = foldedBlocks[line];
        for (int lineNum : hiddenLines) {
            QTextBlock block = document()->findBlockByLineNumber(lineNum);
            if (block.isValid()) {
                // Restore original visibility or true if not tracked
                bool originalVis = originalVisibility.value(lineNum, true);
                block.setVisible(originalVis);
                originalVisibility.remove(lineNum);
            }
        }
        foldedBlocks.remove(line);
    } else {
        // Fold - save original visibility and hide lines
        QTextBlock block = startBlock.next();
        int braceCount = 1;
        QList<int> linesToHide;
        
        while (block.isValid() && braceCount > 0) {
            QString blockText = block.text();
            braceCount += blockText.count('{') - blockText.count('}');
            
            if (braceCount > 0) {
                int blockNum = block.blockNumber();
                linesToHide.append(blockNum);
                // Save original visibility before hiding
                originalVisibility[blockNum] = block.isVisible();
            }
            block = block.next();
        }
        
        if (!linesToHide.isEmpty()) {
            foldedBlocks[line] = linesToHide;
            // Actually hide the lines
            for (int lineNum : linesToHide) {
                QTextBlock block = document()->findBlockByLineNumber(lineNum);
                if (block.isValid()) {
                    block.setVisible(false);
                }
            }
        }
    }
    
    document()->markContentsDirty(0, document()->characterCount());
    viewport()->update();
    lineNumberArea->update();
}

bool EditorWidget::isBlockFolded(int blockNumber) const {
    // Check if this line is the start of a folded block
    if (foldedBlocks.contains(blockNumber)) {
        return true;
    }
    // Check if this line is hidden inside a folded block
    for (auto it = foldedBlocks.begin(); it != foldedBlocks.end(); ++it) {
        if (it.value().contains(blockNumber)) {
            return true;
        }
    }
    return false;
}

void EditorWidget::highlightMatchingBrackets() {
    QList<QTextEdit::ExtraSelection> selections;
    
    QTextCursor cursor = textCursor();
    QTextDocument *doc = document();
    
    int pos = cursor.position();
    QChar currentChar = doc->characterAt(pos);
    QChar prevChar = pos > 0 ? doc->characterAt(pos - 1) : QChar();
    
    int matchPos = -1;
    
    // Check for opening brackets
    if (currentChar == '(') {
        matchPos = findMatchingBracket(pos, '(', ')', true);
    } else if (currentChar == '[') {
        matchPos = findMatchingBracket(pos, '[', ']', true);
    } else if (currentChar == '{') {
        matchPos = findMatchingBracket(pos, '{', '}', true);
    }
    // Check for closing brackets
    else if (prevChar == ')') {
        matchPos = findMatchingBracket(pos - 1, ')', '(', false);
        pos = pos - 1;
    } else if (prevChar == ']') {
        matchPos = findMatchingBracket(pos - 1, ']', '[', false);
        pos = pos - 1;
    } else if (prevChar == '}') {
        matchPos = findMatchingBracket(pos - 1, '}', '{', false);
        pos = pos - 1;
    }
    
    if (matchPos != -1) {
        QTextEdit::ExtraSelection selection1, selection2;
        
        // Highlight current bracket
        selection1.cursor = QTextCursor(doc);
        selection1.cursor.setPosition(pos);
        selection1.cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        selection1.format.setBackground(QColor(100, 200, 100, 100));
        
        // Highlight matching bracket
        selection2.cursor = QTextCursor(doc);
        selection2.cursor.setPosition(matchPos);
        selection2.cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
        selection2.format.setBackground(QColor(100, 200, 100, 100));
        
        selections.append(selection1);
        selections.append(selection2);
    }
    
    bracketSelections = selections;
    
    // Combine with current line highlighting
    QList<QTextEdit::ExtraSelection> allSelections;
    
    // Current line highlight
    if (!isReadOnly()) {
        QTextEdit::ExtraSelection lineSelection;
        QColor lineColor = QColor(Qt::yellow).lighter(160);
        lineColor.setAlpha(30);
        lineSelection.format.setBackground(lineColor);
        lineSelection.format.setProperty(QTextFormat::FullWidthSelection, true);
        lineSelection.cursor = textCursor();
        lineSelection.cursor.clearSelection();
        allSelections.append(lineSelection);
    }
    
    allSelections.append(bracketSelections);
    setExtraSelections(allSelections);
}

int EditorWidget::findMatchingBracket(int position, QChar openBracket, QChar closeBracket, bool forward) {
    QTextDocument *doc = document();
    int count = 1;
    int pos = position;
    
    while (count > 0) {
        pos = forward ? pos + 1 : pos - 1;
        if (pos < 0 || pos >= doc->characterCount()) break;
        
        QChar ch = doc->characterAt(pos);
        if (ch == openBracket) {
            count = forward ? count + 1 : count - 1;
        } else if (ch == closeBracket) {
            count = forward ? count - 1 : count + 1;
        }
    }
    
    return count == 0 ? pos : -1;
}

void EditorWidget::autoCloseBrackets(QKeyEvent *event) {
    QString text = event->text();
    if (text.isEmpty()) return;
    
    QChar ch = text[0];
    QTextCursor cursor = textCursor();
    
    if (ch == '(' || ch == '[' || ch == '{') {
        QString closingBracket;
        if (ch == '(') closingBracket = ")";
        else if (ch == '[') closingBracket = "]";
        else if (ch == '{') closingBracket = "}";
        
        // Don't auto-close if next character is alphanumeric
        QChar nextChar = document()->characterAt(cursor.position());
        if (nextChar.isLetterOrNumber()) return;
        
        // Insert the closing bracket after processing the opening one
        QTimer::singleShot(0, [this, closingBracket, cursor]() {
            QTextCursor newCursor = textCursor();
            newCursor.insertText(closingBracket);
            newCursor.movePosition(QTextCursor::PreviousCharacter);
            setTextCursor(newCursor);
        });
    }
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
            
            // Draw fold/unfold icon for blocks with braces
            QString text = block.text().trimmed();
            if (text.contains('{')) {
                QRect foldRect(5, top + 2, 12, 12);
                painter.setPen(QColor(150, 150, 150));
                painter.drawRect(foldRect);
                
                // Draw + or - based on fold state
                painter.drawLine(foldRect.left() + 2, foldRect.center().y(),
                               foldRect.right() - 2, foldRect.center().y());
                
                if (foldedBlocks.contains(blockNumber)) {
                    painter.drawLine(foldRect.center().x(), foldRect.top() + 2,
                                   foldRect.center().x(), foldRect.bottom() - 2);
                }
            }
            
            painter.setPen(QColor(100, 100, 100));
            painter.drawText(20, top, lineNumberArea->width() - 25, fontMetrics().height(),
                           Qt::AlignRight, number);
        }
        
        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

// LineNumberArea mouse press implementation
void LineNumberArea::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QTextBlock block = codeEditor->getFirstVisibleBlock();
        int top = qRound(codeEditor->getBlockBoundingGeometry(block).translated(codeEditor->getContentOffset()).top());
        int bottom = top + qRound(codeEditor->getBlockBoundingRect(block).height());
        int blockNumber = block.blockNumber();
        
        while (block.isValid()) {
            QPoint pos = event->position().toPoint();
            if (top <= pos.y() && pos.y() <= bottom) {
                // Check if click is on fold icon area
                if (pos.x() >= 5 && pos.x() <= 17) {
                    codeEditor->toggleFold(blockNumber);
                }
                break;
            }
            
            block = block.next();
            top = bottom;
            bottom = top + qRound(codeEditor->getBlockBoundingRect(block).height());
            ++blockNumber;
        }
    }
    QWidget::mousePressEvent(event);
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
    replaceLabel = new QLabel("Replace:");
    replaceLayout->addWidget(replaceLabel);
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
    replaceLabel->hide();
    replaceLineEdit->hide();
    replaceBtn->hide();
    replaceAllBtn->hide();
    setWindowTitle("Find");
    resize(400, 100);
    show();
    findLineEdit->setFocus();
    findLineEdit->selectAll();
}

void FindReplaceDialog::showReplace() {
    replaceLabel->show();
    replaceLineEdit->show();
    replaceBtn->show();
    replaceAllBtn->show();
    setWindowTitle("Find and Replace");
    resize(400, 150);
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
