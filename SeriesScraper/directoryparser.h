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
    QRegularExpression seasonAndEpisodeExpression;
    QRegularExpression episodeNumberExpression;
    QRegularExpression seasonNumberExpression;
    QRegularExpression numberExpression;
    QStringList filter;

    int foundSeason;

    QStringList sortFiles(QStringList files);
    QFileInfoList sortFiles(QFileInfoList files);
    std::vector<int> getEpisodePositions(QStringList episodeList);
    void setNameFilterToAll();

public:
    DirectoryParser();
    bool initializeDirectory(QString path);
    QString getDirectoryPathInput();
    QStringList getFiles();
    QStringList getFilesWithoutSuffix();
    QStringList getFiles(QString suffix);
    QStringList getFilesSuffix();
    int getFoundSeason();
};

#endif // DIRECTORYPARSER_H
