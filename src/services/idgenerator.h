#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include <QCryptographicHash>
#include <QDateTime>
#include <QString>

class IdGenerator
{
public:
    static QString generate(const QString& base);
};

#endif // IDGENERATOR_H
