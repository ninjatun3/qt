// класс основного окна

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString filename;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void started(QString); // сигнал о запуске потока

public slots:
    void finish(); // завершение потока
    void showData(QByteArray); // отображение файла

private slots:
    void on_pushButton_Open_clicked();
    void on_pushButton_About_clicked();
    void on_pushButton_Exit_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
