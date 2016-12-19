#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QString>
#include <QByteArray>

class FileDownloader
{
public:
    FileDownloader();
    bool downloadFile(QString url);
    QByteArray *getDownloadedData();

private:
    QString lastSuccessUrl;
    QByteArray downloadedData;
};

#endif // FILEDOWNLOADER_H
