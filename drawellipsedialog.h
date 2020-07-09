#ifndef DRAWELLIPSEDIALOG_H
#define DRAWELLIPSEDIALOG_H

#include <QDialog>
#include <QImage>

namespace Ui {
class DrawEllipseDialog;
}

class DrawEllipseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DrawEllipseDialog(QWidget *parent = nullptr);
    ~DrawEllipseDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DrawEllipseDialog *ui;

    QImage getRoundQImage(QImage & src, QSize size);
    void drawIcon(QImage image);
    QImage *icon;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // DRAWELLIPSEDIALOG_H
