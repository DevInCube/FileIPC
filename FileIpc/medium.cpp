#include "medium.h"
#include <QRandomGenerator>

Medium::Medium(const QString & dirpath)
  : dirpath_{dirpath}
{

}

QString Medium::createFilePath(int id)
{
   return this->dirpath_ + QString::number(id) + ".txt";
}

int Medium::getNewId()
{
   return 100 + QRandomGenerator::global()->generate() % 1000;
}
