#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mythread.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString filename;

signals:
    void sendFilename(const QString&);

public slots:
    void showString(const QString&);

private slots:
    void on_pushButton_OpenFile_clicked();
    void on_pushButton_About_clicked();
    void on_pushButton_Exit_clicked();

private:
    Ui::MainWindow *ui;

    MyThread* my_thread {};
};
#endif // MAINWINDOW_H
