#include "processdialog.h"
#include "ui_processdialog.h"
#include <QThread>

ProcessDialog::ProcessDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProcessDialog)
{
    ui->setupUi(this);
    val = 0;
    ui->progressBar->reset();
}

ProcessDialog::~ProcessDialog()
{
    delete ui;
}

void ProcessDialog::on_pushButton_clicked()
{
    ui->progressBar->setValue(++val);
}
