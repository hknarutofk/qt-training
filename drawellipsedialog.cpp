#include "drawellipsedialog.h"
#include "ui_drawellipsedialog.h"
#include <QPainter>
#include <QGraphicsScene>

DrawEllipseDialog::DrawEllipseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DrawEllipseDialog)
{
    ui->setupUi(this);    
    icon = new QImage(":/icon.png");
    drawIcon(*icon);
}

DrawEllipseDialog::~DrawEllipseDialog()
{
    delete ui;
    delete icon;
}

void DrawEllipseDialog::on_pushButton_clicked()
{
    //失败。。。。
    QSize size(128, 128);
    QImage img = getRoundQImage(*icon, size);
    drawIcon(img);
}

QImage DrawEllipseDialog::getRoundQImage(QImage & src, QSize size)
 {
     QImage resultImage(size, QImage::Format_ARGB32_Premultiplied);
     src = src.scaled(size);
     QPainter painter(&resultImage);
     painter.setCompositionMode(QPainter::CompositionMode_Source);
     painter.fillRect(resultImage.rect(), Qt::transparent);
     painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
//     painter.drawImage(0, 0, mask);
     painter.setCompositionMode(QPainter::CompositionMode_SourceOut);
     painter.drawImage(0, 0, src);
     painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
     painter.end();
     return resultImage;
 }

void DrawEllipseDialog::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    QPixmap pix(":/new/prefix1/btn_bg.png");
    p.setBrush(QBrush(pix));
    p.drawEllipse(10, 20, 250, 250);
}


void DrawEllipseDialog::drawIcon(QImage image)
{
    QGraphicsScene *scene = new QGraphicsScene();
    scene->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView->setScene(scene);
}
