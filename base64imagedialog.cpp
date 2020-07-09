#include "base64imagedialog.h"
#include "ui_base64imagedialog.h"
#include "base64imageutil.h"
#include "log.h"
#include <QImage>

Base64ImageDialog::Base64ImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Base64ImageDialog)
{
    ui->setupUi(this);
    QImage image = Base64ImageUtil::base64_string_2_img("iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAMAAAAoLQ9TAAAABGdBTUEAALGPC/xhBQAAAAFzUkdCAK7OHOkAAAAgY0hSTQAAeiYAAICEAAD6AAAAgOgAAHUwAADqYAAAOpgAABdwnLpRPAAAAORQTFRFAAAAKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXmKXXm3ur7/////P3/i7TxZpzt+Pv+5u/8pMT0oMH0OX/oPIHo3+v7To3qlbrzqsn1QITp8vf+m77zyNz5Nn7o7fT9RIbpp8f1pcX15+/8SorqqMj19vn+u9T3N37oQoXpvNX34+384Ov7osP0psf1RYfphLDxh7Hx+fv+TYzqLHfmAO3/EQAAACF0Uk5TAC6z+TEho/3+qCQXkvuXGW3z9nH1+n57IKKnLbc8vsBAOke26gAAAAFiS0dEIypibDoAAAAJcEhZcwAAAEgAAABIAEbJaz4AAACnSURBVBjTTY/FAoJQFESvoILdnSN2ARYq2C3//z/yfBhnNXNWM0QMjyAKXvri80sA5ECQ11BYBCcSjTk9nsCPZIoojX8yREBDUZottDuK0gWY6PUx6A5HY6gaF/pEx3SmYb4wuMByBWNtQrXgCmNjqFtrt9h/BLTDcXg6X/AWbNW1ecP9oTtJJMoy87Rhm2xGzpmaL0juKrnovikJ717++1upZmp1Hl/j2Ru6H7uvIwAAACV0RVh0ZGF0ZTpjcmVhdGUAMjAyMC0wNi0wNVQxNzozODoxMiswODowMB/RSHQAAAAldEVYdGRhdGU6bW9kaWZ5ADIwMjAtMDMtMjhUMDc6NDI6MTkrMDg6MDAsYZ8qAAAAAElFTkSuQmCC");
    logDebug() << image;
    QGraphicsScene *scene = new QGraphicsScene;
    scene->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView->setScene(scene);
//    ui->graphicsView->resize(image.width() + 10, image.height() + 10);

    QString b64 = Base64ImageUtil::png_2_base64_string(image);
    logDebug() << b64;
}

Base64ImageDialog::~Base64ImageDialog()
{
    delete ui;
}
