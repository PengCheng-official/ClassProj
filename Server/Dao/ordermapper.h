#ifndef ORDERMAPPER_H
#define ORDERMAPPER_H


#include "mapper.h"

class Order;
class OrderMapper : public Mapper
{
public:
    OrderMapper(QSqlDatabase &database);

public:
    Order *getOrder(const QSqlQuery &query) const;
    //DAO层，数据转对象

    QList<Order *> select(const int cid) const;
    //通过用户cid，查找全部订单

    QList<Order *> select() const;
    //查找全部订单

    int insert(const Order *order) const;
    //插入order，并返回订单号

    void update(const Order *order) const;
    //更新order
};

#endif // ORDERMAPPER_H
