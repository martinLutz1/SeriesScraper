#include "filerenamer.h"
#include <QDebug>

FileRenamer::FileRenamer()
{

}

void FileRenamer::setOldFileNames(QStringList oldFileNames)
{
    this->oldFileNameList = oldFileNames;
}

void FileRenamer::setNewFileNames(QStringList newFileNames)
{
    this->newFileNameList = newFileNames;
}

void FileRenamer::setDirectory(QDir directory)
{
    workingDirectory = directory;
}

void FileRenamer::setSuffixes(QStringList suffixList)
{
    suffixes = suffixList;
}

bool FileRenamer::rename()
{
    if (suffixes.size() != oldFileNameList.size()) {
        return false;
    }
    if (workingDirectory.exists())
    {
        for (int i = 0; i < oldFileNameList.length(); i++)
        {
            if (oldFileNameList.at(i).isEmpty()) // Do not rename empty files
                continue;

            //try catch!
            QString newFileName = newFileNameList.at(i) + "." + suffixes.at(i);
            workingDirectory.rename(oldFileNameList.at(i), newFileName);
        }
        return true;
    } else
    {
        return false;
    }
}
