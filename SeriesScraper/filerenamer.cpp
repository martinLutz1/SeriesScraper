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

bool FileRenamer::rename()
{
    int amountOldFiles = oldFileNameList.size();
    int amountNewNames = newFileNameList.size();
    bool renamingSucceded = false;

    if (workingDirectory.exists())
    {
        renamingSucceded = true;
        int amountToRename = std::min(amountNewNames, amountOldFiles);
        for (int i = 0; i < amountToRename; i++)
        {
            QString fileToRename = oldFileNameList.at(i);
            QString newFileName = newFileNameList.at(i);

            bool emptyFileName = fileToRename.isEmpty();
            bool hasAlreadyNewName = (newFileName == fileToRename);
            // Do not rename empty file names and files with the same name
            if (emptyFileName || hasAlreadyNewName)
                continue;

            bool renameSuccess = workingDirectory.rename(fileToRename, newFileName);
            if (!renameSuccess)
                renamingSucceded = renameSuccess;
        }

    }
    return renamingSucceded;
}
