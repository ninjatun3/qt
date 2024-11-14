// класс работы с файлом

#ifndef READER_H
#define READER_H

#include <QObject>

class Reader : public QObject
{
    Q_OBJECT
public:
    explicit Reader(QObject *parent = nullptr);

//    QByteArray data;
    void startWork(const QString filename); // чтение файла

signals:
    void finished(); // сигнал об окончании работы потока
    void sendData(QByteArray); // передача данных в главное окно
};

#endif // READER_H
