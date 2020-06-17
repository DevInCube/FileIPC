#include "fileipc.h"
#include <QDebug>
#include <QThread>
#include "console.h"

int main()
{
   qDebug() << "This is app A (Client)";
   Medium medium{"./../../files/"};
   FileIpc ipc{medium};
   //
   ipc.connectTo(1);
   if (!ipc.waitForConnected(5000))
   {
       qDebug() << "Can't establish connection.";
       return 1;
   }
   //
   while (!Console::isKeyDown())
   {
       QString outgoing = "Hello from A!";
       qDebug() << "# sending request: ";
       qDebug().quote() << outgoing;
       ipc.write(outgoing);
       //
       while (!Console::isKeyDown())
       {
           qDebug() << "# waiting for response...";
           if (ipc.waitForReadyRead(1000))
               break;
       }
       if (Console::isKeyDown())
           break;
       QString incoming = ipc.read();
       qDebug() << "# got response:";
       qDebug().quote() << incoming;
       //
       QThread::msleep(2000);
   }
}
