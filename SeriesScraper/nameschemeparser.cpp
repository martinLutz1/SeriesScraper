#include "nameschemeparser.h"
#include <QDebug>

NameSchemeParser::NameSchemeParser()
{
    seriesNameExpression.setPattern("\\$series");
    seasonNumberExpression.setPattern("\\$season");
    seasonNumberAdvancedExpression.setPattern("\\$season\\((\\d+)\\)");
    episodeNumberExpression.setPattern("\\$episode");
    episodeNumberAdvancedExpression.setPattern("\\$episode\\((\\d+)\\)");
    episodeNameExpression.setPattern("\\$episodeName");
    numberExpression.setPattern("\\d+");
    nextVariableExpression.setPattern("%");
    replaceExpression.setPattern("\\$replace\\((.+)=(.+)\\)");
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
    QStringList replaceFrom, replaceTo;

    for (int i = 0; i < parsedNameSchemeList.size(); i++)
    {
        QString currentString = parsedNameSchemeList.at(i);
        int variableType = getVariableType(currentString);

        if (variableType == episodeNumber)
        {
            numberExpression.indexIn(currentString, 0);
            // Simple format
            if (numberExpression.cap(0).isEmpty())
                fileName += variables[variableType];
            // Advanced format (leading zeros)
            else
            {
                int numberLenght = numberExpression.cap(0).toInt();
                QString number = QString("%1").arg(episode.toInt(), numberLenght, 10, QChar('0'));
                fileName += number;
            }
        } else if (variableType == seasonNumber)
        {
            numberExpression.indexIn(currentString, 0);
            // Simple format
            if (numberExpression.cap(0).isEmpty())
                fileName += variables[variableType];
            // Advanced format (leading zeros)
            else
            {
                int numberLenght = numberExpression.cap(0).toInt();
                QString number = QString("%1").arg(season.toInt(), numberLenght, 10, QChar('0'));
                fileName += number;
            }
        } else if (variableType == replace) // Doesnt operate on RegExp, change me if you change replace operation
        {
            // Remove everything thats not inside the brackets
            QString replaceTerm = currentString.remove(0, 9);
            replaceTerm = replaceTerm.left(replaceTerm.size() - 1);

            QStringList replaceTermSplitted = replaceTerm.split("=");
            if (replaceTermSplitted.size() != 2) // Error message
                continue;
            else
            { // Two terms found
                replaceFrom << replaceTermSplitted.at(0);
                replaceTo << replaceTermSplitted.at(1);
            }

        }
        else if (variableType != none)
            fileName += variables[variableType];
        else
            fileName += currentString;
    }

    int replaceCount = replaceFrom.size();
    for (int i = 0; i < replaceCount; i++)
    {
        QString from = replaceFrom.at(i);
        QString to = replaceTo.at(i);
        fileName.replace(from, to);
    }
    return fileName;
}

QString NameSchemeParser::getNameSchemeRepresentation()
{
    QStringList variables = {"<series>", "<s", "<ep", "<episode name>", "$replace("};
    QString nameSchemeRepresentation;
    QStringList replaceOperationList;

    for (int i = 0; i < parsedNameSchemeList.size(); i++)
    {
        QString currentString = parsedNameSchemeList.at(i);
        int variableType = getVariableType(currentString);
        if (variableType == episodeNumber)
        {
            numberExpression.indexIn(currentString, 0);
            nameSchemeRepresentation += variables.at(variableType);

            // Simple format
            if (numberExpression.cap(0).isEmpty())
                nameSchemeRepresentation.append(">");
            // Advanced format (leading zeros)
            else {
                int numberLenght = numberExpression.cap(0).toInt();
                nameSchemeRepresentation += "(" + QString::number(numberLenght) + ")>";
            }
        } else if (variableType == seasonNumber) {
            numberExpression.indexIn(currentString, 0);
            nameSchemeRepresentation += variables.at(variableType);

            // Simple format
            if (numberExpression.cap(0).isEmpty())
                nameSchemeRepresentation.append(">");
            // Advanced format (leading zeros)
            else {
                int numberLenght = numberExpression.cap(0).toInt();
                nameSchemeRepresentation += "(" + QString::number(numberLenght) + ")>";
            }
        }
        else if (variableType == replace) {
            QString replaceOperationWithoutDollar = currentString.remove(0, 1);
            replaceOperationList << replaceOperationWithoutDollar;
        }
        else if (variableType != none) {
            nameSchemeRepresentation += variables.at(variableType);
        }
        else {
            nameSchemeRepresentation += currentString;
        }
    }

    int replaceCount = replaceOperationList.size();
    // Add counted replace operations to representation
    if (replaceCount == 1) { // Show replace string if only one replace operation
        nameSchemeRepresentation += "$" + replaceOperationList.at(0) + "$";
    }
    else if (replaceCount > 1) {
        nameSchemeRepresentation += variables.at(replace) + QString::number(replaceCount) + ")$";
    }

    return nameSchemeRepresentation;
}

int NameSchemeParser::getVariableType(QString toCheck)
{
    if (seriesNameExpression.exactMatch(toCheck)) {
        return seriesName;
    }
    else if (seasonNumberExpression.exactMatch(toCheck)
             || seasonNumberAdvancedExpression.exactMatch(toCheck)) {
        return seasonNumber;
    }
    else if (episodeNumberExpression.exactMatch(toCheck)
             || episodeNumberAdvancedExpression.exactMatch(toCheck)) {
        return episodeNumber;
    }
    else if (episodeNameExpression.exactMatch(toCheck)) {
        return episodeName;
    }
    else if (replaceExpression.exactMatch(toCheck)) {
        return replace;
    }
    else {
        return none;
    }
}
