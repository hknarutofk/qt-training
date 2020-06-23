#ifndef DEBPKGINSTALLER_H
#define DEBPKGINSTALLER_H

#include <QObject>
#include "pkexecexecutor.h"

/**
  Deb格式文件安装管理器，负责deb包安装，启动可执行程序
 * @brief The DebPkgInstaller class
 */
class DebPkgInstaller : public QObject
{
    Q_OBJECT
public:
    explicit DebPkgInstaller(QString debPackagePath, QObject *parent = nullptr);
    ~DebPkgInstaller();
    void startInstall();

private:
    QString debPackagePath;
    QString cmd;
    PkexecExecutor *pkexec = nullptr;

signals:
    /**
      安装出错
     * @brief errorEvent
     * @param errorMessage 错误信息（中文）
     */
    void errorEvent(QString errorMessage);

    /**
      安装结束
     * @brief finishedEvent
     */
    void finishedEvent();

public slots:
    void onError(QString errorMessage);
    void onFinished();
};

#endif // DEBPKGINSTALLER_H
