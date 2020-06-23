#ifndef FILEIODIALOG_H
#define FILEIODIALOG_H

#include <QDialog>

namespace Ui {
class FileIODialog;
}

class FileIODialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileIODialog(QWidget *parent = nullptr);
    ~FileIODialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::FileIODialog *ui;
};

#endif // FILEIODIALOG_H
