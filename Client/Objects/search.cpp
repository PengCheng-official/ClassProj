#include "search.h"


Search::Search()
    : _SearchCount(0)
{
}

Search::Search(int cId, int pId, QString sTime, int sCount)
    : _ClientId(cId)
    , _ProductId(pId)
    , _SearchTime(sTime)
    , _SearchCount(sCount)
{
}
