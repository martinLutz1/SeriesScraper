#ifndef NAMESCHEMEPARSER_H
#define NAMESCHEMEPARSER_H
#include <QStringList>
#include <QRegExp>

class NameSchemeParser
{
public:
    NameSchemeParser();
    void parseNameScheme(QString nameScheme);
    QString getFileName(QString series, QString season, QString episode, QString episodeName);
    QString getNameSchemeRepresentation();

private:
    QRegExp seriesNameExpression;
    QRegExp seasonNumberExpression;
    QRegExp episodeNumberAdvancedExpression;
    QRegExp episodeNumberExpression;
    QRegExp episodeNameExpression;
    QRegExp numberExpression;
    QRegExp nextVariableExpression;

    QStringList parsedNameSchemeList;
    enum VariableType {
        seriesName,
        seasonNumber,
        episodeNumber,
        episodeName,
        none
    };

    int getVariableType(QString toCheck);
};

#endif // NAMESCHEMEPARSER_H
