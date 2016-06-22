#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QObject>

class JsonParser : public QObject
{
     Q_OBJECT
private:
    QStringList idList;
public:
    explicit JsonParser(QObject *parent = 0);

signals:

public slots:
    bool getIDfromURL(QString pUrl, QString id);
    // Only execute if getIDfromURL returned true before, otherwise you will get an empty string
    QStringList getIDValue();
};

#endif // JSONPARSER_H
