#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include "objects.h"

class Product
{
PROPERTY_CREATE_H(int, ProductId);
PROPERTY_CREATE_H(QString, ProductName);
PROPERTY_CREATE_H(double, ProductPrice);
PROPERTY_CREATE_H(int, ProductNum);
PROPERTY_CREATE_H(int, ProductSales);
PROPERTY_CREATE_H(QString, ProductAbout);
PROPERTY_CREATE_H(QString, ProductImage);

private:
    //促销策略
    int _ProductStrategy;
    double _num1;
    double _num2;

public:
    Product();
    Product(
            int pId,
            const QString &pName,
            double pPrice,
            int pNum,
            int pSales,
            const QString &pAbout,
            const QString& pImage
            );

    //促销策略
    void setStrategy(int pStrategy, double num1, double num2);
    void applyStrategy(double &price, int &num);
};

#endif // PRODUCT_H
