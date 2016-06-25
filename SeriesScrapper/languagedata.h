#ifndef LANGUAGEDATA_H
#define LANGUAGEDATA_H
#include <QString>

class LanguageData
{
public:
    LanguageData();
    QString getEpisodeName();
    QString getFileName();
    QString getDirectorySelection();
    QString getPath();
    QString getSelection();
    QString getSeries();
    QString getSeriesSelection();
    QString getSeason();
    QString getEpisode();

    void setEpisodeName(QString newEpisodeName);
    void setFileName(QString newFileName);
    void setDirectorySelection(QString newDirectorySelection);
    void setPath(QString newPath);
    void setSelection(QString newSelection);
    void setSeries(QString newSeries);
    void setSeriesSelection (QString newSeriesSelection);
    void setSeason(QString newSeason);
    void setEpisode(QString newEpisode);

private:
    QString episodeName;
    QString fileName;
    QString directorySelection;
    QString path;
    QString selection;
    QString series;
    QString seriesSelection;
    QString season;
    QString episode;
};

#endif // LANGUAGEDATA_H
