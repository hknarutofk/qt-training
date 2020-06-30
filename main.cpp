#include "mainwindow.h"
#include "fileiodialog.h"
#include "openssldialog.h"
#include <QApplication>
#include <QString>
#include <QDebug>
#include "httputil.h"
#include "log.h"
#include "updater.h"
#include "pkexecexecutor.h"
#include <QRegExp>
#include "base64imagedialog.h"

void testQString(){
    char * buffer = "abcd中文";
    QString qstr = QString::fromLocal8Bit(buffer, 4);
    qDebug()<< qstr;

    qDebug() << QString("123131 %1").arg("zzzz");
}

void testInt(){
    char buffer[4];
    buffer[0] = 1;
    buffer[1]=1;
    buffer[2]=1;
    buffer[3]=1;
    int i = *(int *)buffer;
    qDebug() << i;


    int a, *p;
    p = (int *)buffer;
    a = *p;
    qDebug() << a;

}

void testQRegex(){
    QRegExp reg(".*aaa=(\\d+).*");
    QString in = "aaa=1z,aaa=22fdf";
    bool result = reg.exactMatch(in);
    logDebug() << result;
    if(result){
        logDebug() << reg.cap(1);
    }

}

void testQRegex2(){
    QRegExp rx("(\\d+)");
    QString str = "Offsets: 12 14 99 231 7";
    QStringList list;
    int pos = 0;

    while ((pos = rx.indexIn(str, pos)) != -1) {
        list << rx.cap(1);
        pos += rx.matchedLength();
    }
    logDebug() << list;
}


int main(int argc, char *argv[])
{ 
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    Base64ImageDialog dlg;
    dlg.show();

    return a.exec();
}
