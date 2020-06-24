#include "httputil.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTimer>
#include "log.h"

HttpUtil::HttpUtil(QObject *parent) : QObject(parent)
{

}

QString HttpUtil::get(const QUrl url)
{
    QNetworkAccessManager net;
    QNetworkRequest request(url);
    QNetworkReply *reply = net.get(request);

    // 添加消息循环机制...
    QEventLoop eventloop;
    connect(reply, SIGNAL(finished()), &eventloop, SLOT(quit()));
    QTimer timer;
    timer.setInterval(1000);
    timer.setSingleShot(true);
    timer.start();
    logDebug() << "timer started";
    eventloop.exec();
    logDebug() << "eventLoop executed";

    QByteArray array;
    if(timer.isActive()){
        if(reply->error() == QNetworkReply::NoError){
            logDebug() << "success";
        }
        array.append(reply->readAll());
    }
    else{
        disconnect(reply, &QNetworkReply::finished, &eventloop, &QEventLoop::quit);
        reply->abort();
        logDebug() << "timeout";
    }
    reply->deleteLater();

    QString responose = QString::fromUtf8(array);
    logDebug() << responose;
    return responose;
}
