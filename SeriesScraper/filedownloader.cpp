#include "filedownloader.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QFile>
#include <QImage>

FileDownloader::FileDownloader()
{

}

bool FileDownloader::downloadFile(QString url)
{
    if (url.isEmpty())
    {
        lastSuccessUrl.clear();
        downloadedData.clear();
        return false;
    }
    else if (url == lastSuccessUrl) // Dont download twice
        return true;

    bool downloadingSuccessful = false;
    // Create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // The HTTP request
    QNetworkRequest req(url);
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // Blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError)
    {
        downloadedData = reply->readAll();
        lastSuccessUrl = url;
        downloadingSuccessful = true;
    } else
        qDebug() << "Failure at downloading file:" << reply->errorString();

    reply->deleteLater();
    return downloadingSuccessful;
}

void FileDownloader::setData(QByteArray *data)
{
    downloadedData = *data;
}

QByteArray *FileDownloader::getDownloadedData()
{
    return &downloadedData;
}

void FileDownloader::setFilePath(QString filePath, QString fileName)
{
    QString newFileName = filePath + "/" + fileName;
    if (file.fileName() != newFileName)
        file.setFileName(newFileName);
}

bool FileDownloader::saveFileAsImage(bool force)
{
    if (!file.exists() || force)
    {
        QImage image;
        image.loadFromData(downloadedData);
        return image.save(file.fileName());
    }
    return false;
}

bool FileDownloader::fileExists()
{
    return file.exists();
}
