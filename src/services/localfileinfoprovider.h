#ifndef LOCALFILEINFOPROVIDER_H
#define LOCALFILEINFOPROVIDER_H

#include "../models/fileinfo.h"
#include <qlist.h>
#include <qstring.h>

class LocalFileInfoProvider
{
public:
    static QList<FileInfo> get(const QString& path);
};

#endif // LOCALFILEINFOPROVIDER_H
