#ifndef BASEFILEDOWNLOADER_H
#define BASEFILEDOWNLOADER_H

#include <QString>
#include <QByteArray>
#include <QFile>

class BaseFileDownloader
{
public:
    BaseFileDownloader();
    virtual ~BaseFileDownloader();
    bool downloadFile(QString url);
    void setData(QByteArray *data);
    QByteArray *getDownloadedData();
    void setFilePath(QString filePath, QString fileName);
    bool saveFileAsImage(bool force = false);
    bool fileExists();

protected:
    virtual bool download(QString url) = 0;
    QString lastSuccessUrl;
    QByteArray downloadedData;
    QFile file;
};

#endif // BASEFILEDOWNLOADER_H
