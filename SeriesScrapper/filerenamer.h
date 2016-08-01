#ifndef FILERENAMER_H
#define FILERENAMER_H

#include <QStringList>
#include <QDir>


class FileRenamer
{
public:
    FileRenamer();
    void setFiles(QStringList sortedFilesWithSpaces);
    void setEpisodeNames(QStringList episodes);
    void setDirectory(QDir directory);
    bool rename();

private:
    QStringList fileList;
    QStringList episodeList;
    QDir workingDirectory;
};

#endif // FILERENAMER_H
