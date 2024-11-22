#ifndef ORDERLIST_H
#define ORDERLIST_H


#include <QString>

class OrderList
{
private:
    int orderId;
    int productId;
    int productNum;
    double productPrice;

public:
    OrderList();
    OrderList(int oId, int pId, int pNum, double pPrice);

    int getOrderId() const;
    int getProductId() const;
    int getProductNum() const;
    double getProductPrice() const;

    void setOrderId(int value);
    void setProductId(int value);
    void setProductNum(int value);
    void setProductPrice(double value);
};

#endif // ORDERLIST_H
