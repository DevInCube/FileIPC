#ifndef FILEIPCSERVER_H
#define FILEIPCSERVER_H

#include <QFile>
#include "medium.h"
#include "fileipc.h"

class FileIpcServer
{
   Medium medium_;

   QFile inConnectFile_;

public:
   explicit FileIpcServer(const Medium & medium);

   void listen(int thisId);
   bool waitForNewConnection(int msec = 30000);
   FileIpc * newConnection();
};


#endif // FILEIPCSERVER_H
