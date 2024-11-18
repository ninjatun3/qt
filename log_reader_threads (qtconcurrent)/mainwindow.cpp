#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QByteArray>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    my_thread = new MyThread(this);

    // отправка имени файла в класс mythread
    connect(this, &MainWindow::sendFilename,
            my_thread, &MyThread::readFile);

    // отправка строки обратно в главную форму
    connect(my_thread, &MyThread::sendString,
            this, &MainWindow::showString);
}

MainWindow::~MainWindow() {
    delete my_thread;
    delete ui;
}

void MainWindow::on_pushButton_OpenFile_clicked() {
    filename = QFileDialog::getOpenFileName(this,
        "Choose file",
            QDir::currentPath());
    emit sendFilename(filename);
}

void MainWindow::showString(const QString& str) {
    ui->plainTextEdit->insertPlainText(str);
}


void MainWindow::on_pushButton_Exit_clicked() {
    close();
}

void MainWindow::on_pushButton_About_clicked() {
    QMessageBox::about(this, "about", "сообщение");
}
