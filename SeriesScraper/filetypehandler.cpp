#include "filetypehandler.h"
#include <QCoreApplication>
#include <QDir>

FileTypeHandler::FileTypeHandler()
{
    QDir applicationDirectory = QCoreApplication::applicationDirPath();
    fileTypeFile = new QFile;
    fileTypeFile->setFileName(applicationDirectory.absoluteFilePath("fileType.list"));
}

FileTypeHandler::~FileTypeHandler()
{
    delete fileTypeFile;
}

bool FileTypeHandler::loadFileTypeFile()
{
    return loadFile(fileTypeFile);
}

bool FileTypeHandler::saveFileTypeFile()
{
    return saveFile(fileTypeFile);
}

QStringList FileTypeHandler::getFileTypes()
{
    return loadedFile;
}
