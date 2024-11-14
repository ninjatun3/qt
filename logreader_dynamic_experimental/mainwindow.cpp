#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reader.h"
#include <highlighter.h>

#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    rd = new Reader();


    // отправка данных
    connect(this, &MainWindow::sendFilename, rd, &Reader::getFilename);
    //    connect(rd, &Reader::sig_readLine, rd, &Reader::readLine, Qt::UniqueConnection);


    // дин. загрузка при прокрутке plaintTextEdit
    QScrollBar* sbar = ui->textBrowser->verticalScrollBar();
    connect(sbar, &QScrollBar::valueChanged, rd, &Reader::readLine);

    // получение данных
    connect(rd, &Reader::sendData, this, &MainWindow::displayData);
    // подсветка
    //connect(hl, &Highlighter::sendHighlightedStr, this, &MainWindow::displayData);


}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupEditor(const QString& str) {
    editor = new QTextBrowser();
    hl = new Highlighter(editor->document());
    QFile file(str);
    qDebug() << "setupEditor filename: " << str;
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        editor->setPlainText(file.readAll());
    }
}

// вывод текста в поле
void MainWindow::displayData(const QString& data) {
    // вывод разных типов логов разными цветами
/*    if (data.contains("[inf]")) ui->textBrowser->setTextColor("yellow");
    else if (data.contains("[txt]")) ui->textBrowser->setTextColor("orange");
    else if (data.contains("[dbg]")) ui->textBrowser->setTextColor("green");
    else if (data.contains("[wrn]")) ui->textBrowser->setTextColor("darkBlue");
    else if (data.contains("[err]")) ui->textBrowser->setTextColor("purple");
    else if (data.contains("[<<<]")) ui->textBrowser->setTextColor("white");
    else if (data.contains("[>>>]")) ui->textBrowser->setTextColor("red");

    editor = new QTextBrowser;
    highlighter = new Highlighter(editor->document());
    editor->insertPlainText(data);
*/

    ui->textBrowser->insertPlainText(data);

}

// открыть файл
void MainWindow::on_pushButton_Open_clicked() {
    QString fn = QFileDialog::getOpenFileName(this,
                                              "Choose file",
                                              QDir::currentPath());
    emit sendFilename(fn);
    setupEditor(fn);
}

// вывод окна о программе
void MainWindow::on_pushButton_About_clicked() {
    QMessageBox::about(this, "О программе", "О программе");
}

// выход из программы
void MainWindow::on_pushButton_Exit_clicked() {
    close();
}
