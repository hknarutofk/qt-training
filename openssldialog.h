#ifndef OPENSSLDIALOG_H
#define OPENSSLDIALOG_H

#include <QDialog>

namespace Ui {
class OpensslDialog;
}

class OpensslDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpensslDialog(QWidget *parent = nullptr);
    ~OpensslDialog();

private slots:
    void on_pushButton_genRsa_clicked();

private:
    Ui::OpensslDialog *ui;
};

#endif // OPENSSLDIALOG_H
