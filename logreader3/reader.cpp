#include "reader.h"

#include <QDebug>
#include <QFile>

Reader::Reader(QObject *parent)
    : QObject{parent}
{}

// получение имени файла в класс чтения файла
void Reader::getFilename(const QString& fn) {
    filename = fn;
    readLine(); // передача управления в функцию чтения
}

// функция чтения файла построчно
void Reader::readLine() {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        for (size_t i = 0; i < lines; i++) {
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
