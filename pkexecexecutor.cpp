#include "pkexecexecutor.h"
#include <QProcess>
#include "log.h"

PkexecExecutor::PkexecExecutor(QString script, QObject *parent) : QObject(parent)
{
    this->script = script;
    logDebug() << script;
    process = new QProcess();
    connect(process , SIGNAL(readyReadStandardOutput()) , this , SLOT(onProcessReadoutput()));
    connect(process , SIGNAL(readyReadStandardError()) , this , SLOT(onReaderror()));
    connect(process , SIGNAL(finished(int, QProcess::ExitStatus)) , this , SLOT(onFinished(int, QProcess::ExitStatus)));
    step = 0;

}

PkexecExecutor::~PkexecExecutor()
{
    if(process){
        delete process;
    }
}

void PkexecExecutor::start()
{
    logDebug() << "starting bash with root privilges";
    process->start("pkexec bash");
    if(process->waitForStarted()){
        logDebug() << "process started";
        step = 1;
        logDebug() << "step1";
        process->write("whoami\n");
    }
    else{
        logDebug() << "process cannot start";
        emit errorEvent("内部错误，安装程序启动失败");
        emit finishedEvent();
    }
}

void PkexecExecutor::onProcessReadoutput()
{
    QString outStr = QString::fromUtf8(process->readAllStandardOutput().data());
    logDebug() << QString("stdout: %1").arg(outStr);

    //简单状态机判断
    switch (step) {
    //检测root权限
    case 1:
        if(outStr.remove("\n").compare(STR_ROOT) == 0){
            //检测成功，切换到安装指令执行阶段
            step = 2;
            logDebug() << "get root privileges, start to execute script";
            process->write(script.toUtf8());
            //写入回车符号，开始执行。 如果有多行脚本，采用\n分割
            process->write("\n");
            //写入退出指令，待安装程序执行完毕，自动退出
            process->write("exit $?\n");
        }
        else {
            logDebug() << "cannot get root privilges, exit";
            emit errorEvent("未能获取root权限");
            process->kill();
            emit finishedEvent();
        }
        break;
    case 2:
        //暂时不判断回显
        break;
    default:
        break;
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
