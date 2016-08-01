#ifndef LANGUAGECONTROL_H
#define LANGUAGECONTROL_H

#include "languagedata.h"
#include <QDir>


class LanguageControl
{
private:
   LanguageData languageData;
   QDir languageFileDirectory;

public:
    LanguageControl();
    bool loadLanguage(QString language);
    QString getEpisodeName();
    QString getFileName();
    QString getDirectorySelection();
    QString getPath();
    QString getSelection();
    QString getSeries();
    QString getSeriesSelection();
    QString getSeason();
    QString getEpisode();
};

#endif // LANGUAGECONTROL_H
