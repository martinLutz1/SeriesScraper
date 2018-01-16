#ifndef EPISODENAMEHANDLER_H
#define EPISODENAMEHANDLER_H

#include "episodename.h"
#include <QStringList>
#include <vector>

using Positions = std::vector<EpisodeName::Position>;

class EpisodeNameHandler
{
public:
    EpisodeNameHandler();
    ~EpisodeNameHandler();

    void clearOldNamesAndFileTypesAndPositions();
    void setOldNames(const QStringList& oldNames);
    void setNewNames(const QStringList& newNames);
    void setNewName(const QString newName, size_t index);
    void setFileTypes(const QStringList& fileTypes);
    void setPositionDetermination(const Positions& positions);

    EpisodeNames* getEpisodeNames();
    bool atLeastOneEpisodeNameDiffers() const;
    bool atLeastOneSideEmpty() const;
    bool atLeastOneEpisodeCanBeRenamed() const;

private:
    EpisodeNames* episodeNames = new EpisodeNames;
    size_t newNameSize = 0;
    size_t oldNameSize = 0;

private:
    void calculateAndAdjustEpisodeNamesSize();
    void clearOldNames();
    void clearNewNames();
    void clearFileTypes();
    void clearPositions();
};

#endif // EPISODENAMEHANDLER_H
