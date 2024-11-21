#include "product.h"


Product::Product()
    : productStrategy(0)
{
}

Product::Product(int pId, const QString &pName, double pPrice, int pNum, int pSales, const QString &pAbout, const QString &pImage)
    : productId(pId)
    , productName(pName)
    , productPrice(pPrice)
    , productNum(pNum)
    , productSales(pSales)
    , productAbout(pAbout)
    , productImage(pImage)
    , productStrategy(0)
{
}

void Product::setStrategy(int pStrategy, double num1, double num2)
{
    productStrategy = pStrategy;
    s_num1 = num1;
    s_num2 = num2;
}

void Product::applyStrategy(double &price, int &num)
{
    switch(productStrategy)
    {
    case 1:
    {
        price = price * s_num1 / 100.0;
        break;
    }
    case 2:
    {
        if (price * num > s_num1) {
            price -= s_num2 / num;
        }
        break;
    }
    case 3:
    {
        if (num > s_num1) {
            num += s_num2;
        }
        break;
    }
    case 4:
    {
        price = s_num1;
        break;
    }
    default: break;
    }
}

int Product::getProductId() const
{
    return productId;
}

void Product::setProductId(int value)
{
    productId = value;
}

QString Product::getProductName() const
{
    return productName;
}

void Product::setProductName(const QString &value)
{
    productName = value;
}

double Product::getProductPrice() const
{
    return productPrice;
}

void Product::setProductPrice(double value)
{
    productPrice = value;
}

int Product::getProductNum() const
{
    return productNum;
}

void Product::setProductNum(int value)
{
    productNum = value;
}

int Product::getProductSales() const
{
    return productSales;
}

void Product::setProductSales(int value)
{
    productSales = value;
}

QString Product::getProductAbout() const
{
    return productAbout;
}

void Product::setProductAbout(const QString &value)
{
    productAbout = value;
}

QString Product::getProductImage() const
{
    return productImage;
}

void Product::setProductImage(const QString &value)
{
    productImage = value;
}
