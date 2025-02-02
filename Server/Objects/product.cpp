#include "product.h"


Product::Product()
    : _ProductStrategy(0)
{
}

Product::Product(int pId, const QString &pName, double pPrice, int pNum, int pSales, const QString &pAbout, const QString &pImage)
    : _ProductId(pId)
    , _ProductName(pName)
    , _ProductPrice(pPrice)
    , _ProductNum(pNum)
    , _ProductSales(pSales)
    , _ProductAbout(pAbout)
    , _ProductImage(pImage)
    , _ProductStrategy(0)
{
}

void Product::setStrategy(int pStrategy, double num1, double num2)
{
    _ProductStrategy = pStrategy;
    _num1 = num1;
    _num2 = num2;
}

int Product::getStrategy() const
{
    return _ProductStrategy;
}

double Product::getStrategy1() const
{
    return _num1;
}

double Product::getStrategy2() const
{
    return _num2;
}

void Product::applyStrategy(double &price, int &num)
{
    switch(_ProductStrategy)
    {
    case 1:
    {
        price = price * _num1 / 10.0;
        break;
    }
    case 2:
    {
        if (price * num > _num1) {
            price -= _num2 / num;
        }
        break;
    }
    case 3:
    {
        if (num > _num1) {
            num += _num2;
        }
        break;
    }
    case 4:
    {
        if (num <= _num1) price = _num2;
        else {
            price = _num1 * _num2 + _ProductPrice * (num - _num1);
        }
        break;
    }
    default: break;
    }
}
