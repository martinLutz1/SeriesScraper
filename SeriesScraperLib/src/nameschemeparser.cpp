#include "nameschemeparser.h"
#include <QDebug>

NameSchemeParser::NameSchemeParser()
{
    nameSchemeNameExpression.setPattern("^\\|.+?\\|");
    airDateExpression.setPattern("<airDate>");
    replaceExpression.setPattern("\\|(replace)\\(.+\\)\\|$");
    seriesNameExpression.setPattern("<series>");
    seasonNumberExpression.setPattern("<season>");
    seasonNumberAdvancedExpression.setPattern("<season\\((\\d+)\\)>");
    episodeNumberExpression.setPattern("<episode>");
    episodeNumberAdvancedExpression.setPattern("<episode\\((\\d+)\\)>");
    episodeNameExpression.setPattern("\\<episodeName>");
    numberExpression.setPattern("\\d+");
    generalVariableExpression.setPattern("<(.+?)>");
}

void NameSchemeParser::setNameScheme(QString nameScheme)
{
    QString preParsedNameScheme = preParseNameScheme(nameScheme);
    parsedNameSchemeList = parseNameScheme(preParsedNameScheme);
}

QString NameSchemeParser::getFileName(QString series, QString airDate, QString season, QString episode, QString episodeName)
{
    QStringList variables = {series, airDate, season, episode, episodeName};
    QString fileName;

    for (int i = 0; i < parsedNameSchemeList.size(); i++)
    {
        QString currentString = parsedNameSchemeList.at(i);
        auto variableType = getVariableType(currentString);

        switch (variableType)
        {
        case VariableType::episodeNumber:
        case VariableType::seasonNumber:
        {
            QRegularExpressionMatch numberMatch = numberExpression.match(currentString);
            QString foundNumber = numberMatch.captured();
            // Simple format
            if (foundNumber.isEmpty())
            {
                fileName += variables[(int)variableType];
            }
            // Advanced format (leading zeros)
            else
            {
                int numberLenght = foundNumber.toInt();
                QString number;

                if (variableType == VariableType::episodeNumber)
                {
                    number = QString("%1").arg(episode.toInt(), numberLenght, 10, QChar('0'));
                }
                else if (variableType == VariableType::seasonNumber)
                {
                    number = QString("%1").arg(season.toInt(), numberLenght, 10, QChar('0'));
                }

                fileName += number;
            }
            break;
        }
        case VariableType::seriesName:
        case VariableType::airDate:
        case VariableType::episodeName:
        {
            fileName += variables[(int)variableType];
            break;
        }
        case VariableType::none:
        {
            fileName += currentString;
            break;
        }
        default:
        {
            break;
        }
        }
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
    QString nameSchemeRepresentation;
    if (nameSchemeName.isEmpty())
    {
        for (int i = 0; i < parsedNameSchemeList.size(); i++)
            nameSchemeRepresentation += parsedNameSchemeList.at(i);

        int numberReplaceOperations = replaceFrom.size();
        if (numberReplaceOperations > 0)
            nameSchemeRepresentation += " |replace(" + QString::number(numberReplaceOperations) + ")|";
    }
    else
    {
        nameSchemeRepresentation = nameSchemeName;
    }
    return nameSchemeRepresentation;
}

QString NameSchemeParser::preParseNameScheme(QString nameScheme)
{
    replaceFrom.clear();
    replaceTo.clear();

    // Determine name
    QRegularExpressionMatch nameSchemeNameMatch = nameSchemeNameExpression.match(nameScheme);
    QString name = nameSchemeNameMatch.captured();
    nameSchemeName = name.remove("|");
    nameScheme.remove(nameSchemeNameExpression);

    // Parse replace operation
    QRegularExpressionMatch replaceMatch = replaceExpression.match(nameScheme);
    QString replace = replaceMatch.captured();

    if (replace.size() > 0)
    {
        replace.chop(2); // Last 2 chars
        replace.remove(0, 9); // First 9 chars

        QStringList replaceTerms = replace.split("|");
        for (int i = 0; i < replaceTerms.size(); i++)
        {
            QStringList replaceTermSplitted = replaceTerms.at(i).split("=");
            if (replaceTermSplitted.size() != 2) // Error message
                continue;
            else
            {
                replaceFrom << replaceTermSplitted.at(0);
                replaceTo << replaceTermSplitted.at(1);
            }
        }
        nameScheme.remove(replaceExpression);
    } else
    {
        replaceFrom.clear();
        replaceTo.clear();
    }
    int lastNameSchemeCharPosition = nameScheme.length() - 1;
    if (nameScheme.at(lastNameSchemeCharPosition) == ' ') // Remove last empty space, if existing
        nameScheme.chop(1);
    if (nameScheme.at(0) == ' ') // Remove first empty space, if existing
        nameScheme.remove(0,1);

    return nameScheme;
}

QStringList NameSchemeParser::parseNameScheme(QString nameScheme)
{
    QStringList parsedNameScheme;
    bool moreVariablesExist = false;
    do
    {
        QRegularExpressionMatch variableMatch = generalVariableExpression.match(nameScheme);
        moreVariablesExist = variableMatch.hasMatch();
        if (moreVariablesExist)
        {
            QString foundVariable = variableMatch.captured();
            int variableStartPosition = variableMatch.capturedStart();
            int variableEndPosition = variableMatch.capturedEnd();

            if (variableStartPosition > 0)
            {
                QString textInFrontOfVariable = nameScheme.left(variableStartPosition);
                parsedNameScheme << textInFrontOfVariable;
            }
            parsedNameScheme << foundVariable;
            nameScheme.remove(0, variableEndPosition);
        } else
        {
            parsedNameScheme << nameScheme;
        }
    } while (moreVariablesExist);

    return parsedNameScheme;
}

NameSchemeParser::VariableType NameSchemeParser::getVariableType(QString toCheck)
{
    if (seriesNameExpression.match(toCheck).hasMatch())
    {
        return VariableType::seriesName;
    }
    else if (airDateExpression.match(toCheck).hasMatch())
    {
        return VariableType::airDate;
    }
    else if (seasonNumberExpression.match(toCheck).hasMatch()
             || seasonNumberAdvancedExpression.match(toCheck).hasMatch())
    {
        return VariableType::seasonNumber;
    }
    else if (episodeNumberExpression.match(toCheck).hasMatch()
             || episodeNumberAdvancedExpression.match(toCheck).hasMatch())
    {
        return VariableType::episodeNumber;
    }
    else if (episodeNameExpression.match(toCheck).hasMatch())
    {
        return VariableType::episodeName;
    }
    else
    {
        return VariableType::none;
    }
}
