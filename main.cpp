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
#include "debpkginstaller.h"
#include <openssl/md5.h>
#include <openssl/rsa.h>
#include <openssl/objects.h>
#include <openssl/bio.h>
#include <openssl/pem.h>
#include <QByteArray>

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


int main(int argc, char *argv[])
{ 
    testQRegex();
    return 0;
    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();
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

    return a.exec();
}
