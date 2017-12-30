#ifndef DIRECTORYPARSER_H
#define DIRECTORYPARSER_H

#include <QDir>
#include <QStringList>
#include <QRegularExpression>
#include <vector>

#include "episodenamehandler.h"

class DirectoryParser
{
private:
    QRegularExpression seasonAndEpisodeExpression = QRegularExpression("(s|S)[0-9]+(.*)(e|E)[0-9]+"); // S01E01
    QRegularExpression seasonNumberExpression = QRegularExpression("(s|S)[0-9]*"); // S01
    QRegularExpression episodeNumberExpression = QRegularExpression("(e|E)[0-9]*"); // E01
    QRegularExpression seasonSeparatorEpisodeExpression = QRegularExpression("[0-9]+(x|X|\\.|\\-)[0-9]+"); // 1x1 / 1.1 / 1-1
    QRegularExpression seasonSeparatorNumberExpression = QRegularExpression("[0-9]+(x|X|\\.|\\-)"); // 1x / 1. / 1-
    QRegularExpression episodeSeparatorNumberExpression = QRegularExpression("(x|X|\\.|\\-)[0-9]+"); // x1 / .1 / -1
    QRegularExpression digitOnlySeasonAndEpisodeExpression = QRegularExpression("[0-9]+[0-9]+[0-9]+"); // 101
    QRegularExpression numberExpression = QRegularExpression("[0-9]+");
    QDir directory = QDir::home();
    bool directorySet = false;
    QString directoryPathInput;
    QStringList filter;
    int foundSeason = 0;
    QStringList sortedFiles;
    QStringList sortedFileWithoutSuffix;
    QStringList suffixes;
    Positions positionsValidity;
    std::vector<QStringList> pathStructure;
    bool containsRoot = false;
    enum class NameSchemeType { seasonAndEpisode, seasonSeparatorEpisode, digitOnly, none };

    NameSchemeType getNameSchemeType(QString filename);
    QFileInfoList sortFiles(QFileInfoList files);
    QFileInfoList naturalSort(QFileInfoList files);
    QStringList naturalSort(QStringList toSort);
    int getSeason(QString fileName, int amountFiles, NameSchemeType type);
    int getEpisodePositionOfSeasonAndEpisode(QString fileName, std::vector<int> positions);
    int getEpisodePositionOfSeasonSeparatorEpisode(QString fileName, std::vector<int> positions);
    int getEpisodePositionOfDigitOnly(QString fileName, int amountFiles, std::vector<int> positions);
    int getEpisodeLengthOfDigitOnly(int amountFiles);
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
    QDir getDirectory();
    int getFoundSeason();
    QStringList getFilesWithoutSuffix();
    QStringList getFilesSuffix();
    Positions getFilePositions();
};

#endif // DIRECTORYPARSER_H
