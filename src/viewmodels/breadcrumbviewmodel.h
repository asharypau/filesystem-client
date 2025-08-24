#ifndef BREADCRUMB_H
#define BREADCRUMB_H

#include "qlist.h"
#include "qobject.h"
#include "qstring.h"

class BreadcrumbViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QString> pathItems READ pathItems NOTIFY pathItemsChanged)

public:
    BreadcrumbViewModel(QObject* parent = nullptr);

    const QList<QString>& pathItems() const { return _pathItems; }

signals:
    void pathItemsChanged();

private:
    QList<QString> _pathItems;
};

#endif // BREADCRUMB_H
