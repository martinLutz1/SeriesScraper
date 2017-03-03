#include "filerenamer.h"
#include <QDebug>

#define MAX_UNDO_OPERATIONS 15

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

int FileRenamer::getRenameAmount()
{
    return std::min(oldFileNameList.size(), newFileNameList.size());
}

QString FileRenamer::getOldFileName(int index)
{
    QString oldFileName = "";
    if (index < oldFileNameList.size())
        oldFileName = oldFileNameList.at(index);
    return oldFileName;
}

QString FileRenamer::getNewFileName(int index)
{
    QString newFileName = "";
    if (index < newFileNameList.size())
        newFileName = newFileNameList.at(index);
    return newFileName;
}

bool FileRenamer::rename(bool isUndo)
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
            qDebug() << fileToRename << newFileName;

            bool emptyFileName = fileToRename.isEmpty();
            bool emptyNewName = newFileName.isEmpty();
            bool hasAlreadyNewName = (newFileName == fileToRename);
            // Do not rename empty file names and files with the same name
            if (emptyFileName || hasAlreadyNewName || emptyNewName)
                continue;

            renamingSucceded = workingDirectory.rename(fileToRename, newFileName);
            if (!renamingSucceded)
                break;
            // Todo undo if it fails
        }
        if (renamingSucceded
                && workingDirectoryStack.size() < MAX_UNDO_OPERATIONS
                && !isUndo)
        {
            workingDirectoryStack.push_back(workingDirectory);
            oldFileNameListStack.push_back(oldFileNameList);
            newFileNameListStack.push_back(newFileNameList);
        }
    }
    return renamingSucceded;
}

bool FileRenamer::renameFile(int index)
{
    QString fileToRename = oldFileNameList.at(index);
    QString newFileName = newFileNameList.at(index);

    bool emptyFileName = fileToRename.isEmpty();
    bool emptyNewName = newFileName.isEmpty();
    bool hasAlreadyNewName = (newFileName == fileToRename);

    // Do not rename empty file names and files with the same name
    if (emptyFileName || hasAlreadyNewName || emptyNewName)
        return false;
    else
        return workingDirectory.rename(fileToRename, newFileName);
}

void FileRenamer::addToUndoQueue()
{
    workingDirectoryStack.push_back(workingDirectory);
    oldFileNameListStack.push_back(oldFileNameList);
    newFileNameListStack.push_back(newFileNameList);
}

bool FileRenamer::isRenamePossible()
{
    return (!oldFileNameList.isEmpty() && !newFileNameList.isEmpty() && workingDirectory.exists());
}

bool FileRenamer::isUndoPossible()
{
    return (workingDirectoryStack.size() > 0);
}

bool FileRenamer::prepareUndo()
{
    if (workingDirectoryStack.size() > 0)
    {
        workingDirectory = workingDirectoryStack.back();
        oldFileNameList = newFileNameListStack.back();
        newFileNameList = oldFileNameListStack.back();
        workingDirectoryStack.pop_back();
        oldFileNameListStack.pop_back();
        newFileNameListStack.pop_back();

        return true;
    } else
        return false;
}
