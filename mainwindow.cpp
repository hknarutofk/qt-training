#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->cmd = new QProcess();
    connect(cmd , SIGNAL(readyReadStandardOutput()) , this , SLOT(on_readoutput()));
    connect(cmd , SIGNAL(readyReadStandardError()) , this , SLOT(on_readerror()));
    connect(cmd , SIGNAL(finished(int, QProcess::ExitStatus)) , this , SLOT(finished(int, QProcess::ExitStatus)));


}

MainWindow::~MainWindow()
{
    delete ui;
    if(cmd)
    {
        cmd->terminate();
        cmd->waitForFinished();
    }
}

void MainWindow::on_readoutput()
{
    qDebug() << QString::fromUtf8(cmd->readAllStandardOutput().data());
}

void MainWindow::on_readerror()
{
    QString error = QString::fromUtf8(cmd->readAllStandardError().data());
    qDebug() << error;
    if(error.startsWith("[sudo] ")){
        cmd->write("123123\n");
    }
}

void MainWindow::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << QString("on_finished %1").arg(exitCode);
}

void MainWindow::on_pushButton_clicked()
{
    cmd->start("sudo -S dnf install vim -y");
    cmd->waitForStarted();
    qDebug() << "fdfdsfds";
}
