#ifndef GIFDIALOG_H
#define GIFDIALOG_H

#include <QDialog>
#include <QMovie>

namespace Ui {
class GifDialog;
}

class GifDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GifDialog(QWidget *parent = nullptr);
    ~GifDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::GifDialog *ui;
    QMovie *movie;
};

#endif // GIFDIALOG_H
