#include "mythread.h"

#include <QDebug>
#include <QFileDialog>
#include <QByteArray>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>

MyThread::MyThread(QObject* parent) : QObject(parent) {}

/*
// qt 5
void MyThread::readFile(const QString& filename) {
    QFuture<void> future = QtConcurrent::run([this, filename]() {

    qDebug() << "filename recieved: " << filename;

    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        qDebug() << "file opened: " << filename;
        QTextStream stream(&file);
        while (!file.atEnd()) {
            QString str = stream.readLine();
            emit sendString(str);
        }
        file.close();
    } else {
        qDebug() << "file open error";
    }
    });
}
*/

void MyThread::readFile(const QString& filename) {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        qDebug() << "file opened: " << filename;
        QTextStream stream(&file);
        while (!file.atEnd()) {
            QString str = stream.readLine();
            emit sendString(str);
        }
        file.close();
    } else {
        qDebug() << "file open error";
    }
}

// qt 6
void MyThread::readFileC(const QString& filename) {
    QtConcurrent::run(&MyThread::readFile, this, filename);
}
