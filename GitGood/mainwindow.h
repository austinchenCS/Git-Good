#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "codeanalyzer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString out;

    QString dir;

    String outputFileName;

    String directory;

    void delay(int);

    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

public slots:

    //left blank

private slots:
    //void on_pushButton_clicked();

    //void on_pushButton_2_clicked();

    void on_outputButton_clicked();

    void on_inputButton_clicked();

    void on_startButton_clicked();

    void on_openReport_clicked();

    void on_quitButton_clicked();

    void on_restartButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
