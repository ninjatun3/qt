// класс для чтения файла

#ifndef READER_H
#define READER_H

#include "qdir.h"
#include <QObject>
#include <QPlainTextEdit>
#include <QFile>

static QString filename;
static int view_position;
static int filesize;
static int lines = 50;

class Reader : public QObject
{
    Q_OBJECT

public:
    explicit Reader(QObject *parent = nullptr);

public slots:
    void getFilename(const QString&); // получение данных файла
    void readLine(); // чтение файла блоками

signals:
    void sig_readLine();
    void sendData(const QByteArray&);

signals:
};

#endif // READER_H
