#include "reader.h"

#include <QDebug>
#include <QFile>

Reader::Reader(QObject *parent)
    : QObject{parent}
{}

// получение имени файла в класс чтения файла
void Reader::getFilename(const QString& fn) {
    filename = fn;
    qDebug() << "filename recieved: " << filename;
    readLine(); // передача управления в функцию чтения
}

// функция чтения файла блоками
void Reader::readLine() {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        for (int i = 0; i < lines && !file.atEnd(); i++) {
            file.seek(view_position);
            QByteArray str;
            str = file.readLine();
            view_position += str.size();
            emit sendData(str);
        }
        file.close();
    } else {
        qDebug() << "file open error";
    }
}


/*
// функция чтения файла блоками
void Reader::readLine() {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        while (!file.atEnd()) {
            file.seek(view_position);
            QByteArray str;
            str = file.read(lines);
            view_position += lines;
            emit sendData(str);
        }
        file.close();
    } else {
        qDebug() << "file open error";
    }
}
*/
