#include "reader.h"

#include <QDebug>
#include <QFile>

Reader::Reader(QObject *parent)
    : QObject{parent}
{}

// функция построчного чтения файла
void Reader::startWork(const QString filename) {
    qDebug() << "work started: " << filename;

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        qDebug() << "file opened: " << filename;
        while (!file.atEnd()) {
            QByteArray data = file.readLine();
            emit sendData(data);
        }
        file.close();
    } else {
        qDebug() << "file open error";
    }
    emit finished();
}
