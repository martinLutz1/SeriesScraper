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
    bool directorySet = false;
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
    std::vector<QStringList> pathStructure;
    bool containsRoot = false;

    QFileInfoList sortFiles(QFileInfoList files);
    QFileInfoList naturalSort(QFileInfoList files);
    QStringList naturalSort(QStringList toSort);
    std::vector<int> getEpisodePositions(QStringList episodeList);
    int getDirectoryPositionInList(QStringList directoryList, QString directoryToFind);
    void setPathStructure(int depth);
    void setFileInformation();

public:
    DirectoryParser();
    void setFileTypes(QStringList fileTypes);
    bool initializeDirectory(QString path);

    // Returns vector of directory lists, containing all siblings dirs along the path
    // The last vector tells the position of the current path directory in each list
    std::vector<QStringList> getPathStructure();
    QString getDirectoryViaStructure(int level, int selection);
    bool getStructureContainsRoot();
    QString getDirectoryPathInput();
    int getFoundSeason();
    QStringList getFiles();
    QStringList getFilesWithoutSuffix();
    QStringList getFilesSuffix();
};

#endif // DIRECTORYPARSER_H
