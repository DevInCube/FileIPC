#include "fileipc.h"
#include "fileipcserver.h"
#include <QDebug>
#include <QVector>
#include <QThread>

#include "console.h"

class ClientThread : public QThread
{
    FileIpc * ipc_;

 public:
    ClientThread(FileIpc * ipc): ipc_{ipc} {}

    void run() override
    {
        qDebug() << "# new thread started";
        while (!Console::isKeyDown())
        {
            qDebug() << "# waiting for request...";
            if (!ipc_->waitForReadyRead(500))
                continue;
             QString incoming = ipc_->read();
             qDebug() << "# got request:";
             qDebug().quote() << incoming;
             //
             QString outgoing = "Hi from S!";
             qDebug() << "# sending response: ";
             qDebug().quote() << outgoing;
             ipc_->write(outgoing);
        }
        delete ipc_;
        qDebug() << "# new thread finished";
    }

};

int main()
{
   qDebug() << "This is app S (Server)";
   Medium medium{"./../../files/"};
   FileIpcServer server{medium};
    qDebug() << "# listening on id 1";
   server.listen(1);
   QVector<ClientThread *> threads;
   while (!Console::isKeyDown())
   {
       qDebug() << "# waiting for connection...";
       if (!server.waitForNewConnection(3000))
           continue;
        FileIpc * clientIpc = server.newConnection();
        qDebug() << "# got new connection";
        //
        ClientThread * clientThread = new ClientThread{clientIpc};
        clientThread->start();
        threads.push_back(clientThread);
   }
   qDebug() << "# server is stopping...";
   for (ClientThread * ct : threads)
   {
       ct->wait();
       delete ct;
   }
}

