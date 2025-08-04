#ifndef DISPATCHERH_H
#define DISPATCHERH_H

#include <qobject.h>

class Dispatcher : public QObject
{
    Q_OBJECT

public:
    explicit Dispatcher(QObject *parent = nullptr);

    void dispatch(QByteArray data);
};

#endif // DISPATCHERH_H
