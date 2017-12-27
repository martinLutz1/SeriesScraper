#ifndef EPISODENAME_H
#define EPISODENAME_H

#include <QString>
#include <QStringList>
#include <vector>

class EpisodeName
{
public:
    enum class Position
    {
        determined,
        unsure
    };

public:
    EpisodeName(
            QString oldName = "",
            QString newName = "",
            QString fileType = "",
            Position position = Position::unsure);

    const QString getOldName() const;
    const QString getOldNameWithSuffix() const;
    const QString getNewName() const;
    const QString getNewNameWithSuffix() const;
    const QString getFileType() const;
    bool newAndOldAreEqual() const;
    bool isPositionDetermined() const;
    bool atLeastOneNameEmpty() const;

    void setOldName(QString oldName);
    void setNewName(QString newName);
    void setFileType(QString fileType);
    void setPosition(Position position);

private:
    QString oldName = "";
    QString newName = "";
    QString fileType = "";
    Position position = Position::unsure;

    QStringList forbiddenCharacters {"<", ">", ":", "\"", "/", "|", "?", "*"};
    QString removeForbiddenCharacters(QString string);
};

using EpisodeNames = std::vector<EpisodeName>;

#endif // EPISODENAME_H
