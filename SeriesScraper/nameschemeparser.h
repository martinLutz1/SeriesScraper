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

    enum VariableType {
        seriesName,
        airDate,
        seasonNumber,
        episodeNumber,
        episodeName,
        none
    };

    QString preParseNameScheme(QString nameScheme);
    QStringList parseNameScheme(QString nameScheme);
    int getVariableType(QString toCheck);
};

#endif // NAMESCHEMEPARSER_H
