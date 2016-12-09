#ifndef FILETYPEHANDLER_H
#define FILETYPEHANDLER_H

#include "rawloader.h"
#include  <QFile>

class FileTypeHandler : public RawLoader
{
public:
    FileTypeHandler();
    ~FileTypeHandler();
    bool loadFileTypeFile();
    bool saveFileTypeFile();
    QStringList getFileTypes();

private:
    QFile *fileTypeFile;
};

#endif // FILETYPEHANDLER_H