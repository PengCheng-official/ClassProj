#ifndef ORDERLIST_H
#define ORDERLIST_H


#include <QString>
#include "objects.h"
#include "product.h"

class OrderList
{
PROPERTY_CREATE_H(int, OrderId);
PROPERTY_CREATE_H(int, ProductId);
PROPERTY_CREATE_H(int, ProductNum);
PROPERTY_CREATE_H(double, ProductPrice);

public:
    OrderList();
    OrderList(int oId, int pId, int pNum, double pPrice);
};

#endif // ORDERLIST_H
