#ifndef ORDERLISTMAPPER_H
#define ORDERLISTMAPPER_H


#include "mapper.h"

class OrderList;
class OrderListMapper : public Mapper
{
public:
    OrderListMapper(QSqlDatabase &database);

public:
    OrderList *getOrderList(const QSqlQuery &query) const;
    //DAO层，数据转对象

    QList<OrderList *> select(const int oid) const;
    //通过订单oid，查找订单详情

    void insert(const OrderList *orderList) const;
    //插入orderList

    void insert(const QList<OrderList *> orderLists) const;
    //插入多个orderList
};

#endif // ORDERLISTMAPPER_H
