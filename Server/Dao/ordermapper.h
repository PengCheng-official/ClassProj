#ifndef ORDERMAPPER_H
#define ORDERMAPPER_H


#include "mapper.h"

class Order;
class OrderMapper : public Mapper
{
public:
    OrderMapper(QSqlDatabase &database);

public:
    Order *getOrder(const QSqlQuery &query);

    QList<Order *> select(int cid);
    // 返回用户cid的全部订单

    QList<Order *> select();
    // 返回全部订单

    int insert(const Order *order);
    // 返回订单号

    void update(const Order *order);
};

#endif // ORDERMAPPER_H
