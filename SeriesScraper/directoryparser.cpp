#include "directoryparser.h"
#include <QDebug>
#include <QCollator>
#include <QCoreApplication>

QStringList DirectoryParser::sortFiles(QStringList files)
{
    QStringList sortedFiles;
    std::vector<int> position = getEpisodePositions(files);

    if (int(position.size()) != files.size()) // Name scheme not found, let QT sort
    {
        foundSeason = 0;
        return files;
    }

    for (int i = 0; i < files.size(); i++)
    {
        while (sortedFiles.size() <= position.at(i))  // Prepare space
            sortedFiles.push_back("");
        if (position.at(i) >= 0)
            sortedFiles[position.at(i)] = files.at(i);
    }
    return sortedFiles;
}

QFileInfoList DirectoryParser::sortFiles(QFileInfoList files)
{
    QFileInfoList sortedFiles;
    QStringList filesQs;

    for (int i = 0; i < files.size(); i++)  // Get strings to calculate positions
        filesQs << files.at(i).filePath();

    std::vector<int> position = getEpisodePositions(filesQs);

    if (int(position.size()) < files.size()) // Name scheme not found, let QT sort
    {
        foundSeason = 0;
        return files;
    }

    for (int i = 0; i < files.size(); i++)
    {
        while (sortedFiles.size() <= position.at(i))  // Prepare space
            sortedFiles.push_back(QFileInfo(""));
        if (position.at(i) >= 0)
            sortedFiles[position.at(i)] = files.at(i);
    }
    return sortedFiles;
}

std::vector<int> DirectoryParser::getEpisodePositions(QStringList episodeList)
{
    std::vector<int> episodePosition;
    QRegularExpressionMatch seasonAndEpisodeMatch;
    QRegularExpressionMatch episodeNumberMatch;
    QRegularExpressionMatch seasonNumberMatch;

    for (int i = 0; i < episodeList.size(); i++)
    {
        seasonAndEpisodeMatch = seasonAndEpisodeExpression.match
                (episodeList.at(i).toLower(), 0, QRegularExpression::PartialPreferCompleteMatch);

        if (seasonAndEpisodeMatch.hasMatch())
        {
            QString seasonAndEpisodeText = seasonAndEpisodeMatch.captured();

            seasonNumberMatch = seasonNumberExpression.match(seasonAndEpisodeText, 0);
            QString seasonNumberText = seasonNumberMatch.captured();
            seasonNumberMatch = numberExpression.match(seasonNumberText, 0);
            foundSeason = seasonNumberMatch.captured().toInt();

            episodeNumberMatch = episodeNumberExpression.match(seasonAndEpisodeText, 0);
            QString episodeNumberText = episodeNumberMatch.captured();
            episodeNumberMatch = numberExpression.match(episodeNumberText, 0);
            int foundEpisodePosition = episodeNumberMatch.captured().toInt() - 1;
            episodePosition.push_back(foundEpisodePosition);
        }
    }
    return episodePosition;
}

void DirectoryParser::setNameFilterToAll()
{
    filter.clear();
    filter << "*.avi" << "*.mkv" << "*.mp4" << "*.m4v" << "*.mpg" << "*.flv" << ".*webm" << "*.ogv" << "*.mov" << "*.wmv";
}

DirectoryParser::DirectoryParser() : foundSeason(0)
{
    directory.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    directory.setSorting(QDir::NoSort);
    directory.setPath("");
    setNameFilterToAll();

    seasonAndEpisodeExpression.setPattern("(s)[0-9]+(.*)(e)[0-9]+");
    seasonNumberExpression.setPattern("(s)[0-9]*");
    episodeNumberExpression.setPattern("(e)[0-9]*");
    numberExpression.setPattern("[0-9]*$");
}

bool DirectoryParser::initializeDirectory(QString path)
{
    QDir directory(path);
    bool directoryExists = directory.exists();
    if (directoryExists)
        this->directory = directory;
    directoryPathInput = path;
    return directoryExists;
}

QString DirectoryParser::getDirectoryPathInput()
{
    return directoryPathInput;
}

QStringList DirectoryParser::getFiles()
{
    directory.setNameFilters(filter);
    QFileInfo fileInfo;
    QFileInfoList list = directory.entryInfoList();
    QStringList filesToReturn;

    for (int i = 0; i < list.size(); ++i)
    {
        fileInfo = list.at(i);
        if (fileInfo.isFile())
            filesToReturn << fileInfo.fileName();
    }
    filesToReturn = sortFiles(filesToReturn);
    return filesToReturn;
}

QStringList DirectoryParser::getFilesWithoutSuffix()
{
    QFileInfo fileInfo;
    QStringList fileList = getFiles();
    QStringList fileWithoutSuffix;

    for (int i = 0; i < fileList.size(); i++)
    {
        fileInfo.setFile(fileList.at(i));
        fileWithoutSuffix << fileInfo.completeBaseName();
    }
    return fileWithoutSuffix;
}

QStringList DirectoryParser::getFiles(QString suffix)
{
    filter = QStringList(suffix);
    QStringList fileList = getFiles();
    setNameFilterToAll();
    return fileList;
}

QStringList DirectoryParser::getFilesSuffix()
{
    QStringList suffixes;
    if (directory.exists())
    {
        directory.setNameFilters(filter);
        QFileInfoList fileList = directory.entryInfoList();
        fileList = sortFiles(fileList);

        for (int i = 0; i < fileList.size(); i++)
        {
            if (fileList.at(i).isFile())
                suffixes << fileList.at(i).suffix();
            else if(!fileList.at(i).isDir())
                suffixes << "";
        }
    }
    else
        suffixes << "";

    return suffixes;
}

int DirectoryParser::getFoundSeason()
{
    return foundSeason;
}
