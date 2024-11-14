#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "highlighter.h"

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
    QString filename;

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void newFile();
    void openFile(const QString &path = QString());
    void readFile(const QString& line);
    void showData(const QString& line);

private:
    Ui::MainWindow *ui;


    void setupEditor();
    void setupFileMenu();

    QTextEdit *editor;
    Highlighter *highlighter;
};

#endif // MAINWINDOW_H
