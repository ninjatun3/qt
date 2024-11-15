// класс главного окна

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "highlighter.h"
#include "reader.h"

#include <QMainWindow>
#include <QSyntaxHighlighter>
#include <QTextEdit>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString filename; // имя открываемого файла

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openFile(const QString &path = QString()); // открыть диалог выбора файла
    void showData(const QString& line); // отобразить файл, полученный из класса чтения

signals:
    void sendFilename(const QString&); // передать имя файла в класс чтения

private:
    Ui::MainWindow *ui;

    void setupEditor(); // применить правила подсветки для текстовой области
    void setupFileMenu(); // верхнее меню окна

    Reader *rd;
    QTextEdit *editor;
    Highlighter *highlighter;
};

#endif // MAINWINDOW_H
