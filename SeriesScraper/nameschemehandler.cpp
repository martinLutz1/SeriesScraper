#include "nameschemehandler.h"

#include <QCoreApplication>
#include <QDebug>

NameSchemeHandler::NameSchemeHandler() :
    selectedNameSchemeIndex(0),
    successReading(false)
{
    applicationDirectory = QCoreApplication::applicationDirPath();
    nameSchemeFile.setFileName(applicationDirectory.absoluteFilePath("namescheme.list"));
}

bool NameSchemeHandler::readNameSchemeFile()
{
    successReading = nameSchemeFile.open(QIODevice::ReadOnly);
    if (!successReading)
        return false;

    QTextStream in(&nameSchemeFile);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (!line.isEmpty())
            nameSchemeList << line;
    }
    nameSchemeFile.close();
    return true;
}

bool NameSchemeHandler::saveNameSchemeFile()
{
    successReading = nameSchemeFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    if (!successReading) // Reading failed
        return false;

    int size = nameSchemeList.size();
    QTextStream inOut(&nameSchemeFile);

    for (int i = 0; i < size; i++)
    {
        if (i - size == 0) // Last item
            inOut << nameSchemeList.at(i);
        else
            inOut << nameSchemeList.at(i) << "\n";
    }
    nameSchemeFile.close();
    return successReading;
}

bool NameSchemeHandler::addNameScheme(QString nameScheme)
{
    nameSchemeList << nameScheme;
    return saveNameSchemeFile();
}

bool NameSchemeHandler::removeNameScheme(int index)
{
    int size = nameSchemeList.size();
    if (!(index >= 0 && index < size))
        return false;

    nameSchemeList.removeAt(index);
    if (index == selectedNameSchemeIndex)
        selectedNameSchemeIndex = 0;
    return saveNameSchemeFile();
}

bool NameSchemeHandler::replaceNameScheme(int index, QString newNameScheme)
{
    int size = nameSchemeList.size();
    if (!(index >= 0 && index < size))
        return false;

    nameSchemeList[index] = newNameScheme;
    saveNameSchemeFile();
    return true;
}

bool NameSchemeHandler::setNameScheme(int index)
{
    int size = nameSchemeList.size();
    if (!(index >= 0 && index < size))
        return false;

    selectedNameSchemeIndex = index;
    nameSchemeParser.parseNameScheme(nameSchemeList.at(index));
    return true;
}

QString NameSchemeHandler::getNameScheme()
{
    return nameSchemeList.at(selectedNameSchemeIndex);
}

QString NameSchemeHandler::getFileName(QString series, int season, int episode, QString episodeName)
{
    QString fileName = nameSchemeParser.getFileName(series, QString::number(season),
                                                    QString::number(episode + 1), episodeName);
    return fileName;
}

QStringList NameSchemeHandler::getFileNameList(QString series, int season, int amountEpisodes, QStringList episodeName)
{
    QStringList fileNameList;
    for (int i = 0; i < amountEpisodes; i++)
    {
        QString fileName = getFileName(series, season, i, episodeName.at(i));
        fileNameList << fileName;
    }
    return fileNameList;
}

QString NameSchemeHandler::getNameSchemeRepresentation()
{
    return(nameSchemeParser.getNameSchemeRepresentation());
}

int NameSchemeHandler::getAmountNameSchemes()
{
    return nameSchemeList.size();
}

int NameSchemeHandler::getSelectedNameSchemeIndex()
{
    return selectedNameSchemeIndex;
}
