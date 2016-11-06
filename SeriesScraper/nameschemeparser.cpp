#include "nameschemeparser.h"
#include <QDebug>

NameSchemeParser::NameSchemeParser()
{
    seriesNameExpression.setPattern("series");
    seasonNumberExpression.setPattern("season");
    episodeNumberAdvancedExpression.setPattern("episode\\((\\d+)\\)");
    episodeNumberExpression.setPattern("episode");
    episodeNameExpression.setPattern("episodeName");
    numberExpression.setPattern("\\d+");
    nextVariableExpression.setPattern("%");

    parseNameScheme("%season% %series% - s%season%e%episode% - %episodeName% [NIC]");
    qDebug() << getFileName("Supernatural", "2", "9", "My way");
}

void NameSchemeParser::parseNameScheme(QString nameScheme)
{
    // Split scheme at %
    QStringList nameSchemeList = nameScheme.split(nextVariableExpression);
    // Remove empty subsets
    while(nameSchemeList.removeOne(""));

    parsedNameSchemeList = nameSchemeList;
}

QString NameSchemeParser::getFileName(QString series, QString season, QString episode, QString episodeName)
{
    QStringList variables = {series, season, episode, episodeName};
    QString fileName;

    for (int i = 0; i < parsedNameSchemeList.size(); i++) {
        QString currentString = parsedNameSchemeList.at(i);
        int variableType = getVariableType(currentString);

        if (variableType == episodeNumber) {
            numberExpression.indexIn(currentString, 0);
            // Simple format
            if (numberExpression.cap(0).isEmpty()) {
                fileName += variables[variableType];
            }
            // Advanced format (leading zeros)
            else {
                int numberLenght = numberExpression.cap(0).toInt();
                QString number = QString("%1").arg(episode.toInt(), numberLenght, 10, QChar('0'));
                fileName += number;
            }
        }
        else if (variableType != none) {
            fileName += variables[variableType];
        }
        else {
            fileName += currentString;
        }
    }
    return fileName;
}

int NameSchemeParser::getVariableType(QString toCheck)
{
    if (seriesNameExpression.exactMatch(toCheck)) {
        return seriesName;
    }
    else if (seasonNumberExpression.exactMatch(toCheck)) {
        return seasonNumber;
    }
    else if (episodeNumberExpression.exactMatch(toCheck)
             || episodeNumberAdvancedExpression.exactMatch(toCheck)) {
        return episodeNumber;
    }
    else if (episodeNameExpression.exactMatch(toCheck)) {
        return episodeName;
    }
    else {
        return none;
    }
}
