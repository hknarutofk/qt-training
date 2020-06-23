#include "fileiodialog.h"
#include "ui_fileiodialog.h"
#include <QFile>
#include <QDebug>

FileIODialog::FileIODialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileIODialog)
{
    ui->setupUi(this);
}

FileIODialog::~FileIODialog()
{
    delete ui;
}

void FileIODialog::on_pushButton_clicked()
{
    QFile file("/tmp/a.kyl");
    if(!file.open(QIODevice::ReadWrite)){
        qDebug() << "cannot open file";
    }
    file.write(".kyl", 4);
    qint32 package_type = 1;
    qint64 package_size=1024;
    qint64 additional_size=1024;
    char package_data[1024];
    char additional_attributes[1024];
    QString signature="fdsfdsfdsfdsfdsfdsfdsfds";
    file.write((char *)&package_type, sizeof(package_type));
    file.write((char*)&package_size, sizeof(package_size));
    file.write(package_data, sizeof(package_data));
    file.write(additional_attributes, sizeof(additional_attributes));
    file.write(signature.toLocal8Bit());

    file.close();
}
