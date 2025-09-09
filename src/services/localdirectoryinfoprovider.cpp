#include "localdirectoryinfoprovider.h"
#include <qdir.h>
#include <qfileinfo.h>

DirectoryInfo LocalDirectoryInfoProvider::get(const QString& path)
{
    QDir dir(path);
    DirectoryInfo directoryInfo{path};

    if (dir.exists())
    {
        const QList<QFileInfo> entries = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
        directoryInfo.filesInfo.reserve(entries.count());

        for (const QFileInfo& entry : entries)
        {
            directoryInfo.filesInfo.append({entry.baseName(),
                                            entry.suffix(),
                                            entry.lastModified(),
                                            entry.isDir() ? 0 : static_cast<quint64>(entry.size()),
                                            entry.isDir()});
        }
    }

    return directoryInfo;
}
