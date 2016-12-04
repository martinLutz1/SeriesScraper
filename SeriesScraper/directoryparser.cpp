#include "directoryparser.h"
#include <QDebug>
#include <QCollator>
#include <QCoreApplication>

QStringList DirectoryParser::sortFiles(QStringList files)
{
    QStringList sortedFiles;
    std::vector<int> position = getEpisodePositions(files);

    if (int(position.size()) != files.size())  // Name scheme not found, let QT sort
        return files;

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

    if (int(position.size()) < files.size())  // Name scheme not found, let QT sort
        return files;

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
    QRegularExpressionMatch match;
    QRegularExpressionMatch matchEpisodeNumber;

    for (int i = 0; i < episodeList.size(); i++)
    {
        match = episodeNumberExpression.match
                (episodeList.at(i).toLower(), 0, QRegularExpression::PartialPreferCompleteMatch);

        if (match.hasMatch())
        {

            QString capturedEpisodeString = match.captured();
            matchEpisodeNumber = numberFromEpisodeNumberExpression.match
                    (capturedEpisodeString, 0, QRegularExpression::PartialPreferCompleteMatch);
            int actualPosition = matchEpisodeNumber.captured().toInt() - 1;
            episodePosition.push_back(actualPosition);
        }
    }
    return episodePosition;
}

void DirectoryParser::setNameFilterToAll()
{
    filter.clear();
    filter << "*.avi" << "*.mkv" << "*.mp4" << "*.m4v" << "*.mpg" << "*.flv" << ".*webm" << "*.ogv" << "*.mov" << "*.wmv";
}

DirectoryParser::DirectoryParser()
{
    directory.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    directory.setSorting(QDir::NoSort);
    directory.setPath("");
    setNameFilterToAll();

    episodeNumberExpression.setPattern("(s)[0-9]+(.*)(e)[0-9]+");
    numberFromEpisodeNumberExpression.setPattern("[0-9]*$");
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

QStringList DirectoryParser::getFilesWithoutExtension()
{
    QFileInfo fileInfo;
    QStringList fileList = getFiles();
    QStringList fileWithoutExtension;

    for (int i = 0; i < fileList.size(); i++)
    {
        fileInfo.setFile(fileList.at(i));
        fileWithoutExtension << fileInfo.completeBaseName();
    }
    return fileWithoutExtension;
}

QStringList DirectoryParser::getFiles(QString extension)
{
    filter = QStringList(extension);
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
