#include "processdialog.h"
#include "ui_processdialog.h"
#include <QThread>

/**
 * 1. 利用openssl 生成RSA密钥对； 2. 服务器Java利用私钥签名文件（sha1）;3 客户端验证签名（Qt）
 * @brief ProcessDialog::ProcessDialog
 * @param parent
 */
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
