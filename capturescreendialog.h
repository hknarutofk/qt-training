#ifndef CAPTURESCREENDIALOG_H
#define CAPTURESCREENDIALOG_H

#include <QDialog>
#include <QProcess>

namespace Ui {
class CaptureScreenDialog;
}

class CaptureScreenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CaptureScreenDialog(QWidget *parent = nullptr);
    ~CaptureScreenDialog();

private slots:
    void on_pushButton_clicked();
    void onProcessReadoutput();
    void onReaderror();
    void onFinished(int, QProcess::ExitStatus);

    void on_pushButton_2_clicked();

private:
    Ui::CaptureScreenDialog *ui;
    QProcess *process;
};

#endif // CAPTURESCREENDIALOG_H
