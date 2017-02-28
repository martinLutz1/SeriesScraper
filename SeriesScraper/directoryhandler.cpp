#include "directoryhandler.h"

DirectoryHandler::DirectoryHandler(QObject *parent) : QObject(parent)
{

}

void DirectoryHandler::setFileTypes(QStringList fileTypes)
{
    directoryParser.setFileTypes(fileTypes);
}

std::vector<QStringList> DirectoryHandler::getPathStructure()
{
    return directoryParser.getPathStructure();
}

QString DirectoryHandler::getDirectoryViaStructure(int level, int selection)
{
    return directoryParser.getDirectoryViaStructure(level, selection);
}

bool DirectoryHandler::getStructureContainsRoot()
{
    return directoryParser.getStructureContainsRoot();
}

QString DirectoryHandler::getDirectoryPathInput()
{
    return directoryParser.getDirectoryPathInput();
}

int DirectoryHandler::getFoundSeason()
{
    return directoryParser.getFoundSeason();
}

QStringList DirectoryHandler::getFiles()
{
    return directoryParser.getFiles();
}

QStringList DirectoryHandler::getFilesWithoutSuffix()
{
    return directoryParser.getFilesWithoutSuffix();
}

QStringList DirectoryHandler::getFilesSuffix()
{
    return directoryParser.getFilesSuffix();
}

void DirectoryHandler::initializeDirectory(QString path)
{
    bool initialized = directoryParser.initializeDirectory(path);
    emit directoryInitialized(initialized);
}
