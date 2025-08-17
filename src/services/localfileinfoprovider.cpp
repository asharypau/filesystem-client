#include "localfileinfoprovider.h"
#include <qdir.h>
#include <qfileinfo.h>

QList<FileInfo> LocalFileInfoProvider::get(const QString& path)
{
    QDir dir(path);
    QList<FileInfo> filesInfo;

    if (dir.exists())
    {
        const QList<QFileInfo> entries = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
        for (const QFileInfo& entry : entries)
        {
            filesInfo.append({entry.baseName(),
                              entry.suffix(),
                              entry.lastModified(),
                              entry.isDir() ? 0 : static_cast<quint64>(entry.size()),
                              entry.isDir()});
        }
    }

    return filesInfo;
}
