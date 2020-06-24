#include "mainwindow.h"
#include "fileiodialog.h"
#include "openssldialog.h"
#include <QApplication>
#include <QString>
#include <QDebug>
#include "httputil.h"
#include "log.h"
#include "updater.h"

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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
