#include "nameschemehandler.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

NameSchemeHandler::NameSchemeHandler() :
    selectedNameSchemeIndex(0)
{
    QDir applicationDirectory = QCoreApplication::applicationDirPath();
    nameSchemeFile = new QFile;
    nameSchemeFile->setFileName(applicationDirectory.absoluteFilePath("namescheme.list"));
}

NameSchemeHandler::~NameSchemeHandler()
{
    delete nameSchemeFile;
}

bool NameSchemeHandler::readNameSchemeFile()
{
    return loadFile(nameSchemeFile);
}

bool NameSchemeHandler::saveNameSchemeFile()
{
    return saveFile(nameSchemeFile);
}

bool NameSchemeHandler::addNameScheme(QString nameScheme)
{
    loadedFile << nameScheme;
    return saveNameSchemeFile();
}

bool NameSchemeHandler::removeNameScheme(int index)
{
    int size = loadedFile.size();
    if (!(index >= 0 && index < size))
        return false;

    loadedFile.removeAt(index);
    if (index == selectedNameSchemeIndex)
        selectedNameSchemeIndex = 0;
    return saveNameSchemeFile();
}

bool NameSchemeHandler::replaceNameScheme(int index, QString newNameScheme)
{
    int size = loadedFile.size();
    bool validIndex = (index >= 0 && index < size);
    if (validIndex)
    {
        loadedFile[index] = newNameScheme;
        return saveNameSchemeFile();
    }
    return validIndex;
}

bool NameSchemeHandler::setNameScheme(int index)
{
    int size = loadedFile.size();
    bool validIndex = (index >= 0 && index < size);
    if (validIndex)
    {
        selectedNameSchemeIndex = index;
        nameSchemeParser.setNameScheme(loadedFile.at(index));
    }
    return validIndex;
}

QString NameSchemeHandler::getNameScheme()
{
    return loadedFile.at(selectedNameSchemeIndex);
}

QString NameSchemeHandler::getFileName(QString series, QString airDate, int season, int episode, QString episodeName)
{
    QString fileName = nameSchemeParser.getFileName(series, airDate, QString::number(season),
                                                    QString::number(episode + 1), episodeName);
    return fileName;
}

QStringList NameSchemeHandler::getFileNameList(QString series, QString airDate, int season, int amountEpisodes, QStringList episodeName)
{
    QStringList fileNameList;
    if (amountEpisodes == episodeName.size())
    {
        for (int i = 0; i < amountEpisodes; i++)
        {
            QString episode = "";
            if (episodeName.size() > i)
                episode = episodeName.at(i);
            QString fileName = getFileName(series, airDate, season, i, episode);
            fileNameList << fileName;
        }
    }
    return fileNameList;
}

QString NameSchemeHandler::getNameSchemeRepresentation()
{
    return nameSchemeParser.getNameSchemeRepresentation();
}

int NameSchemeHandler::getAmountNameSchemes()
{
    return loadedFile.size();
}

int NameSchemeHandler::getSelectedNameSchemeIndex()
{
    return selectedNameSchemeIndex;
}
