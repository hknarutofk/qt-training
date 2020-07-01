#include "downloadmanager.h"
#include <QTextStream>
#include <cstdio>
#include "log.h"

DownloadManager::DownloadManager(QObject *parent)
    : QObject(parent)
{
}

void DownloadManager::setUrl(const QUrl &url)
{
    this->url = url;
}

void DownloadManager::setOutPath(const QString &outPath)
{
    this->outPath = outPath;
    logDebug() << outPath;
}

QString DownloadManager::getSaveFileName()
{
    if(url.isEmpty()){
        return "";
    }
    QString path = url.path();
    QString basename = QFileInfo(path).fileName();
    return basename;
}

void DownloadManager::startDownload()
{
    QString filename = getSaveFileName();
    output.setFileName(outPath);
    if (!output.open(QIODevice::WriteOnly)) {
        logDebug() << "Problem opening save file '%s' for download '%s': %s\n" << qPrintable(filename) << url.toEncoded().constData() <<  qPrintable(output.errorString());
        return;                 // skip this download
    }

    QNetworkRequest request(url);
    currentDownload = manager.get(request);
    connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)),
            SLOT(downloadProgress(qint64,qint64)));
    connect(currentDownload, SIGNAL(finished()),
            SLOT(downloadFinished()));
    connect(currentDownload, SIGNAL(readyRead()),
            SLOT(downloadReadyRead()));

    // prepare the output
    logDebug() << QString("Downloading %1...").arg(url.toEncoded().constData());
    downloadTime.start();
}

void DownloadManager::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    progressBar.setStatus(bytesReceived, bytesTotal);

    // calculate the download speed
    double speed = bytesReceived * 1000.0 / downloadTime.elapsed();
    QString unit;
    if (speed < 1024) {
        unit = "bytes/sec";
    } else if (speed < 1024*1024) {
        speed /= 1024;
        unit = "kB/s";
    } else {
        speed /= 1024*1024;
        unit = "MB/s";
    }

    progressBar.setMessage(QString::fromLatin1("%1 %2")
                           .arg(speed, 3, 'f', 1).arg(unit));
    progressBar.update();
    emit downloadProgressEvent(bytesReceived, bytesTotal);
}

void DownloadManager::downloadFinished()
{
    progressBar.clear();
    output.close();

    if (currentDownload->error()) {
        // download failed
        fprintf(stderr, "Failed: %s\n", qPrintable(currentDownload->errorString()));
        output.remove();
    } else {
        // let's check if it was actually a redirect
        if (isHttpRedirect()) {
            reportRedirect();
            output.remove();
        } else {
            printf("Succeeded.\n");            
        }
    }

    currentDownload->deleteLater();
    emit finishedEvent();
}

void DownloadManager::downloadReadyRead()
{
    output.write(currentDownload->readAll());
}

bool DownloadManager::isHttpRedirect() const
{
    int statusCode = currentDownload->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    return statusCode == 301 || statusCode == 302 || statusCode == 303
           || statusCode == 305 || statusCode == 307 || statusCode == 308;
}

void DownloadManager::reportRedirect()
{
    int statusCode = currentDownload->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QUrl requestUrl = currentDownload->request().url();
    logDebug() << "Request: " << requestUrl.toDisplayString()
                        << " was redirected with code: " << statusCode
                        << '\n';

    QVariant target = currentDownload->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (!target.isValid())
        return;
    QUrl redirectUrl = target.toUrl();
    if (redirectUrl.isRelative())
        redirectUrl = requestUrl.resolved(redirectUrl);
    logDebug() << "Redirected to: " << redirectUrl.toDisplayString()
                        << '\n';
}
