#ifndef LOG2_H
#define LOG2_H

#include <QString>
#include <QTextBrowser>
#include <QThread>

class Log4TextBrowser
{
public:
    Log4TextBrowser();
    inline Log4TextBrowser operator()(){
        return *this;
    }

    inline Log4TextBrowser operator<<(QString str){
        append(str.toUtf8());
        return *this;
    }

    inline Log4TextBrowser operator<<(long l){
        append(QString("%1").arg(l));
        return *this;
    }

    void append(QString str);
    void setTextBrowser(QTextBrowser *textBrowser);

private:
    QTextBrowser *tb;
};

static Log4TextBrowser log2;
//#define logDebug() log2() << (long)QThread::currentThread()->currentThreadId() <<  __FUNCTION__ << "(" << __FILE__ << ":" << __LINE__ << ")__"
#define logDebug() log2() << (long)QThread::currentThread()->currentThreadId() <<  __FUNCTION__ << "(" << __FILE__ << ":" << __LINE__ << ")__"
#endif // LOG2_H
