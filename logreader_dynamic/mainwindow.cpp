#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reader.h"

#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    Reader* rd = new Reader();
    // отправка
    connect(this, &MainWindow::sendFilename, rd, &Reader::getFilename);
    //    connect(rd, &Reader::sig_readLine, rd, &Reader::readLine, Qt::UniqueConnection);

    // получение данных
    connect(rd, &Reader::sendData, this, &MainWindow::displayData);

    // дин. загрузка при прокрутке plaintTextEdit
    QScrollBar* sbar = ui->textBrowser->verticalScrollBar();
    connect(sbar, &QScrollBar::valueChanged, rd, &Reader::readLine);

}

MainWindow::~MainWindow() {
    delete ui;
}

// вывод текста в поле
void MainWindow::displayData(const QByteArray& data) {
    // вывод разных типов логов разными цветами
    if (data.contains("[inf]")) ui->textBrowser->setTextColor("yellow");
    else if (data.contains("[txt]")) ui->textBrowser->setTextColor("orange");
    else if (data.contains("[dbg]")) ui->textBrowser->setTextColor("green");
    else if (data.contains("[wrn]")) ui->textBrowser->setTextColor("darkBlue");
    else if (data.contains("[err]")) ui->textBrowser->setTextColor("purple");
    else if (data.contains("[<<<]")) ui->textBrowser->setTextColor("white");
    else if (data.contains("[>>>]")) ui->textBrowser->setTextColor("red");
    ui->textBrowser->insertPlainText(data);
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
