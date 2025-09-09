#ifndef LOCALDIRECTORYINFOPROVIDER_H
#define LOCALDIRECTORYINFOPROVIDER_H

#include "../models/fileinfo.h"
#include <qstring.h>

class LocalDirectoryInfoProvider
{
public:
    static DirectoryInfo get(const QString& path);
};

#endif // LOCALDIRECTORYINFOPROVIDER_H
