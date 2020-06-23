#include "debpkginstaller.h"
#include "log.h"

DebPkgInstaller::DebPkgInstaller(QString debPackagePath, QObject *parent): QObject(parent)
{
    this->debPackagePath = debPackagePath;
    cmd = QString("apt install -y -f %1").arg(debPackagePath);
    logDebug() << cmd;
    pkexec = new PkexecExecutor(cmd);
    connect(pkexec , SIGNAL(errorEvent(QString)) , this , SLOT(onError(QString)));
    connect(pkexec , SIGNAL(finishedEvent()) , this , SLOT(onFinished()));
}

DebPkgInstaller::~DebPkgInstaller()
{
    if(pkexec){
        delete pkexec;
    }
}

/**
 * 1. 执行apt install
 * 2. 执行apt 依赖安装
 * 3. 创建麒麟桌面快捷方式
 */
void DebPkgInstaller::startInstall()
{
    pkexec->start();
    logDebug() << "started";
    emit errorEvent("test");
}

void DebPkgInstaller::onError(QString errorMessage)
{
    logDebug() << QString("get error： %1").arg(errorMessage);
    emit errorEvent(errorMessage);//向上传递
}

void DebPkgInstaller::onFinished()
{
    logDebug() << "finished";
    emit finishedEvent();//向上传递
    logDebug() "emit finishedEvent";
}
