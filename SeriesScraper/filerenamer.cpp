#include "filerenamer.h"

FileRenamer::FileRenamer()
{

}

void FileRenamer::setFiles(QStringList sortedFilesWithSpaces)
{
    fileList = sortedFilesWithSpaces;
}

void FileRenamer::setEpisodeNames(QStringList episodes)
{
    episodeList = episodes;
}

void FileRenamer::setDirectory(QDir directory)
{
    workingDirectory = directory;
}

bool FileRenamer::rename()
{
    if (workingDirectory.exists())
    {
        for (int i = 0; i < episodeList.length(); i++)
        {
            if (fileList.at(i).isEmpty()) // Do not rename empty files
                continue;

            //try catch!
             workingDirectory.rename(fileList.at(i), episodeList.at(i));
        }
        return true;
    } else
    {
        return false;
    }
}
