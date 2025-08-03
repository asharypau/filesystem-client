#ifndef APPVIEWMODEL_H
#define APPVIEWMODEL_H

#include <qobject.h>

class MainViewModel : public QObject
{
    Q_OBJECT

public:
    explicit MainViewModel(QObject* parent = nullptr)
        : QObject(parent)
    {
    }
};

#endif // APPVIEWMODEL_H
