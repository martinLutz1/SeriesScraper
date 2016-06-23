#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QObject>

class JsonParser : public QObject
{
     Q_OBJECT
private:
    QStringList idList;
    int amountSeasons;

public:
    explicit JsonParser(QObject *parent = 0);

signals:

public slots:
    bool getSeriesSeason(QString url, QString series, int season, QString id);
    // Only execute if getIDfromURL returned true before, otherwise you will get an empty string
    QStringList getIDValue();
    int getAmountSeasons();
};

#endif // JSONPARSER_H
