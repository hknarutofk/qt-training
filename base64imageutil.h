#ifndef BASE64IMAGEUTIL_H
#define BASE64IMAGEUTIL_H

#include <QObject>
#include <QImage>

class Base64ImageUtil
{
public:
    Base64ImageUtil();
    //image 转 base64 字符串
    static QString png_2_base64_string(const QImage& img);

    //base64 转 QImage
    static QImage base64_string_2_img(const QString& str);
};

#endif // BASE64IMAGEUTIL_H
