#include "episodename.h"

EpisodeName::EpisodeName(
        QString oldName,
        QString newName,
        QString fileType,
        EpisodeName::Position position)
    : oldName(oldName)
    , newName(removeForbiddenCharacters(newName))
    , fileType(fileType)
    , position(position)
{
}

const QString& EpisodeName::getOldName() const
{
    return oldName;
}

const QString EpisodeName::getOldNameWithSuffix() const
{
    const auto oldNameWithSuffix = oldName + QString(".") + fileType;
    return oldNameWithSuffix;
}

const QString& EpisodeName::getNewName() const
{
    return newName;
}

const QString EpisodeName::getNewNameWithSuffix() const
{
    const auto newNameWithSuffix = newName + QString(".") + fileType;
    return newNameWithSuffix;
}

const QString& EpisodeName::getFileType() const
{
    return fileType;
}

bool EpisodeName::newAndOldAreEqual() const
{
    return (oldName == newName);
}

bool EpisodeName::isPositionDetermined() const
{
    return (position == Position::determined);
}

bool EpisodeName::atLeastOneNameEmpty() const
{
    return (newName.isEmpty() || oldName.isEmpty());
}

void EpisodeName::setOldName(QString oldName)
{
    this->oldName = oldName;
}

void EpisodeName::setNewName(QString newName)
{
    this->newName = removeForbiddenCharacters(newName);
}

void EpisodeName::setFileType(QString fileType)
{
    this->fileType = fileType;
}

void EpisodeName::setPosition(EpisodeName::Position position)
{
    this->position = position;
}

QString EpisodeName::removeForbiddenCharacters(QString string)
{
    if (string.isEmpty())
    {
        return string;
    }

    auto stringWithoutForbiddenCharacters = string;
    for (const auto& forbiddenCharacter : forbiddenCharacters)
    {
        stringWithoutForbiddenCharacters.replace(forbiddenCharacter, QString(""));
    }
    return stringWithoutForbiddenCharacters;
}
