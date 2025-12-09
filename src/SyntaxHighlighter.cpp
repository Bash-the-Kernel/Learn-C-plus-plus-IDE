#include "SyntaxHighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) {
    HighlightingRule rule;

    keywordFormat.setForeground(QColor(86, 156, 214));
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns = {
        "\\bauto\\b", "\\bbreak\\b", "\\bcase\\b", "\\bcatch\\b", "\\bclass\\b",
        "\\bconst\\b", "\\bconstexpr\\b", "\\bcontinue\\b", "\\bdefault\\b", "\\bdelete\\b",
        "\\bdo\\b", "\\belse\\b", "\\benum\\b", "\\bexplicit\\b", "\\bextern\\b",
        "\\bfor\\b", "\\bfriend\\b", "\\bif\\b", "\\binline\\b", "\\bmutable\\b",
        "\\bnamespace\\b", "\\bnew\\b", "\\boperator\\b", "\\bprivate\\b", "\\bprotected\\b",
        "\\bpublic\\b", "\\breturn\\b", "\\bsizeof\\b", "\\bstatic\\b", "\\bstruct\\b",
        "\\bswitch\\b", "\\btemplate\\b", "\\bthis\\b", "\\bthrow\\b", "\\btry\\b",
        "\\btypedef\\b", "\\btypename\\b", "\\bunion\\b", "\\busing\\b", "\\bvirtual\\b",
        "\\bvolatile\\b", "\\bwhile\\b", "\\bnoexcept\\b", "\\bnullptr\\b", "\\boverride\\b",
        "\\bfinal\\b", "\\bconcept\\b", "\\brequires\\b", "\\bconsteval\\b", "\\bconstinit\\b"
    };
    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    typeFormat.setForeground(QColor(78, 201, 176));
    QStringList typePatterns = {
        "\\bint\\b", "\\bchar\\b", "\\bfloat\\b", "\\bdouble\\b", "\\bbool\\b",
        "\\bvoid\\b", "\\blong\\b", "\\bshort\\b", "\\bunsigned\\b", "\\bsigned\\b",
        "\\bsize_t\\b", "\\bstring\\b", "\\bvector\\b", "\\bmap\\b", "\\bset\\b",
        "\\barray\\b", "\\blist\\b", "\\bqueue\\b", "\\bstack\\b", "\\bpair\\b"
    };
    for (const QString &pattern : typePatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = typeFormat;
        highlightingRules.append(rule);
    }

    preprocessorFormat.setForeground(QColor(155, 155, 155));
    rule.pattern = QRegularExpression("^\\s*#\\s*\\w+");
    rule.format = preprocessorFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(QColor(206, 145, 120));
    rule.pattern = QRegularExpression("\".*\"|'.'");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    numberFormat.setForeground(QColor(181, 206, 168));
    rule.pattern = QRegularExpression("\\b[0-9]+\\.?[0-9]*\\b");
    rule.format = numberFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(QColor(106, 153, 85));
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(QColor(106, 153, 85));
    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

void SyntaxHighlighter::highlightBlock(const QString &text) {
    for (const HighlightingRule &rule : highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);

    while (startIndex >= 0) {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}
