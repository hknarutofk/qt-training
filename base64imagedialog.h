#ifndef BASE64IMAGEDIALOG_H
#define BASE64IMAGEDIALOG_H

#include <QDialog>

namespace Ui {
class Base64ImageDialog;
}

class Base64ImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Base64ImageDialog(QWidget *parent = nullptr);
    ~Base64ImageDialog();

private:
    Ui::Base64ImageDialog *ui;
};

#endif // BASE64IMAGEDIALOG_H
