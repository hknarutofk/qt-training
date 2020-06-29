#ifndef PKEXECUTIL_H
#define PKEXECUTIL_H

#include <QObject>
#include <QProcess>
#include <QMutex>
#include <QSemaphore>
/**
  封装操作系统pkexec调用，用于获取root权限
  采用单例模式，整个进程只需要用户输入一次密码，保持具有root权限的bash
 * @brief The PkexecUtil class
 */
class PkexecExecutor : public QObject
{
    Q_OBJECT

private:
    QProcess *process = nullptr;    
    QSemaphore semaphore;

    //声明静态变量
    static PkexecExecutor *instance;
    static QMutex mutex;

    /**
      执行原理 echo scrpit | pkexec sh
     * @brief PkexecExecutor
     * @param script 多条指令采用;分割
     */
    PkexecExecutor();
    /**
      立即触发pkexec bash弹出系统授权窗口
     * @brief start
     */
    void start();

public:
    ~PkexecExecutor();

    /**
      获取实例，立即触发pkexec bash弹出系统授权窗口
     * @brief getInstance
     * @return
     */
    static PkexecExecutor *getInstance();

    /**
        在root权限下执行，等价于系统sudo
     * @brief sudo
     * @param script
     */
    void sudo(QString script);

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
