#include "passwddialog.h"
#include "ui_passwddialog.h"
#include <QDebug>

PasswdDialog::PasswdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswdDialog)
{
    ui->setupUi(this);
}

PasswdDialog::~PasswdDialog()
{
    delete ui;
}

void PasswdDialog::on_pushButton_confirm_clicked()
{
    qDebug() << ui->lineEdit_passwd->text();
}
