#include "orderlist.h"


OrderList::OrderList()
{
}

OrderList::OrderList(int oId, int pId, int pNum, double pPrice)
    : _OrderId(oId),
      _ProductId(pId),
      _ProductNum(pNum),
      _ProductPrice(pPrice)
{
}
