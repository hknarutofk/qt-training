#ifndef PKEXECUTIL_H
#define PKEXECUTIL_H

#include <QObject>
#include <QProcess>
/**
  封装操作系统pkexec调用，用于获取root权限
 * @brief The PkexecUtil class
 */
class PkexecExecutor : public QObject
{
    Q_OBJECT

private:
    QString script;
    QProcess *process = nullptr;
    /**
      用于异步判断命令阶段
      0=初始值， 1=检测root， 2=执行安装， 其他待补充
     * @brief step
     */
    int step;

public:
    /**
      执行原理 echo scrpit | pkexec sh
     * @brief PkexecExecutor
     * @param script 多条指令采用;分割
     */
    explicit PkexecExecutor(QString script, QObject *parent = nullptr);
    ~PkexecExecutor();
    void start();


    const QString STR_ROOT="root";

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
    void onProcessReadoutput();
    void onReaderror();
    void onFinished(int, QProcess::ExitStatus);
};

#endif // PKEXECUTIL_H
