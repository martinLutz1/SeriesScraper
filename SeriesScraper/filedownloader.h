#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QString>
#include <QByteArray>
#include <QFile>

class FileDownloader
{
public:
    FileDownloader();
    bool downloadFile(QString url);
    void setData(QByteArray *data);
    QByteArray *getDownloadedData();
    void setFilePath(QString filePath, QString fileName);
    bool saveFileAsImage(bool force = false);
    bool fileExists();

private:
    QString lastSuccessUrl;
    QByteArray downloadedData;
    QFile file;
};

#endif // FILEDOWNLOADER_H
