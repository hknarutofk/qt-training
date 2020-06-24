#include "updater.h"
#include "httputil.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "log.h"

Updater::Updater(QObject *parent) : QObject(parent)
{    

}

Updater::~Updater()
{

}

void Updater::checkUpdate()
{
    logDebug() << "start to check update";
    QString json = HttpUtil::get(CHECK_URL);
    QJsonParseError e;
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8(), &e);
    if (e.error == QJsonParseError::NoError && !doc.isNull()) {
        logDebug() << doc;
        if(doc.isObject()){
            QJsonObject obj = doc.object();
            QString newVersion = obj.value("version").toString();
            QString url = obj.value("url").toString();
            logDebug() << "newVersion:" + newVersion;
            logDebug() << url;
            // 判断版本大小
            // 将2段版本号转换成浮点数，进行比较
            logDebug() << "oldVersion:" + VERSION;
            if(VERSION.toFloat() < newVersion.toFloat()){
                logDebug() << "new version found, start to download";

                // 异步信号曹， 完成后触发安装
            }
        }
    }
    else{
        logDebug() << QString("json parse error: %1").arg(e.error);
    }
}
