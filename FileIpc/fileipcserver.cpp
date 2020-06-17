#include "fileipcserver.h"
#include "fs.h"

FileIpcServer::FileIpcServer(const Medium & medium)
   : medium_{medium}
{

}

void FileIpcServer::listen(int thisId)
{
   this->inConnectFile_.setFileName(medium_.createFilePath(thisId));
}

bool FileIpcServer::waitForNewConnection(int msec)
{
   return Fs::waitForReadyRead(this->inConnectFile_, msec);
}


FileIpc * FileIpcServer::newConnection()
{
   QString clientIdString = Fs::readFrom(this->inConnectFile_);
   if (clientIdString.length() == 0) return nullptr;
   int clientId = clientIdString.toInt();
   int pairId = medium_.getNewId();
   FileIpc * ipc = new FileIpc(medium_, pairId, clientId);
   ipc->write(QString::number(pairId));
   return ipc;
}

