#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>

class MyThread : public QObject {
    Q_OBJECT

public:
    explicit MyThread(QObject* parent = nullptr);

signals:
    void sendString(const QString&);

public slots:
    void readFile(const QString&);
    void readFileC(const QString&);
};

#endif // MYTHREAD_H
