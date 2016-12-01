#ifndef DIRECTORYPARSER_H
#define DIRECTORYPARSER_H

#include <QDir>
#include <QStringList>
#include <QRegularExpression>
#include <vector>

class DirectoryParser
{
private:
    QDir directory;
    QString directoryPathInput;
    QRegularExpression episodeNumberExpression;
    QRegularExpression numberFromEpisodeNumberExpression;
    QStringList filter;

    QStringList sortFiles(QStringList files);
    QFileInfoList sortFiles(QFileInfoList files);
    void setNameFilterToAll();

public:
    DirectoryParser();
    bool initializeDirectory(QString path);
    QString getDirectoryPathInput();
    QStringList getFiles();
    QStringList getFilesWithoutExtension();
    QStringList getFiles(QString extension);
    QStringList getFilesSuffix();
    std::vector<int> getEpisodePositions(QStringList episodeList);
};

#endif // DIRECTORYPARSER_H
