#include "mainwindow2.h"
#include "ui_mainwindow2.h"
#include <QMessageBox>

MainWindow2::MainWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
}

MainWindow2::~MainWindow2()
{
    delete ui;
}

void MainWindow2::on_pushButton_clicked()
{
    QMessageBox::information(NULL, "info", "info");
}

void MainWindow2::on_pushButton_2_clicked()
{
    this->close();
}
