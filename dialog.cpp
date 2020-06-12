#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_btn1_clicked()
{
    QMessageBox::StandardButton btn = QMessageBox::information(NULL, "Title", "Content");
    qDebug() << btn;
    if(btn == QMessageBox::Ok){
        qDebug() << "yes";
    }
    else{
        qDebug() << btn;
        qDebug() << QMessageBox::Ok;
    }

    QMessageBox::information(NULL, "Title", "Content",
                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}
