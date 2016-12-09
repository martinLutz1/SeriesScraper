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
    QStringList filter;
    QRegularExpression seasonAndEpisodeExpression;
    QRegularExpression episodeNumberExpression;
    QRegularExpression seasonNumberExpression;
    QRegularExpression numberExpression;

    int foundSeason;
    QStringList sortedFiles;
    QStringList sortedFileWithoutSuffix;
    QStringList suffixes;

    QFileInfoList sortFiles(QFileInfoList files);
    QFileInfoList naturalSort(QFileInfoList files);
    std::vector<int> getEpisodePositions(QStringList episodeList);
    void setFileInformation();

public:
    DirectoryParser();
    void setFileTypes(QStringList fileTypes);
    bool initializeDirectory(QString path);

    QString getDirectoryPathInput();
    int getFoundSeason();
    QStringList getFiles();
    QStringList getFilesWithoutSuffix();
    QStringList getFilesSuffix();

};

#endif // DIRECTORYPARSER_H
