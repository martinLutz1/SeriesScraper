#include "directoryparser.h"
#include <QDebug>

DirectoryParser::DirectoryParser()
{
    directory.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    directory.setSorting(QDir::Name);
    directory.setNameFilters(QStringList() << "*.avi" << "*.mkv" << "*.mp4" << "*.m4v" << "*.mpg"
                             << "*.flv" << ".*webm" << "*.ogv" << "*.mov" << "*.wmv");
}

bool DirectoryParser::setDirectory(QDir directory)
{
    if (directory.exists()) {
        this->directory = directory;
        return true;
    }
    else {
        return false;
    }
}

QStringList DirectoryParser::getFiles()
{
    QStringList fileNames;
    QFileInfo fileInfo;
    QFileInfoList list = directory.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        fileInfo = list.at(i);
        if (fileInfo.isFile())
        fileNames << fileInfo.fileName();
    }
    return fileNames;
}
