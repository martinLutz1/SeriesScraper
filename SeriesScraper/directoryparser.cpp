#include "directoryparser.h"
#include <QCoreApplication>
#include <QCollator>
#include <QDebug>
#include <cmath>
#include <unordered_map>
#include "mainwindow.h" // Path structure box number

DirectoryParser::NameSchemeType DirectoryParser::getNameSchemeType(QString filename)
{
    bool isSeasonAndEpisode = seasonAndEpisodeExpression.match(filename, 0, QRegularExpression::PartialPreferCompleteMatch).hasMatch();
    if (isSeasonAndEpisode)
    {
        return NameSchemeType::seasonAndEpisode;
    }

    bool isSeasonSeparatorEpisode = seasonSeparatorEpisodeExpression.match(filename, 0, QRegularExpression::PartialPreferCompleteMatch).hasMatch();
    if (isSeasonSeparatorEpisode)
    {
        return NameSchemeType::seasonSeparatorEpisode;
    }

    bool isDigitOnly = digitOnlySeasonAndEpisodeExpression.match(filename, 0, QRegularExpression::PartialPreferCompleteMatch).hasMatch();
    if (isDigitOnly)
    {
        return NameSchemeType::digitOnly;
    }

    return NameSchemeType::none;
}

QFileInfoList DirectoryParser::sortFiles(QFileInfoList files)
{
    positionsValidity.clear();

    QStringList fileNames;
    QFileInfoList sortedFiles;

    for (const auto& file: files)
    {
        fileNames << file.fileName();
    }

    std::vector<int> position = getEpisodePositions(fileNames);

    // Name scheme not found, natural sort
    if (int(position.size()) < fileNames.size())
    {
        sortedFiles = naturalSort(files);
    }
    // Sort by found positions
    else
    {
        QFileInfoList unsureFiles;

        for (int i = 0; i < files.size(); i++)
        {
            const auto foundPosition = position.at(i);

            // No season should be larger than 10.000 episodes.
            // We avoid crashing on too large numbers.
            if (foundPosition > 10000)
            {
                break;
            }

            while (sortedFiles.size() <= foundPosition)
            {
                sortedFiles.push_back(QFileInfo());
                positionsValidity.push_back(EpisodeName::Position::unsure);
            }

            if (foundPosition >= 0)
            {
                sortedFiles[foundPosition] = files.at(i);
                positionsValidity[foundPosition] = EpisodeName::Position::determined;
            }
            else
            {
                unsureFiles.push_back(files.at(i));
            }
        }

        // Insert files whose positions where unsure.
        if (!unsureFiles.isEmpty())
        {
            for (auto i = 0; i < sortedFiles.size(); i++)
            {
                if (positionsValidity.at(i) == EpisodeName::Position::unsure)
                {
                    sortedFiles[i] = unsureFiles.front();
                    unsureFiles.pop_front();

                    if (unsureFiles.isEmpty())
                    {
                        break;
                    }
                }
            }
            // If there are not enough positions to be filled,
            // just attach the unsure files to the end.
            for (auto unsureFile: unsureFiles)
            {
                sortedFiles.push_back(unsureFile);
                positionsValidity.push_back(EpisodeName::Position::unsure);
            }
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
              [&collator](const QString& file1, const QString& file2)
    {
        return collator.compare(file1, file2) < 0;
    });

    // Convert strings back to fileInfo
    QFileInfoList fileInfos;
    for (int i = 0; i < fileList.size(); i ++)
        fileInfos << QFileInfo(fileList.at(i));
    return fileInfos;
}

QStringList DirectoryParser::naturalSort(QStringList toSort)
{
    QStringList sorted = toSort;
    QCollator collator;
    collator.setNumericMode(true);
    std::sort(sorted.begin(), sorted.end(),
              [&collator](const QString& string1, const QString& string2)
    {
        return collator.compare(string1, string2) < 0;
    });
    return sorted;
}

int DirectoryParser::getSeason(QString fileName, int amountFiles, NameSchemeType type)
{
    int season = 0;
    switch (type)
    {
    case NameSchemeType::seasonAndEpisode:
    {
        QRegularExpressionMatch seasonAndEpisodeMatch = seasonAndEpisodeExpression.match
                (fileName, 0, QRegularExpression::PartialPreferCompleteMatch);

        if (seasonAndEpisodeMatch.hasMatch())
        {
            QString seasonAndEpisodeText = seasonAndEpisodeMatch.captured();
            QString seasonNumberText = seasonNumberExpression.match(seasonAndEpisodeText, 0).captured();
            season = numberExpression.match(seasonNumberText, 0).captured().toInt();
        }
        break;
    }
    case NameSchemeType::seasonSeparatorEpisode:
    {
        QRegularExpressionMatch seasonSeparatorEpisodeMatch = seasonSeparatorEpisodeExpression.match
                (fileName, 0, QRegularExpression::PartialPreferCompleteMatch);

        if (seasonSeparatorEpisodeMatch.hasMatch())
        {
            QString seasonSeparatorEpisodeText = seasonSeparatorEpisodeMatch.captured();
            QString seasonNumberText = seasonSeparatorNumberExpression.match(seasonSeparatorEpisodeText, 0).captured();
            season = numberExpression.match(seasonNumberText, 0).captured().toInt();
        }
        break;
    }
    case NameSchemeType::digitOnly:
    {
        QRegularExpressionMatch digitOnlyMatch = digitOnlySeasonAndEpisodeExpression.match
                (fileName, 0, QRegularExpression::PartialPreferCompleteMatch);

        if (digitOnlyMatch.hasMatch())
        {
            QString digitOnlyText = digitOnlyMatch.captured();
            int seasonLength = digitOnlyText.length() - getEpisodeLengthOfDigitOnly(amountFiles);
            season = digitOnlyText.left(seasonLength).toInt();
        }
        break;
    }
    case NameSchemeType::none:
    default:
    {
        break;
    }
    }
    return season;
}

int DirectoryParser::getEpisodePositionOfSeasonAndEpisode(QString fileName, std::vector<int> positions)
{
    QRegularExpressionMatch seasonAndEpisodeMatch = seasonAndEpisodeExpression.match
            (fileName, 0, QRegularExpression::PartialPreferCompleteMatch);

    if (seasonAndEpisodeMatch.hasMatch())
    {
        QString seasonAndEpisodeText = seasonAndEpisodeMatch.captured();
        QString episodeNumberText = episodeNumberExpression.match(seasonAndEpisodeText, 0).captured();
        int episode = numberExpression.match(episodeNumberText, 0).captured().toInt() - 1;
        for (auto pos : positions)
        {
            // Duplicate found
            if (episode == pos)
            {
                return -1;
            }
        }
        return episode;
    }
    else
    {
        return -1;
    }
}

int DirectoryParser::getEpisodePositionOfSeasonSeparatorEpisode(QString fileName, std::vector<int> positions)
{
    QRegularExpressionMatch seasonSeparatorEpisodeMatch = seasonSeparatorEpisodeExpression.match
            (fileName, 0, QRegularExpression::PartialPreferCompleteMatch);

    if (seasonSeparatorEpisodeMatch.hasMatch())
    {
        QString seasonSeparatorEpisodeText = seasonSeparatorEpisodeMatch.captured();
        QString episodeNumberText = episodeSeparatorNumberExpression.match(seasonSeparatorEpisodeText, 0).captured();
        int episode =  numberExpression.match(episodeNumberText, 0).captured().toInt() - 1;
        for (auto pos : positions)
        {
            // Duplicate found
            if (episode == pos)
            {
                return -1;
            }
        }
        return episode;
    }
    else
    {
        return -1;
    }
}

int DirectoryParser::getEpisodePositionOfDigitOnly(QString fileName, int amountFiles, std::vector<int> positions)
{
    QRegularExpressionMatch digitOnlyMatch = digitOnlySeasonAndEpisodeExpression.match
            (fileName, 0, QRegularExpression::PartialPreferCompleteMatch);

    if (digitOnlyMatch.hasMatch())
    {
        QString digitOnlyText = digitOnlyMatch.captured();
        int episodeLenght = getEpisodeLengthOfDigitOnly(amountFiles);
        int episode =  digitOnlyText.right(episodeLenght).toInt() - 1;
        for (auto pos : positions)
        {
            // Duplicate found
            if (episode == pos)
            {
                return -1;
            }
        }
        return episode;
    }
    else
    {
        return -1;
    }
}

int DirectoryParser::getEpisodeLengthOfDigitOnly(int amountFiles)
{
    for (int i = 1; true; i++)
    {
        if ((amountFiles - pow(10, i)) <= 0)
            return i + 1;
    }
}

std::vector<int> DirectoryParser::getEpisodePositions(QStringList episodeList)
{
    std::vector<int> episodePosition;
    std::unordered_map<int, int> foundSeasonToNumberOccurency;

    for (int i = 0; i < episodeList.size(); i++)
    {
        NameSchemeType type = getNameSchemeType(episodeList.at(i));
        // Season
        int foundSeason = getSeason(episodeList.at(i), episodeList.size(), type);
        if (foundSeasonToNumberOccurency.find(foundSeason) == foundSeasonToNumberOccurency.end())
        {
            foundSeasonToNumberOccurency.emplace(foundSeason, 1);
        }
        else
        {
            foundSeasonToNumberOccurency.at(foundSeason)++;
        }

        // Episode positions
        int foundPosition;
        switch (type)
        {
        case NameSchemeType::seasonAndEpisode:
            foundPosition = getEpisodePositionOfSeasonAndEpisode(episodeList.at(i), episodePosition);
            break;
        case NameSchemeType::seasonSeparatorEpisode:
            foundPosition = getEpisodePositionOfSeasonSeparatorEpisode(episodeList.at(i), episodePosition);
            break;
        case NameSchemeType::digitOnly:
            foundPosition = getEpisodePositionOfDigitOnly(episodeList.at(i), episodeList.size(), episodePosition);
            break;
        case NameSchemeType::none:
        default:
            foundPosition = -1;
            break;
        }
        episodePosition.push_back(foundPosition);
    }

    // Set found season to the one that occured the most
    int mostOccurencies = 0;
    for (auto iter : foundSeasonToNumberOccurency)
    {
        if (iter.second > mostOccurencies)
        {
            mostOccurencies = iter.second;
            foundSeason = iter.first;
        }
    }

    std::vector<int> sortedEpisodePositions = episodePosition;
    std::vector<int> emptyPositions;
    std::sort(sortedEpisodePositions.begin(), sortedEpisodePositions.end());

    for (int i = 1; i < int(sortedEpisodePositions.size()); i++)
    {
        auto emptySpaceSize = sortedEpisodePositions.at(i) - sortedEpisodePositions.at(i - 1);
        // Double entries, overwrite the first occurence
        if (emptySpaceSize == 0 && sortedEpisodePositions.at(i) != -1)
        {
            emptyPositions.push_back(sortedEpisodePositions.at(i - 1));
        }
        // Collect empty positions
        else
        {
            for (int j = 1; j < emptySpaceSize; j++)
            {
                emptyPositions.push_back(sortedEpisodePositions.at(i - 1) + j);
            }
        }
    }

    // Not found position. Fill the empty space in episodePosition with them.
    if (!sortedEpisodePositions.empty() && sortedEpisodePositions.at(0) == -1)
    {
        for (auto iter : episodePosition)
        {
            if (iter == -1 && !emptyPositions.empty())
            {
                iter = emptyPositions.front();
                emptyPositions.erase(emptyPositions.begin());
            }
        }
    }

    return episodePosition;
}

int DirectoryParser::getDirectoryPositionInList(QStringList directoryList, QString directoryToFind)
{
    for (int i = 0; i < directoryList.size(); i++)
    {
        if (directoryList.at(i) == directoryToFind)
            return i;
    }
    return -1; // Not found
}

void DirectoryParser::setPathStructure(int depth)
{
    std::vector<QStringList> pathStructure;
    if (directorySet)
    {
        QStringList currentDirectoryPositionList;
        QDir workingDirectory = directory;
        workingDirectory.setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);

        QDir parentDir = workingDirectory;
        parentDir.cdUp();

        if (workingDirectory.isRoot())
        {
            QStringList rootDriveList;
            QFileInfoList rootDrives = QDir::drives();
            for (int i = 0; i < rootDrives.size(); i++)
            {
                rootDriveList << rootDrives.at(i).absolutePath();
            }
            rootDriveList = naturalSort(rootDriveList);
            currentDirectoryPositionList << QString::number(getDirectoryPositionInList(rootDriveList, workingDirectory.absolutePath()));
            pathStructure.push_back(workingDirectory.entryList());
            pathStructure.push_back(rootDriveList);
            pathStructure.push_back(currentDirectoryPositionList);
            containsRoot = true;
        }
        else
        {
            // Last directory content where nothing is selected
            pathStructure.push_back(naturalSort(workingDirectory.entryList()));

            for (int i = 0; i < depth; i++)
            {
                QStringList directoryListToSearch;
                QString directoryToFind;

                directoryToFind = workingDirectory.dirName();
                directoryListToSearch = naturalSort(parentDir.entryList());
                int newDirectoryPosition = getDirectoryPositionInList(directoryListToSearch, directoryToFind);

                if (newDirectoryPosition == -1) // Workaround for not seeing Volumes on network drives on macOS
                {
                    directoryListToSearch << workingDirectory.dirName();
                    directoryListToSearch = naturalSort(directoryListToSearch);
                    newDirectoryPosition = getDirectoryPositionInList(directoryListToSearch, directoryToFind);
                }

                currentDirectoryPositionList <<  QString::number(newDirectoryPosition);
                pathStructure.push_back(directoryListToSearch);

                if (parentDir.isRoot() && (depth != i + 1))
                {
                    QStringList rootDriveList;
                    QFileInfoList rootDrives = QDir::drives();
                    for (int i = 0; i < rootDrives.size(); i++)
                    {
                        rootDriveList << rootDrives.at(i).absolutePath();
                    }
                    rootDriveList = naturalSort(rootDriveList);
                    currentDirectoryPositionList << QString::number(getDirectoryPositionInList(rootDriveList, parentDir.absolutePath()));
                    pathStructure.push_back(rootDriveList);
                    containsRoot = true;
                    break;
                }
                else
                {
                    workingDirectory.cdUp();
                    parentDir.cdUp();
                    containsRoot = false;
                }
            }
            pathStructure.push_back(currentDirectoryPositionList);
        }
    }
    this->pathStructure = pathStructure;
}

