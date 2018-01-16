#ifndef GENERICFILEDOWNLOADER_H
#define GENERICFILEDOWNLOADER_H

#include "basefiledownloader.h"


class GenericFileDownloader : public BaseFileDownloader
{
public:
    GenericFileDownloader();

private:
    bool download(QString url) override;
};

#endif // GENERICFILEDOWNLOADER_H
