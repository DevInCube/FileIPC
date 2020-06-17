#include "fileipc.h"
#include "fs.h"
#include <QTextStream>
#include <QThread>

FileIpc::FileIpc(const Medium & medium)
   : medium_{medium}
{

}

FileIpc::FileIpc(const Medium & medium, int inId, int outId)
   : medium_{medium},
     infile_{medium_.createFilePath(inId)},
     outfile_{medium_.createFilePath(outId)}
{

}

void FileIpc::connectTo(int serverId)
{
    int thisId = medium_.getNewId();
    this->infile_.setFileName(medium_.createFilePath(thisId));
    QFile serverConnectFile{medium_.createFilePath(serverId)};
    Fs::writeTo(serverConnectFile, QString::number(thisId));
}

bool FileIpc::waitForConnected(int msec)
{
   if (!Fs::waitForReadyRead(this->infile_, msec))
       return false;
   QString response = Fs::readFrom(this->infile_);
   int pairedId = response.toInt();
   this->outfile_.setFileName(medium_.createFilePath(pairedId));
   return true;
}


void FileIpc::write(const QString &message)
{
   Fs::writeTo(outfile_, message);
}

bool FileIpc::waitForReadyRead(int msec)
{
   return Fs::waitForReadyRead(this->infile_, msec);
}


QString FileIpc::read()
{
   return Fs::readFrom(infile_);
}
