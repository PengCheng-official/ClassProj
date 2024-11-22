#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product
{
private:
    int productId;
    QString productName;
    double productPrice;
    int productNum;
    int productSales;
    QString productAbout;
    QString productImage;

    //促销策略
    int productStrategy;
    double s_num1;
    double s_num2;

public:
    Product();
    Product(int pId, const QString &pName, double pPrice, int pNum, int pSales, const QString &pAbout, const QString& pImage);

    //促销策略
    void setStrategy(int pStrategy, double num1, double num2);
    void applyStrategy(double &price, int &num);

    int getProductId() const;
    QString getProductName() const;
    double getProductPrice() const;
    int getProductNum() const;
    int getProductSales() const;
    QString getProductAbout() const;
    QString getProductImage() const;

    void setProductId(int value);
    void setProductName(const QString &value);
    void setProductPrice(double value);
    void setProductNum(int value);
    void setProductSales(int value);
    void setProductAbout(const QString &value);
    void setProductImage(const QString &value);
};

#endif // PRODUCT_H
