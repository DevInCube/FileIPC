#ifndef MEDIUM_H
#define MEDIUM_H

#include <QString>

class Medium
{
   QString dirpath_;

public:
   explicit Medium(const QString & dirpath);

   QString createFilePath(int id);
   int getNewId();
};


#endif // MEDIUM_H
