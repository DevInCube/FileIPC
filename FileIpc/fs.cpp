#include "fs.h"
#include <QTextStream>
#include <QThread>

void Fs::writeTo(QFile & out, const QString &message)
{
   while (!out.open(QFile::WriteOnly))
       QThread::msleep(50);
   QTextStream ts{&out};
   ts << message;
   out.flush();
   out.close();
}


bool Fs::waitForReadyRead(QFile & in, int msec)
{
    int time = 0;
    while (in.size() == 0)
    {
        if (time >= msec)
            return false;
        QThread::msleep(250);
        time += 250;
    }
    return true;
}

QString Fs::readFrom(QFile & in)
{
  while (!in.open(QFile::ReadOnly))
      QThread::msleep(50);
  QTextStream ts{&in};
  QString incomingMessage = ts.readAll();
  in.close();
  in.resize(0);  // clear file
  return incomingMessage;
}
