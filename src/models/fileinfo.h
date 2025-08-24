#ifndef FILEINFO_H
#define FILEINFO_H

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

#endif // FILEINFO_H