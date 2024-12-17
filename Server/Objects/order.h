#ifndef ORDER_H
#define ORDER_H


#include <QString>
#include "objects.h"

class Order
{
PROPERTY_CREATE_H(int, OrderId);
PROPERTY_CREATE_H(int, ClientId);
PROPERTY_CREATE_H(int, ProductNum);
PROPERTY_CREATE_H(double, TotalPrice);
PROPERTY_CREATE_H(QString, OrderStatus);
// ENUM{'未支付', '已支付', '已完成', '已取消', '已退款'}
PROPERTY_CREATE_H(QString, CreateTime);
PROPERTY_CREATE_H(QString, FinishTime);

public:
    Order();
    Order(int cId, double totPrice, QString oStatus, QString cTime);
};

#endif // ORDER_H
