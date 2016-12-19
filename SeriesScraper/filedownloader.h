#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QByteArray>

class FileDownloader
{
public:
    FileDownloader();
    bool downloadFile(QString url);
    QByteArray *getDownloadedData();

private:
    QByteArray downloadedData;
};

#endif // FILEDOWNLOADER_H
