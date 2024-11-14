// класс для чтения файла

#ifndef READER_H
#define READER_H

#include "qdir.h"
#include "highlighter.h"

#include <QObject>
#include <QFile>
#include <QTextBrowser>

static QString filename;
static size_t view_position;
static size_t filesize;
static size_t lines = 50;

class Reader : public QObject
{
    Q_OBJECT

private:
    Highlighter* highlighter;
    QTextBrowser* editor;
public:
    explicit Reader(QObject *parent = nullptr);

public slots:
    void getFilename(const QString&); // получение данных файла
    void readLine(); // чтение файла блоками

signals:
    void sig_readLine();
    void sendData(const QString&);

signals:
};

#endif // READER_H
