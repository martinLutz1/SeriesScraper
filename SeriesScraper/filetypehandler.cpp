#include "filetypehandler.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

FileTypeHandler::FileTypeHandler()
{
    QDir applicationDirectory = QCoreApplication::applicationDirPath();
    fileTypeFile = new QFile;
    fileTypeFile->setFileName(applicationDirectory.absoluteFilePath("filetype.list"));
}

FileTypeHandler::~FileTypeHandler()
{
    delete fileTypeFile;
}

bool FileTypeHandler::loadFileTypeFile()
{
    bool loadingSuccessful = loadFile(fileTypeFile);
    if (!loadingSuccessful)
    {
        QStringList defaultFileTypes;
        defaultFileTypes << "avi" << "mkv" << "mp4" << "m4v" << "mpg" << "flv" << "webm" << "ogv" << "mov" << "wmv";
        loadedFile = defaultFileTypes;
    }
    sort();
    saveFileTypeFile();
    return loadingSuccessful;
}

QStringList FileTypeHandler::getFileTypes()
{
    return loadedFile;
}

int FileTypeHandler::addFileType(QString newFileType)
{
    loadedFile << newFileType;
    loadedFile.removeDuplicates();
    sort();
    saveFileTypeFile();

    int positionInList = loadedFile.indexOf(newFileType);
    return positionInList;
}

void FileTypeHandler::removeFileType(int index)
{
    loadedFile.removeAt(index);
    saveFileTypeFile();
}

int FileTypeHandler::setFileType(int index, QString newFileType)
{
    if (index >= 0 && index < loadedFile.size())
    {
        loadedFile[index] = newFileType;
        loadedFile.removeDuplicates();
        sort();
        saveFileTypeFile();
        int positionInList = loadedFile.indexOf(newFileType);
        return positionInList;
    }
    else
        return -1;
}

bool FileTypeHandler::saveFileTypeFile()
{
    return saveFile(fileTypeFile);
}

void FileTypeHandler::sort()
{
    std::sort(loadedFile.begin(), loadedFile.end(),
              [](const QString& s1, const QString& s2) {
        return s1.toLower() < s2.toLower(); });
}
