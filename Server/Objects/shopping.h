#ifndef SHOPPING_H
#define SHOPPING_H


#include <QString>
#include "objects.h"

class Shopping
{
PROPERTY_CREATE_H(int, ClientId);
PROPERTY_CREATE_H(int, ProductId);
PROPERTY_CREATE_H(int, ShoppingNum);
PROPERTY_CREATE_H(double, ShoppingPrice);

public:
    Shopping();
    Shopping(int cId, int pId, int sNum, double sPrice);
};

#endif // SHOPPING_H
