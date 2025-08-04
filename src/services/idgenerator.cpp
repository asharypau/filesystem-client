#include "idgenerator.h"

QString IdGenerator::generate(const QString& base)
{
    QDateTime now = QDateTime::currentDateTime();
    QString timeStr = now.toString("yyyyMMdd-HHmmss-zzz");

    QByteArray hash = QCryptographicHash::hash(base.toUtf8(), QCryptographicHash::Sha1).toHex();
    QString hashPart = QString::fromLatin1(hash.left(8));

    return QString("%1-%2").arg(timeStr, hashPart);
}
