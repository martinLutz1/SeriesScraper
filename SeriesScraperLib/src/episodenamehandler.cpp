#include "episodenamehandler.h"
#include <QDebug>

EpisodeNameHandler::EpisodeNameHandler()
{
}

EpisodeNameHandler::~EpisodeNameHandler()
{
    delete episodeNames;
}

void EpisodeNameHandler::clearOldNamesAndFileTypesAndPositions()
{
    clearOldNames();
    clearFileTypes();
    clearPositions();
}

void EpisodeNameHandler::setOldNames(const QStringList& oldNames)
{
    oldNameSize = oldNames.size();
    calculateAndAdjustEpisodeNamesSize();

    for (size_t i = 0; i < oldNameSize; i++)
    {
        episodeNames->at(i).setOldName(oldNames.at(i));
    }
}

void EpisodeNameHandler::setNewNames(const QStringList& newNames)
{
    clearNewNames();

    newNameSize = newNames.size();
    calculateAndAdjustEpisodeNamesSize();

    for (size_t i = 0; i < newNameSize; i++)
    {
        episodeNames->at(i).setNewName(newNames.at(i));
    }
}

void EpisodeNameHandler::setNewName(const QString newName, size_t index)
{
    // We need more space if the index describes a new episode name.
    newNameSize = std::max(newNameSize, index + 1);
    calculateAndAdjustEpisodeNamesSize();

    episodeNames->at(index).setNewName(newName);
}

void EpisodeNameHandler::setFileTypes(const QStringList& fileTypes)
{
    for (size_t i = 0; i < oldNameSize; i++)
    {
        episodeNames->at(i).setFileType(fileTypes.at(i));
    }
}

void EpisodeNameHandler::setPositionDetermination(const Positions &positions)
{
    for (size_t i = 0; i < oldNameSize; i++)
    {
        episodeNames->at(i).setPosition(positions.at(i));
    }
}

EpisodeNames* EpisodeNameHandler::getEpisodeNames()
{
    return episodeNames;
}

bool EpisodeNameHandler::atLeastOneEpisodeNameDiffers() const
{
    auto atLeastOneDiffers = false;

    for (auto& episodeName: *episodeNames)
    {
        if (!episodeName.newAndOldAreEqual())
        {
            atLeastOneDiffers = true;
            break;
        }
    }
    return atLeastOneDiffers;
}

bool EpisodeNameHandler::atLeastOneSideEmpty() const
{
    auto oldNamesEmpty = true;
    auto newNamesEmpty = true;

    for (auto& episodeName: *episodeNames)
    {
        if (!episodeName.getOldName().isEmpty())
        {
            oldNamesEmpty = false;
        }
        if (!episodeName.getNewName().isEmpty())
        {
            newNamesEmpty = false;
        }
        if (!oldNamesEmpty && !newNamesEmpty)
        {
            return false;
        }
    }
    return true;
}

bool EpisodeNameHandler::atLeastOneEpisodeCanBeRenamed() const
{
    for (auto& episodeName: *episodeNames)
    {
        if (!episodeName.atLeastOneNameEmpty() &&
                !episodeName.newAndOldAreEqual())
        {
            return true;
        }
    }
    return false;
}

void EpisodeNameHandler::calculateAndAdjustEpisodeNamesSize()
{
    const auto newEpisodeNameSize = std::max(oldNameSize, newNameSize);

    episodeNames->resize(newEpisodeNameSize);
}

void EpisodeNameHandler::clearOldNames()
{
    for (size_t i = 0; i < oldNameSize; i++)
    {
        episodeNames->at(i).setOldName(QString());
    }
}

void EpisodeNameHandler::clearNewNames()
{
    for (size_t i = 0; i < newNameSize; i++)
    {
        episodeNames->at(i).setNewName(QString());
    }
}

void EpisodeNameHandler::clearFileTypes()
{
    for (size_t i = 0; i < oldNameSize; i++)
    {
        episodeNames->at(i).setFileType(QString());
    }
}

void EpisodeNameHandler::clearPositions()
{
    for (size_t i = 0; i < oldNameSize; i++)
    {
        episodeNames->at(i).setPosition(EpisodeName::Position::unsure);
    }
}
