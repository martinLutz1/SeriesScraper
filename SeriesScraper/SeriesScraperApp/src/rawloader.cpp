#include "rawloader.h"
#include <QTextStream>

RawLoader::RawLoader()
{

}

bool RawLoader::loadFile(QFile *file)
{
    bool successReading = file->open(QIODevice::ReadOnly);
    if (successReading)
    {
        QTextStream in(file);
        while (!in.atEnd())
        {
            QString line = in.readLine();
            if (!line.isEmpty())
                loadedFile << line;
        }
    }
    file->close();
    return successReading;
}

bool RawLoader::saveFile(QFile *file)
{
    bool successReading = file->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    if (successReading)
    {
        int size = loadedFile.size();
        QTextStream inOut(file);

        for (int i = 0; i < size; i++)
        {
            if (i - size == 0) // Last item
                inOut << loadedFile.at(i);
            else
                inOut << loadedFile.at(i) << "\n";
        }
    }
    file->close();
    return successReading;
}
