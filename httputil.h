#ifndef HTTPUTIL_H
#define HTTPUTIL_H

#include <QObject>
#include <QNetworkAccessManager>

class HttpUtil : public QObject
{
    Q_OBJECT
public:
    explicit HttpUtil(QObject *parent = nullptr);

    /**
      http https下载一段简单内容，返回响应字符串
     * @brief get
     * @param url
     * @return
     */
    static QString get(const QUrl url);

signals:

public slots:
};

#endif // HTTPUTIL_H
