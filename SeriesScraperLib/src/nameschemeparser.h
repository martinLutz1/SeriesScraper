#ifndef NAMESCHEMEPARSER_H
#define NAMESCHEMEPARSER_H
#include <QStringList>
#include <QRegularExpression>

class NameSchemeParser
{
public:
    NameSchemeParser();
    void setNameScheme(QString nameScheme);
    QString getFileName(QString series, QString airDate, QString season, QString episode, QString episodeName);
    QString getNameSchemeRepresentation();

private:
    enum class VariableType
    {
        seriesName,
        airDate,
        seasonNumber,
        episodeNumber,
        episodeName,
        none
    };

private:
    QRegularExpression nameSchemeNameExpression;
    QRegularExpression replaceExpression;
    QRegularExpression generalVariableExpression;

    QRegularExpression seriesNameExpression;
    QRegularExpression airDateExpression;
    QRegularExpression seasonNumberExpression;
    QRegularExpression seasonNumberAdvancedExpression;
    QRegularExpression episodeNumberAdvancedExpression;
    QRegularExpression episodeNumberExpression;
    QRegularExpression episodeNameExpression;
    QRegularExpression numberExpression;

    QStringList parsedNameSchemeList;
    QString nameSchemeName;
    QStringList replaceFrom, replaceTo;

    QString preParseNameScheme(QString nameScheme);
    QStringList parseNameScheme(QString nameScheme);
    VariableType getVariableType(QString toCheck);
};

#endif // NAMESCHEMEPARSER_H
