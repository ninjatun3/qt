#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule; // правило обработки текста

    // дата
    date.setForeground(Qt::yellow);
    rule.pattern = QRegularExpression(QStringLiteral("\\[\\d\\d:\\d\\d:\\d\\d\\.\\d\\d\\d\\]"));
    rule.format = date;
    highlightingRules.append(rule);

    // текст сообщения
    multiLineMessage.setForeground(Qt::white);
    messageStart = QRegularExpression(QStringLiteral("\\s"));
    messageEnd = QRegularExpression(QStringLiteral("$"));

    // информация
    inf.setForeground(Qt::green);
    rule.pattern = QRegularExpression(QStringLiteral("\\[inf\\]"));
    rule.format = inf;
    highlightingRules.append(rule);

    // текст
    txt.setForeground(Qt::blue);
    rule.pattern = QRegularExpression(QStringLiteral("\\[txt\\]"));
    rule.format = txt;
    highlightingRules.append(rule);

    // отладочная информация
    dbg.setForeground(Qt::magenta);
    rule.pattern = QRegularExpression(QStringLiteral("\\[dbg\\]"));
    rule.format = dbg;
    highlightingRules.append(rule);

    // предупреждения
    wrn.setForeground(Qt::darkBlue);
    rule.pattern = QRegularExpression(QStringLiteral("\\[wrn\\]"));
    rule.format = wrn;
    highlightingRules.append(rule);

    // ошибки
    err.setForeground(Qt::red);
    rule.pattern = QRegularExpression(QStringLiteral("\\[err\\]"));
    rule.format = err;
    highlightingRules.append(rule);

    // входящие
    input.setForeground(Qt::lightGray);
    rule.pattern = QRegularExpression(QStringLiteral("\\[<<<\\]"));
    rule.format = input;
    highlightingRules.append(rule);

    // исходящие
    output.setForeground(Qt::cyan);
    rule.pattern = QRegularExpression(QStringLiteral("\\[>>>\\]"));
    rule.format = output;
    highlightingRules.append(rule);

}

// функция подсветки блока текста
void Highlighter::highlightBlock(const QString &text) {
    // поиск правила подсветки текста
    for (const HighlightingRule &rule : std::as_const(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    // обработка блоков текста
    setCurrentBlockState(0);
    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(messageStart);
    while (startIndex >= 0) {
        QRegularExpressionMatch match = messageEnd.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineMessage);
        startIndex = text.indexOf(messageStart, startIndex + commentLength);
    }
}
