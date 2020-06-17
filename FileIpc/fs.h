#ifndef FS_H
#define FS_H

#include <QFile>

namespace Fs {
void writeTo(QFile & out, const QString &message);
bool waitForReadyRead(QFile & in, int msec = 30000);
QString readFrom(QFile & in);
}


#endif // FS_H
