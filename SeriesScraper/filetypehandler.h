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

    QStringList getFileTypes();
    int addFileType(QString newFileType);
    void removeFileType(int index);
    int setFileType(int index, QString newFileType);

private:
    QFile *fileTypeFile;
    bool saveFileTypeFile();
    void sort();
};

#endif // FILETYPEHANDLER_H
