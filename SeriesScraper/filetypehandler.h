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
    int addFileType(QString newFileType);
    void removeFileType(int index);

private:
    QFile *fileTypeFile;
    void sort();
};

#endif // FILETYPEHANDLER_H
