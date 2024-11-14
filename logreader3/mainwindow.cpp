#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupFileMenu();
    setupEditor();

    setCentralWidget(editor);
    setWindowTitle(tr("Syntax Highlighter"));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::newFile() {
    editor->clear();
}

void MainWindow::openFile(const QString &path) {
    filename = path;
    readFile(filename);
    // emit sendFilename(filename);
}

void MainWindow::showData(const QString& line) {
    editor->insertPlainText(line);
}

void MainWindow::readFile(const QString& line) {
    qDebug() << "readFile worked";
    if (filename.isNull())
        filename = QFileDialog::getOpenFileName(this,
                                                tr("Open File"), "", "Log files (*.log)");

    if (!filename.isEmpty()) {
        QFile file(filename);
        if (file.open(QFile::ReadOnly | QFile::Text))
            while (!file.atEnd()) {
                QString line = file.readLine();
                showData(line);
                //editor->insertPlainText(line);
            }
    }
}

void MainWindow::setupEditor() {
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    editor = new QTextEdit;
    editor->setFont(font);

    highlighter = new Highlighter(editor->document());

    QFile file("mainwindow.h");
    if (file.open(QFile::ReadOnly | QFile::Text))
        editor->setPlainText(file.readAll());
}

void MainWindow::setupFileMenu() {
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    menuBar()->addMenu(fileMenu);

    fileMenu->addAction(tr("&New"), this, SLOT(newFile()),
                        QKeySequence(tr("Ctrl+N",
                                        "File|New")));
    fileMenu->addAction(tr("&Open..."), this, SLOT(openFile()),
                        QKeySequence(tr("Ctrl+O",
                                        "File|Open")));
    fileMenu->addAction(tr("&Exit"), qApp, SLOT(quit()),
                        QKeySequence(tr("Ctrl+Q",
                                        "File|Exit")));
}
