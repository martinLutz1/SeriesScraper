#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QObject>

class JsonParser : public QObject
{
     Q_OBJECT
private:
public:
    explicit JsonParser(QObject *parent = 0);
    QString getIDfromURL(QString pUrl, QString id);

signals:

public slots:
};

#endif // JSONPARSER_H
