#include "orderlist.h"


OrderList::OrderList()
{
}

OrderList::OrderList(int oId, int pId, int pNum, double pPrice)
    : orderId(oId),
      productId(pId),
      productNum(pNum),
      productPrice(pPrice)
{
}

int OrderList::getOrderId() const
{
    return orderId;
}

void OrderList::setOrderId(int value)
{
    orderId = value;
}

int OrderList::getProductId() const
{
    return productId;
}

void OrderList::setProductId(int value)
{
    productId = value;
}

int OrderList::getProductNum() const
{
    return productNum;
}

void OrderList::setProductNum(int value)
{
    productNum = value;
}

double OrderList::getProductPrice() const
{
    return productPrice;
}

void OrderList::setProductPrice(double value)
{
    productPrice = value;
}
