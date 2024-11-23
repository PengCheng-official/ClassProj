#include "shopping.h"


Shopping::Shopping()
{
}

Shopping::Shopping(int cId, int pId, int sNum, double sPrice)
    : _ClientId(cId),
      _ProductId(pId),
      _ShoppingNum(sNum),
      _ShoppingPrice(sPrice)
{
}
