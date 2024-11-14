// класс основного окна

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "reader.h"

#include <QMainWindow>
#include <QDebug>
#include <QThread>
#include <QMessageBox>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void displayData(const QByteArray&); // отображение данных в поле

signals:
    void sendFilename(const QString&); // отправка имени файла обработчику

private slots:
    void on_pushButton_Open_clicked(); // кнопка открытия файла
    void on_pushButton_About_clicked(); // кнопка о программе для проверки отзывчивости интерфейса
    void on_pushButton_Exit_clicked(); // кнопка выхода

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
