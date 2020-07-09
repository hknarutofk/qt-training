#include "mainwindow.h"
#include "fileiodialog.h"
#include "openssldialog.h"
#include <QApplication>
#include <QString>
#include <QDebug>
#include "httputil.h"
#include "updater.h"
#include "pkexecexecutor.h"
#include <QRegExp>
#include "base64imagedialog.h"
#include "debpkginstaller.h"
#include <openssl/md5.h>
#include <openssl/rsa.h>
#include <openssl/objects.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <QByteArray>
#include "mainwindow2.h"
#include "drawellipsedialog.h"
#include "gifdialog.h"
#include "log.h"
#include <QUrl>
#include <QProcess>
#include "capturescreendialog.h"

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
    QRegExp reg(".*, exitCode=(\\d+)\n");
    QString in = "_finished_command_:ls /, exitCode=0\n";
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

void testBase64(){
    QString url = "http://tool.chinaz.com/Tools/Base64.aspx";
    logDebug() << url;
    QString base64Url = QString::fromUtf8(url.toUtf8().toBase64());
    logDebug() << base64Url;
    logDebug() << QString::fromUtf8(QByteArray::fromBase64(base64Url.toUtf8()));

}

void testOpenssl(){
    RSA *rsa_publickey = NULL;
    BIO *bio = NULL;
    char *pubString = "-----BEGIN PUBLIC KEY-----\n"
                      "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA3/mncP8WG/w9X9X2L0qs\n"
                      "Pni0o1D8DGGPrDprwJXiYvm/wp+UpIQo9IMP2TxO4CRRC86Bsu8gjfZeViqz8qio\n"
                      "FXMB6ujnvqWDgJNAqwKzh+Q6SdxWkYZZfTUCEOh2OkjGSSsgdOF+ZVV9XiZrUcTb\n"
                      "XpTxE4eW5AG2Ii9bDK4AkKrDwOwb6IozuA4EGZPQg8EN0FzgycfYX4n40REzt68P\n"
                      "w/hZS9BbX2dPUYgJGLqghoiuQk5IRdvZx3oysvm41qZgZkrbar0gccyMXIoX61FA\n"
                      "78yzlyhcSwUsbkB1CO54iywiY2SoCkA3/e9ZoQdoHDjpIlLwAUz8eH71hB1QWjDG\n"
                      "dQIDAQAB\n"
                      "-----END PUBLIC KEY-----";
    int pubStringLen = strlen(pubString);
    bio = BIO_new_mem_buf(pubString, pubStringLen);
    rsa_publickey = PEM_read_bio_RSA_PUBKEY(bio, &rsa_publickey, NULL, NULL);
    printf("%X\n", rsa_publickey);
    RSA_print_fp(stdout, rsa_publickey, 0);
    BIO_free(bio);
}

void testUrlEncodeDecode(){
    QString param = "123,./:中文 ";
    QString encoded = QUrl::toPercentEncoding(param);
    logDebug() << encoded;
    param = QUrl::fromPercentEncoding(encoded.toUtf8());
    logDebug() << param;

    QUrl url("http://www.a.c/?p=123%2C.%2F%3A%E4%B8%AD%E6%96%87%20&z=cdfd&fdfs=.fdjls#432432");
    logDebug() << url.hasQuery();
    logDebug() << url.query();

}

void testParam(const QUrl &url){
    logDebug() << url;
}

void testffmpeg(){
    QProcess process;
    QStringList args;
    args << "-video_size" << "1332x841"<< "-framerate"<< "6"<< "-f"<< "x11grab"<< "-i"<< "$DISPLAY+1024x1024"<< "/tmp/Capturer_gif_20200706_134526_602.mp4";
    logDebug() << args;

    process.start("/usr/bin/ffmpeg", args);
    bool result = process.waitForStarted();
    logDebug() << result;
    result = process.waitForFinished();
    logDebug() << result;
    process.kill();
    result = process.waitForFinished();
    logDebug() << result;

    //test fail...
}

int main(int argc, char *argv[])
{ 

    QApplication a(argc, argv);    
    QString str = "abcdefffff";
    QString cn_str = "中文中文中文";
    QString mix_str = "bcdef中文文";

    logDebug() << str;
    logDebug() << cn_str;
    logDebug() << mix_str;

    logDebug() << str.length();
    logDebug() << str.size();
    logDebug() << str.toUtf8().size();

    logDebug() << cn_str.length();
    logDebug() << cn_str.size();
    logDebug() << cn_str.toUtf8().size();

    logDebug() << mix_str.length();
    logDebug() << mix_str.size();
    logDebug() << mix_str.toUtf8().size();
    return a.exec();
}
