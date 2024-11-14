#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reader.h"

#include <QApplication>
#include <QMessageBox>
#include <QThread>
#include <QFileDialog>
#include <QByteArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // создание отдельного потока, перемещение в него экземпляра Reader
    QThread* thread = new QThread();
    Reader* rd = new Reader();
    rd->moveToThread(thread);

    // запуск отдельного потока с открытием файла
    connect(this, &MainWindow::started, rd, &Reader::startWork, Qt::QueuedConnection);
    connect(rd, &Reader::finished, this, &MainWindow::finish, Qt::QueuedConnection);
    connect(rd, &Reader::sendData, this, &MainWindow::showData, Qt::QueuedConnection);

    thread->start();
}

MainWindow::~MainWindow() {
    delete ui;
}

// вывод текста в поле
void MainWindow::showData(QByteArray data) {
    ui->plainTextEdit->insertPlainText(data);
}

// сигнал об успешном завершении потока
void MainWindow::finish() {
    qDebug() << "thread finished";
}

// открыть файл с рашсирешнием .log
void MainWindow::on_pushButton_Open_clicked() {
    QString filename = QFileDialog::getOpenFileName(this,
        "Choose file",
            QDir::currentPath(),
                tr("Log files (*.log)"));
    emit started(filename);
}

// вывод окна о программе
void MainWindow::on_pushButton_About_clicked() {
    QMessageBox::about(this, "О программе", "О программе");
}

// выход из программы
void MainWindow::on_pushButton_Exit_clicked() {
    close();
}
