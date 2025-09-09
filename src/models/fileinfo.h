#ifndef FILEINFO_H
#define FILEINFO_H

#include "qlist.h"
#include <qdatetime.h>
#include <qstring.h>

class FileInfo
{
public:
    QString name;
    QString extension;
    QDateTime lastModifiedDate;
    quint64 size;
    bool isDirectory;
};

class DirectoryInfo
{
public:
    QString path;
    QList<FileInfo> filesInfo;
};

#endif // FILEINFO_H