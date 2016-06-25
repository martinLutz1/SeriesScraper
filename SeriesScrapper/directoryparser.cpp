#include "directoryparser.h"
#include <QDebug>

void DirectoryParser::setNameFilterToAll()
{
    directory.setNameFilters(QStringList() << "*.avi" << "*.mkv" << "*.mp4" << "*.m4v" << "*.mpg"
                             << "*.flv" << ".*webm" << "*.ogv" << "*.mov" << "*.wmv");
    episodeNumberExpression.setPattern("s[0-9]+e[0-9]+");
}

DirectoryParser::DirectoryParser()
{
    directory.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    directory.setSorting(QDir::Name);
    setNameFilterToAll();
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
    loadedFiles.clear();
    QFileInfo fileInfo;
    QFileInfoList list = directory.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        fileInfo = list.at(i);
        if (fileInfo.isFile())
        loadedFiles << fileInfo.fileName();
    }

   // QRegularExpressionMatch match = episodeNumberExpression.match(fileNames.at(8), 0, QRegularExpression::PartialPreferCompleteMatch);
   // bool hasMatch = match.hasMatch(); // true
   // qDebug() << "Match:" << match.hasMatch() << "" << "Partial:" << match.hasPartialMatch() << "" << match.captured();
    return loadedFiles;
}

QStringList DirectoryParser::getFiles(QString extension)
{
    directory.setNameFilters(QStringList() << extension);
    QStringList list = getFiles();
    setNameFilterToAll();
    return list;
}
