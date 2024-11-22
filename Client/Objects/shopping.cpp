#include "shopping.h"


Shopping::Shopping()
{
}

Shopping::Shopping(int cId, int pId, int sNum, double sPrice)
    : clientId(cId),
      productId(pId),
      shoppingNum(sNum),
      shoppingPrice(sPrice)
{
}

int Shopping::getClientId() const
{
    return clientId;
}

void Shopping::setClientId(int value)
{
    clientId = value;
}

int Shopping::getProductId() const
{
    return productId;
}

void Shopping::setProductId(int value)
{
    productId = value;
}

int Shopping::getShoppingNum() const
{
    return shoppingNum;
}

void Shopping::setShoppingNum(int value)
{
    shoppingNum = value;
}

double Shopping::getShoppingPrice() const
{
    return shoppingPrice;
}

void Shopping::setShoppingPrice(double value)
{
    shoppingPrice = value;
}
