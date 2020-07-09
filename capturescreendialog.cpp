#include "capturescreendialog.h"
#include "ui_capturescreendialog.h"
#include "log.h"

CaptureScreenDialog::CaptureScreenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CaptureScreenDialog)
{
    ui->setupUi(this);
    process = new QProcess();
    connect(process , SIGNAL(readyReadStandardOutput()) , this , SLOT(onProcessReadoutput()));
    connect(process , SIGNAL(readyReadStandardError()) , this , SLOT(onReaderror()));
    connect(process , SIGNAL(finished(int, QProcess::ExitStatus)) , this , SLOT(onFinished(int, QProcess::ExitStatus)));
}

CaptureScreenDialog::~CaptureScreenDialog()
{
    delete ui;
}

void CaptureScreenDialog::on_pushButton_clicked()
{
    QString display = QProcessEnvironment::systemEnvironment().value("DISPLAY");
    QStringList args;
    args << "-video_size" << "1332x841"<< "-framerate"<< "6"<< "-f"<< "x11grab"<< "-i"<< display + "+1024x1024"<< "/tmp/Capturer_gif_20200706_134526_602.mp4";
    logDebug() << args;
    process->start("ffmpeg", args);
}

void CaptureScreenDialog::onProcessReadoutput()
{
    QString outStr = QString::fromUtf8(process->readAllStandardOutput().data());
    logDebug() << QString("stdout: %1").arg(outStr);
}

void CaptureScreenDialog::onReaderror()
{
    QString errStr = QString::fromUtf8(process->readAllStandardError().data());
    logDebug() << QString("stderr: %1").arg(errStr);
}

void CaptureScreenDialog::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    logDebug() << QString("finined %1").arg(exitCode);
}

void CaptureScreenDialog::on_pushButton_2_clicked()
{
    process->terminate();
}
