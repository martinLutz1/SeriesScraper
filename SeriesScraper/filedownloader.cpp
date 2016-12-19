#include "filedownloader.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

FileDownloader::FileDownloader()
{

}

bool FileDownloader::downloadFile(QString url)
{
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
        downloadingSuccessful = true;
    } else
        qDebug() << "Failure" << reply->errorString();

    delete reply;
    return downloadingSuccessful;
}

QByteArray *FileDownloader::getDownloadedData()
{
    return &downloadedData;
}
