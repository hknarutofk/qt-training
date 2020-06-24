#ifndef UPDATER_H
#define UPDATER_H

#include <QObject>
#include <QNetworkAccessManager>

/**
  软件升级管理器
 * @brief The updater class
 */
class Updater : public QObject
{
    Q_OBJECT
public:
    explicit Updater(QObject *parent = nullptr);
    ~Updater();
    /**
      固定采用两段版本号
      主版本号.次版本号
     * @brief VERSION
     */
//    const unsigned int MAJOR_VERSION=1;
//    const unsigned int MINOR_VERSION=0;
    const QString VERSION = "1.0";

    /**
      {"version":"1.1","url":"http://localhost/qt-training/gwinstaller.run"}
     * @brief CHECK_URL
     */
    const QString CHECK_URL="http://localhost/qt-training/version.json";
    /**
      执行更新检查，如果有更新，则触发upateEvent时间
     * @brief checkUpdate
     */
    void checkUpdate();

private:
    QNetworkAccessManager *networkAccessManager = nullptr;

signals:
    /**
     * @brief updateEvent
     * @param version 最新版本
     * @param url 最新版本下载地址
     */
    void updateEvent(QString version, QString url);

public slots:
};

#endif // UPDATER_H
