#ifndef SHOPPING_H
#define SHOPPING_H


#include <QString>

class Shopping
{
private:
    int clientId;
    int productId;
    int shoppingNum;
    double shoppingPrice;

public:
    Shopping();
    Shopping(int cId, int pId, int sNum, double sPrice);

    int getClientId() const;
    int getProductId() const;
    int getShoppingNum() const;
    double getShoppingPrice() const;

    void setClientId(int value);
    void setProductId(int value);
    void setShoppingNum(int value);
    void setShoppingPrice(double value);
};

#endif // SHOPPING_H
