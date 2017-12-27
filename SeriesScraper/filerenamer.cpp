#include "filerenamer.h"
#include <QDebug>

#define MAX_UNDO_OPERATIONS 15

FileRenamer::FileRenamer()
{
}

void FileRenamer::setEpisodeNames(EpisodeNames& episodeNames)
{
    oldFileNameList.clear();
    newFileNameList.clear();

    for (auto& episodeName: episodeNames)
    {
        if (!episodeName.newAndOldAreEqual() &&
                !episodeName.atLeastOneNameEmpty())
        {
            oldFileNameList.push_back(episodeName.getOldNameWithSuffix());
            newFileNameList.push_back(episodeName.getNewNameWithSuffix());
        }
    }
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
    if (index >= oldFileNameList.size())
    {
        const auto error = QString("FileRenamer::getOldFileName: ")
                + QString("Trying to access invalid oldFileName at ")
                + QString::number(index);
        throw std::runtime_error(error.toStdString().c_str());
    }
    return oldFileNameList.at(index);
}

QString FileRenamer::getNewFileName(int index)
{
    if (index >= newFileNameList.size())
    {
        const auto error = QString("FileRenamer::getOldFileName: ")
                + QString("Trying to access invalid newFileName at ")
                + QString::number(index);
        throw std::runtime_error(error.toStdString().c_str());
    }
    return newFileNameList.at(index);
}

bool FileRenamer::renameFile(int index)
{
    QString oldFileName = oldFileNameList.at(index);
    QString newFileName = newFileNameList.at(index);
    return workingDirectory.rename(oldFileName, newFileName);
}

void FileRenamer::addToUndoQueue()
{
    workingDirectoryStack.push_back(workingDirectory);
    oldFileNameListStack.push_back(oldFileNameList);
    newFileNameListStack.push_back(newFileNameList);
}

bool FileRenamer::isRenamePossible()
{
    return (!oldFileNameList.isEmpty()
            && !newFileNameList.isEmpty()
            && workingDirectory.exists());
}

bool FileRenamer::isUndoPossible()
{
    return (workingDirectoryStack.size() > 0);
}

bool FileRenamer::isSpaceOnUndoQueue()
{
    return (workingDirectoryStack.size() < MAX_UNDO_OPERATIONS);
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
    }
    else
    {
        return false;
    }
}
