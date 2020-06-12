#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QProcess *cmd;
    QPixmap pix;
    QGraphicsScene sense;

private slots:
    void on_readoutput();
    void on_readerror();
    void on_pushButton_clicked();
    void finished(int exitCode, QProcess::ExitStatus exitStatus);


    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};
#endif // MAINWINDOW_H
