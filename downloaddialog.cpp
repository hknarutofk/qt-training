#include "downloaddialog.h"
#include "ui_downloaddialog.h"

DownloadDialog::DownloadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DownloadDialog)
{
    ui->setupUi(this);

    ui->progressBar->reset();
}

DownloadDialog::~DownloadDialog()
{
    delete ui;
}

void DownloadDialog::on_pushButton_clicked()
{

}
