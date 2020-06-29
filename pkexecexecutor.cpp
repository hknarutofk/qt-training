#include "pkexecexecutor.h"
#include <QProcess>
#include "log.h"

//定义静态变量
PkexecExecutor *PkexecExecutor::instance;
QMutex PkexecExecutor::mutex;

PkexecExecutor::PkexecExecutor()
{
    process = new QProcess();
    connect(process , SIGNAL(readyReadStandardOutput()) , this , SLOT(onProcessReadoutput()));
    connect(process , SIGNAL(readyReadStandardError()) , this , SLOT(onReaderror()));
    connect(process , SIGNAL(finished(int, QProcess::ExitStatus)) , this , SLOT(onFinished(int, QProcess::ExitStatus)));
}

PkexecExecutor::~PkexecExecutor()
{
    if(process->isOpen()){
        process->kill();
    }
    process->deleteLater();
}

void PkexecExecutor::start()
{
    logDebug() << "starting bash with root privilges";
    process->start("pkexec bash");
    if(process->waitForStarted()){
        logDebug() << "process started";
    }
    else{
        logDebug() << "process cannot start";
        emit errorEvent("内部错误，安装程序启动失败");
        emit finishedEvent();
    }
}

PkexecExecutor *PkexecExecutor::getInstance()
{
    if(instance == nullptr){
        mutex.lock();
        if(instance == nullptr){
            instance = new PkexecExecutor();
            instance->start();
        }
        mutex.unlock();
    }
    return instance;
}

void PkexecExecutor::sudo(QString script)
{
    logDebug() << "lock"; //强制排队
    mutex.lock();
    logDebug() << script;
    process->write(script.toUtf8());
    //写入回车符号，开始执行。 如果有多行脚本，采用\n分割
    process->write("\n");

    //写入结束标识，用于判断指令执行完毕
    process->write(QString("echo _finished_command_:%1, exitCode=`echo $?`\n").arg(script).toUtf8());
}

void PkexecExecutor::onProcessReadoutput()
{
    QString outStr = QString::fromUtf8(process->readAllStandardOutput().data());
    logDebug() << QString("stdout: %1").arg(outStr);
    if(outStr.startsWith("_finished_command_")){
        // 调用类接受到此事件，应当立即断开finishedEvent信号槽连接
        mutex.unlock();
        logDebug() << "unlock";
        emit finishedEvent();
    }
}

void PkexecExecutor::onReaderror()
{
    QString errStr = QString::fromUtf8(process->readAllStandardError().data());
    logDebug() << QString("stderr: %1").arg(errStr);
}

void PkexecExecutor::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    logDebug() << QString("finined %1").arg(exitCode);
    emit finishedEvent();
}
