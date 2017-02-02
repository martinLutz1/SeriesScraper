#include "directoryparser.h"
#include <QCoreApplication>
#include <QCollator>
#include <QDebug>

QFileInfoList DirectoryParser::sortFiles(QFileInfoList files)
{
    QFileInfoList sortedFiles;
    QStringList fileList;

    for (int i = 0; i < files.size(); i++)  // Get strings to calculate positions
        fileList << files.at(i).fileName();

    std::vector<int> position = getEpisodePositions(fileList);


    if (int(position.size()) < files.size()) // Name scheme not found, natural sort
    {
        sortedFiles = naturalSort(files);
    } else // Sort by found positions
    {
        for (int i = 0; i < files.size(); i++)
        {
            while (sortedFiles.size() <= position.at(i))  // Prepare space
                sortedFiles.push_back(QFileInfo(""));
            if (position.at(i) >= 0)
                sortedFiles[position.at(i)] = files.at(i);
        }
    }
    return sortedFiles;
}

QFileInfoList DirectoryParser::naturalSort(QFileInfoList files)
{
    // Use strings to use collators natural sort function
    QStringList fileList;
    for (int i = 0; i < files.size(); i ++)
        fileList << files.at(i).absoluteFilePath();

    QCollator collator;
    collator.setNumericMode(true);
    std::sort(fileList.begin(), fileList.end(),
              [&collator](const QString &file1, const QString &file2)
    {
        return collator.compare(file1, file2) < 0;
    });

    // Convert strings back to fileInfo
    QFileInfoList fileInfos;
    for (int i = 0; i < fileList.size(); i ++)
        fileInfos << QFileInfo(fileList.at(i));
    return fileInfos;
}

std::vector<int> DirectoryParser::getEpisodePositions(QStringList episodeList)
{
    std::vector<int> episodePosition;
    QRegularExpressionMatch seasonAndEpisodeMatch;
    QRegularExpressionMatch episodeNumberMatch;
    QRegularExpressionMatch seasonNumberMatch;

    // Set season
    if (episodeList.size() > 0)
    {
        seasonAndEpisodeMatch = seasonAndEpisodeExpression.match
                (episodeList.at(0).toLower(), 0, QRegularExpression::PartialPreferCompleteMatch);

        if (seasonAndEpisodeMatch.hasMatch())
        {
            QString seasonAndEpisodeText = seasonAndEpisodeMatch.captured();

            seasonNumberMatch = seasonNumberExpression.match(seasonAndEpisodeText, 0);
            QString seasonNumberText = seasonNumberMatch.captured();
            seasonNumberMatch = numberExpression.match(seasonNumberText, 0);
            foundSeason = seasonNumberMatch.captured().toInt();
        }
    }

    // Get episode positions
    for (int i = 0; i < episodeList.size(); i++)
    {
        seasonAndEpisodeMatch = seasonAndEpisodeExpression.match
                (episodeList.at(i).toLower(), 0, QRegularExpression::PartialPreferCompleteMatch);

        if (seasonAndEpisodeMatch.hasMatch())
        {
            QString seasonAndEpisodeText = seasonAndEpisodeMatch.captured();

            episodeNumberMatch = episodeNumberExpression.match(seasonAndEpisodeText, 0);
            QString episodeNumberText = episodeNumberMatch.captured();
            episodeNumberMatch = numberExpression.match(episodeNumberText, 0);
            int foundEpisodePosition = episodeNumberMatch.captured().toInt() - 1;
            episodePosition.push_back(foundEpisodePosition);
        }
    }

    // Return empty vector, if multiple indexes with the same position exist
    std::vector<int> sortedEpisodePositions = episodePosition;
    std::sort(sortedEpisodePositions.begin(), sortedEpisodePositions.end());
    for (int i = 1; i < int(sortedEpisodePositions.size()); i++)
    {
        if (sortedEpisodePositions.at(i - 1) == sortedEpisodePositions.at(i))
            return std::vector<int>();
    }
    return episodePosition;
}

void DirectoryParser::setFileInformation()
{
    directory.setFilter(QDir::Files);
    QFileInfoList fileInfoList = directory.entryInfoList(filter);
    QFileInfoList sortedFileInfoList = sortFiles(fileInfoList);

    QStringList newSortedFiles;
    QStringList newSortedFilesWithoutSuffix;
    QStringList newSuffixes;

    QFileInfo fileInfo;
    for (int i = 0; i < sortedFileInfoList.size(); ++i)
    {
        fileInfo = sortedFileInfoList.at(i);
        if (fileInfo.isFile())
        {
            newSortedFiles << fileInfo.fileName();
            newSortedFilesWithoutSuffix << fileInfo.completeBaseName();
            newSuffixes << fileInfo.suffix();
        } else if (!fileInfo.isDir())
        {
            newSortedFiles << "";
            newSortedFilesWithoutSuffix << "";
            newSuffixes << "";
        }
    }

    sortedFiles = newSortedFiles;
    sortedFileWithoutSuffix = newSortedFilesWithoutSuffix;
    suffixes = newSuffixes;
}

DirectoryParser::DirectoryParser() : foundSeason(0)
{
    directory.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    directory.setSorting(QDir::NoSort);
    directory.setPath("");

    seasonAndEpisodeExpression.setPattern("(s)[0-9]+(.*)(e)[0-9]+");
    seasonNumberExpression.setPattern("(s)[0-9]*");
    episodeNumberExpression.setPattern("(e)[0-9]*");
    numberExpression.setPattern("[0-9]*$");
}

void DirectoryParser::setFileTypes(QStringList fileTypes)
{
    for (int i = 0; i < fileTypes.size(); i++)
        fileTypes[i] = "*." + fileTypes.at(i);
    filter = fileTypes;
    directory.setNameFilters(filter);
}

bool DirectoryParser::initializeDirectory(QString path)
{
    QDir directory(path);
    bool directoryExists = directory.exists();
    foundSeason = 0;
    if (directoryExists)
    {
        this->directory = directory;
        setFileInformation();
    }
    directoryPathInput = path;
    return directoryExists;
}

QString DirectoryParser::getDirectoryPathInput()
{
    return directoryPathInput;
}

int DirectoryParser::getFoundSeason()
{
    return foundSeason;
}

QStringList DirectoryParser::getFiles()
{
    return sortedFiles;
}

QStringList DirectoryParser::getFilesWithoutSuffix()
{
    return sortedFileWithoutSuffix;
}

QStringList DirectoryParser::getFilesSuffix()
{
    return suffixes;
}
