#ifndef SEARCH_H
#define SEARCH_H

#include <QString>
#include "objects.h"

class Search
{
PROPERTY_CREATE_H(int, ClientId);
PROPERTY_CREATE_H(int, ProductId);
PROPERTY_CREATE_H(QString, SearchTime);   //toString("yyyy-MM-dd hh:mm:ss")
PROPERTY_CREATE_H(int, SearchCount);

public:
    Search();
    Search(int cId, int pId, QString sTime, int sCount);
};

#endif // SEARCH_H
