#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // настройка главного окна
    setupEditor();
    setupFileMenu();
    setCentralWidget(editor);
    setWindowTitle(tr("Log reader"));
    rd = new Reader();

    // соединения:
    // отправка имени файла для чтения
    connect(this, &MainWindow::sendFilename, rd, &Reader::getFilename);

    // получение данных
    connect(rd, &Reader::sendData, this, &MainWindow::showData);

    // подгрузка файла при прокрутке
    QScrollBar* sbar = editor->verticalScrollBar();
    connect(sbar, &QScrollBar::valueChanged, rd, &Reader::readLine);
}

MainWindow::~MainWindow() {
    delete ui;
}

// открыть файл с расширением .log
void MainWindow::openFile(const QString &path) {
    QString filename = path;
    filename = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", "Log files (*.log)");
    emit sendFilename(filename);
}

// отображение данных
void MainWindow::showData(const QString& line) {
    editor->insertPlainText(line);
}

// формат вывода
void MainWindow::setupEditor() {
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    editor = new QTextEdit;
    editor->setFont(font);
    highlighter = new Highlighter(editor->document());
}

// верхнее меню
void MainWindow::setupFileMenu() {
    QMenu *fileMenu = new QMenu(tr("&Файл"), this);
    menuBar()->addMenu(fileMenu);
    fileMenu->addAction(tr("&Открыть..."), this, SLOT(openFile()),
                        QKeySequence(tr("Ctrl+O",
                                        "File|Open")));
    fileMenu->addAction(tr("&Выход"), qApp, SLOT(quit()),
                        QKeySequence(tr("Ctrl+Q",
                                        "File|Exit")));
}
