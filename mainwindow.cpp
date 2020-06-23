#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include "dialog.h"
#include "passwddialog.h"
#include "processdialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);

    this->cmd = new QProcess();
    connect(cmd , SIGNAL(readyReadStandardOutput()) , this , SLOT(on_readoutput()));
    connect(cmd , SIGNAL(readyReadStandardError()) , this , SLOT(on_readerror()));
    connect(cmd , SIGNAL(finished(int, QProcess::ExitStatus)) , this , SLOT(finished(int, QProcess::ExitStatus)));
    pix.load(":/new/prefix1/bg.jpeg");
    ui->graphicsView->setScene(&sense);
    sense.addPixmap(pix);
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
//    cmd->start("sudo -S dnf install vim -y");
//    cmd->waitForStarted();
//    qDebug() << "fdfdsfds";

    Dialog *dialog = new Dialog();
    dialog->show();
    qDebug() << "show dialog";
}

void MainWindow::on_pushButton_2_clicked()
{
     PasswdDialog *passwdDialog = new PasswdDialog();
     passwdDialog->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    ProcessDialog * dlg = new ProcessDialog();
    dlg->show();    
}
