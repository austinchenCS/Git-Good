#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QLineEdit>
#include <QTextStream>
#include <QString>
#include <QTime>
#include <QDesktopServices>
#include <QProcess>
#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );

    QMovie *movie = new QMovie(":/img/ajax-loader.gif");
    ui->loading->setMovie(movie);
    movie->start();

    ui->stackedWidget->setCurrentIndex(0);

    ui->openReport->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::delay(int n)
{
    QTime downTime = QTime::currentTime().addMSecs(n);

    while ( QTime::currentTime() < downTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void MainWindow::on_outputButton_clicked()
{
    this->out = QFileDialog::getSaveFileName(this,tr("Save As"),"/home",
                                             tr("Text Files (*.txt)"));

    if(!out.isEmpty())
    {
        if (!out.endsWith(".txt"))
        {
            out += ".txt";
        }
        ui->reportLine->setText(out);
        QByteArray array = out.toLocal8Bit();
        char* temp = array.data();
        this->outputFileName = temp;
    }
}

void MainWindow::on_inputButton_clicked()
{
    this->dir = QFileDialog::getExistingDirectory(this,tr("Open Directory"),
                                                  "/home",
                                                  QFileDialog::ShowDirsOnly);

    if (!dir.isEmpty())
    {
        ui->dirLine->setText(dir);
        QByteArray array = dir.toLocal8Bit();
        char* temp = array.data();
        this->directory = temp;
    }
}

void MainWindow::on_startButton_clicked()
{    
    if (!this->dir.isEmpty() && !this->out.isEmpty())
    {
        ui->reportLine->setDisabled(true);
        ui->dirLine->setDisabled(true);
        ui->inputButton->setDisabled(true);
        ui->outputButton->setDisabled(true);
        // Disable functionality of Start Button
        //ui->startButton->setDisabled(true);
        //ui->startButton->setVisible(false);
        // Change "page" to progress bar
        ui->stackedWidget->setCurrentIndex(1);
        this->delay(350);

        // Run code analyzer
        CodeAnalyzer codebase(this->directory.c_str(),
                              this->outputFileName.c_str());
        codebase.analyze();
        double score = codebase.getFinalScore();
        // Set score = finalScore from code analyzer
        QString qScore = QString::number(score);
        ui->score->setText(qScore);

        ui->stackedWidget->setCurrentIndex(2);
        this->delay(1000);
        ui->stackedWidget->setCurrentIndex(3);
        ui->openReport->setVisible(true);
        QObject::connect(ui->quitButton, SIGNAL(clicked()),
                         QApplication::instance(), SLOT(quit()));
        ui->quitButton->setDisabled(true);
        ui->restartButton->setDisabled(true);
        this->delay(1000);
        ui->quitButton->setDisabled(false);
        ui->restartButton->setDisabled(false);

    }
}

void MainWindow::on_openReport_clicked()
{
    QDesktopServices::openUrl(this->out);
}

void MainWindow::on_quitButton_clicked()
{
    //intentionally left blank
}

void MainWindow::on_restartButton_clicked()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0]);
}
