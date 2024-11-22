#include "order.h"


Order::Order()
{
}

Order::Order(int cId, double totPrice, QString oStatus, QString cTime, QString fTime)
    : clientId(cId),
      totalPrice(totPrice),
      orderStatus(oStatus),
      createTime(cTime),
      finishTime(fTime)
{
}

int Order::getClientId() const
{
    return clientId;
}

void Order::setClientId(int value)
{
    clientId = value;
}

double Order::getTotalPrice() const
{
    return totalPrice;
}

void Order::setTotalPrice(double value)
{
    totalPrice = value;
}

QString Order::getCreateTime() const
{
    return createTime;
}

void Order::setCreateTime(const QString &value)
{
    createTime = value;
}

QString Order::getFinishTime() const
{
    return finishTime;
}

void Order::setFinishTime(const QString &value)
{
    finishTime = value;
}
