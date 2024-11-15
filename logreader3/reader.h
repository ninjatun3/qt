// класс чтения файла

#ifndef READER_H
#define READER_H

#include "qdir.h"
#include <QObject>
#include <QPlainTextEdit>
#include <QFile>

static QString filename; // имя файла
static size_t view_position; // позиция чтения
static size_t lines = 50; // размер блока чтения

class Reader : public QObject
{
    Q_OBJECT

public:
    explicit Reader(QObject *parent = nullptr);

public slots:
    void getFilename(const QString&); // получение данных файла
    void readLine(); // чтение файла блоками

signals:
    void sendData(const QByteArray&); // передача данных в главное окно

};

#endif // READER_H
