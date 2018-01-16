#ifndef RAWLOADER_H
#define RAWLOADER_H

#include <QStringList>
#include <QFile>

class RawLoader
{
public:
    RawLoader();

protected:
    bool loadFile(QFile *file);
    bool saveFile(QFile *file);
    QStringList loadedFile;
};

#endif // RAWLOADER_H
