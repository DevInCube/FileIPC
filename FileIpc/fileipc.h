#ifndef FILEIPC_H
#define FILEIPC_H

#include <QFile>
#include "medium.h"

class FileIpc
{
   Medium medium_;

   QFile infile_;
   QFile outfile_;

public:
   explicit FileIpc(const Medium & medium);
   FileIpc(const Medium & medium, int inId, int outId);

   void connectTo(int serverId);
   bool waitForConnected(int msec = 30000);


   void write(const QString &message);
   bool waitForReadyRead(int msec = 30000);

   QString read();
};


#endif // FILEIPC_H
