#ifndef PASSWDDIALOG_H
#define PASSWDDIALOG_H

#include <QDialog>

namespace Ui {
class PasswdDialog;
}

class PasswdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasswdDialog(QWidget *parent = nullptr);
    ~PasswdDialog();

private slots:
    void on_pushButton_confirm_clicked();

private:
    Ui::PasswdDialog *ui;
};

#endif // PASSWDDIALOG_H
