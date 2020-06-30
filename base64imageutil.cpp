#include "base64imageutil.h"
#include <QBuffer>

Base64ImageUtil::Base64ImageUtil()
{

}

QString Base64ImageUtil::png_2_base64_string(const QImage &img)
{
    QByteArray ba;
    QBuffer buf(&ba);
    buf.open(QIODevice::WriteOnly);

    img.save(&buf, "PNG");
    QByteArray ba2 = ba.toBase64();
    QString b64str = QString::fromLatin1(ba2);

    return b64str;
}

QImage Base64ImageUtil::base64_string_2_img(const QString &str)
{
    QImage img;
    QByteArray arr_base64 = str.toLatin1();
    img.loadFromData(QByteArray::fromBase64(arr_base64));

    return img;
}