void DirectoryParser::setFileInformation()
{
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
        }
        else if (!fileInfo.isDir())
        {
            newSortedFiles << "";
            newSortedFilesWithoutSuffix << "";
            newSuffixes << "";
        }
    }
    setPathStructure(NUMBER_PATH_STRUCTURE_COMBOBOXES);

    sortedFiles = newSortedFiles;
    sortedFileWithoutSuffix = newSortedFilesWithoutSuffix;
    suffixes = newSuffixes;
}

DirectoryParser::DirectoryParser()
{
    directory.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    directory.setSorting(QDir::NoSort);
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
    QDir newDirectory(path);
    directorySet = newDirectory.exists();
    foundSeason = 0;
    if (directorySet)
    {
        directory = newDirectory;
        setFileInformation();
    }
    directoryPathInput = path;
    return directorySet;
}

std::vector<QStringList> DirectoryParser::getPathStructure()
{
    return pathStructure;
}

QString DirectoryParser::getDirectoryViaStructure(int level, int selection)
{
    if (level >= int(pathStructure.size() - 1))
        return "";

    QDir newDirectory = directory;
    QString directoryName = pathStructure.at(level).at(selection);

    for (int i = 0; i < level; i++)
    {
        newDirectory.cdUp();
    }
    newDirectory.cd(directoryName);
    return newDirectory.absolutePath();
}

bool DirectoryParser::getStructureContainsRoot()
{
    return containsRoot;
}

QString DirectoryParser::getDirectoryPathInput()
{
    return directoryPathInput;
}

QDir DirectoryParser::getDirectory()
{
    return directory;
}

int DirectoryParser::getFoundSeason()
{
    return foundSeason;
}

QStringList DirectoryParser::getFilesWithoutSuffix()
{
    return sortedFileWithoutSuffix;
}

QStringList DirectoryParser::getFilesSuffix()
{
    return suffixes;
}

Positions DirectoryParser::getFilePositions()
{
    return positionsValidity;
}
