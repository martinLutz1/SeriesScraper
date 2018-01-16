#include "basefiledownloader.h"
#include <QImage>

BaseFileDownloader::BaseFileDownloader()
{
}

BaseFileDownloader::~BaseFileDownloader()
{
}

bool BaseFileDownloader::downloadFile(QString url)
{
    if (url.isEmpty())
    {
        lastSuccessUrl.clear();
        downloadedData.clear();
        return false;
    }
    else if (url == lastSuccessUrl) // Dont download twice
    {
        return true;
    }
    else
    {
        return download(url);
    }
}

void BaseFileDownloader::setData(QByteArray *data)
{
    downloadedData = *data;
}

QByteArray *BaseFileDownloader::getDownloadedData()
{
    return &downloadedData;
}

void BaseFileDownloader::setFilePath(QString filePath, QString fileName)
{
    QString newFileName = filePath + "/" + fileName;
    if (file.fileName() != newFileName)
    {
        file.setFileName(newFileName);
    }
}

bool BaseFileDownloader::saveFileAsImage(bool force)
{
    if (!file.exists() || force)
    {
        QImage image;
        image.loadFromData(downloadedData);
        return image.save(file.fileName());
    }
    return false;
}

bool BaseFileDownloader::fileExists()
{
    return file.exists();
}
