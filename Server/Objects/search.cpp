#include "search.h"


Search::Search()
    : searchCount(0)
{
}

Search::Search(int cId, int pId, QString sTime, int sCount)
    : clientId(cId)
    , productId(pId)
    , searchTime(sTime)
    , searchCount(sCount)
{
}

int Search::getClientId() const
{
    return clientId;
}

void Search::setClientId(int value)
{
    clientId = value;
}

int Search::getProductId() const
{
    return productId;
}

void Search::setProductId(int value)
{
    productId = value;
}

QString Search::getSearchTime() const
{
    return searchTime;
}

void Search::setSearchTime(const QString &value)
{
    searchTime = value;
}

int Search::getSearchCount() const
{
    return searchCount;
}

void Search::setSearchCount(int value)
{
    searchCount = value;
}
