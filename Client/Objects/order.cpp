#include "order.h"


Order::Order()
{
}

Order::Order(int cId, double totPrice, QString oStatus, QString cTime)
    : _ClientId(cId),
      _TotalPrice(totPrice),
      _OrderStatus(oStatus),
      _CreateTime(cTime)
{
}
