#include "nameschemehandler.h"

#include <QCoreApplication>
#include <QDebug>

NameSchemeHandler::NameSchemeHandler() : successReading(false)
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

bool NameSchemeHandler::addNameScheme(QString nameScheme)
{
    successReading = nameSchemeFile.open(QIODevice::ReadWrite | QIODevice::Text);
    if (!successReading)
        return false;

    nameSchemeList << nameScheme;
    QTextStream inOut(&nameSchemeFile);
    inOut << "\n" << nameScheme;

    nameSchemeFile.close();
    return true;
}

bool NameSchemeHandler::removeNameScheme(int index)
{
    int size = nameSchemeList.size();
    if (!(index >= 0 && index < size))
        return false;

    successReading = nameSchemeFile.open(QIODevice::WriteOnly | QIODevice::Text);
    if (!successReading) // Reading failed
        return false;

    nameSchemeList.removeAt(index);
    size = nameSchemeList.size();
    QTextStream inOut(&nameSchemeFile);
    inOut.flush();

    for (int i = 0; i < size; i++)
    {
        if (i - size == 0) // Last item
            inOut << nameSchemeList.at(i);
        else
            inOut << nameSchemeList.at(i) << "\n";
    }
    nameSchemeFile.close();
    return true;
}

QString NameSchemeHandler::getNameScheme(int index)
{
    int size = nameSchemeList.size();

    if (index >= 0 && index < size)
        return nameSchemeList.at(index);
    else
        return QString("");
}

bool NameSchemeHandler::setNameScheme(int index)
{
    int size = nameSchemeList.size();
    if (!(index >= 0 && index < size))
        return false;

    nameSchemeParser.parseNameScheme(nameSchemeList.at(index));
    return true;
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
