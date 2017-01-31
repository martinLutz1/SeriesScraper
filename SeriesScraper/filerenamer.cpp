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
            bool emptyNewName = newFileName.isEmpty();
            bool hasAlreadyNewName = (newFileName == fileToRename);
            // Do not rename empty file names and files with the same name
            if (emptyFileName || hasAlreadyNewName || emptyNewName)
                continue;

            renamingSucceded = workingDirectory.rename(fileToRename, newFileName);
            if (!renamingSucceded)
                break;
        }
    }
    undoPossible = renamingSucceded;
    return renamingSucceded;
}

bool FileRenamer::isUndoPossible()
{
    return undoPossible;
}

bool FileRenamer::deleteLastUndo()
{
    undoPossible = false;
}

bool FileRenamer::undo()
{
    if (undoPossible)
    {
        // Swap old and new file names
        QStringList temp = oldFileNameList;
        oldFileNameList = newFileNameList;
        newFileNameList = temp;
        return rename();
    } else
    {
        return false;
    }
}
