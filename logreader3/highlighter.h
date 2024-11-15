// класс подсветки синтаксиса

#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QObject>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QDebug>

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlighter(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override; // функция подсветки блока текста

private:
    struct HighlightingRule // правило подсветки
    {
        QRegularExpression pattern; // маска подсветки
        QTextCharFormat format; // формат подсветки
    };
    QList<HighlightingRule> highlightingRules; // перечень правил подсветки

    QRegularExpression messageStart; // разметка блока текста сообщения
    QRegularExpression messageEnd; // разметка блока текста сообщения
    QTextCharFormat multiLineMessage; // блок текста

    QTextCharFormat date; // дата
    QTextCharFormat inf; // информация
    QTextCharFormat txt; // текст
    QTextCharFormat dbg; // отладочные сведения
    QTextCharFormat wrn; // предупреждение
    QTextCharFormat err; // ошибка
    QTextCharFormat input; // входящие данные
    QTextCharFormat output; // исходящие данные
};

#endif // HIGHLIGHTER_H
