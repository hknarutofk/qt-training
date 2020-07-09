#include "gifdialog.h"
#include "ui_gifdialog.h"
#include "log.h"


GifDialog::GifDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GifDialog)
{
    ui->setupUi(this);
}

GifDialog::~GifDialog()
{
    delete ui;
    delete movie;
}

void GifDialog::on_pushButton_clicked()
{
    movie = new QMovie(":/uploading.gif");
    ui->label->setMovie(movie);
    logDebug() << movie;
    logDebug() << movie->currentImage();
    logDebug() << movie->currentPixmap();
    logDebug() << movie->currentImage().width() << movie->currentImage().height();
//    ui->label->setGeometry(10, 10, movie->currentImage().width(), movie->currentImage().height());
    movie->start();
}
