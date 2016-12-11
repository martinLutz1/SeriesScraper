#include "filetypehandler.h"
#include <QCoreApplication>
#include <QDir>

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
        saveFileTypeFile();
    }
    return loadingSuccessful;
}

bool FileTypeHandler::saveFileTypeFile()
{
    return saveFile(fileTypeFile);
}

QStringList FileTypeHandler::getFileTypes()
{
    return loadedFile;
}

void FileTypeHandler::addFileType(QString newFileType)
{
    loadedFile << newFileType;
    saveFileTypeFile();
}

void FileTypeHandler::removeFileType(int index)
{
    loadedFile.removeAt(index);
    saveFileTypeFile();
}
