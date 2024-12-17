#ifndef ORDERLISTMAPPER_H
#define ORDERLISTMAPPER_H


#include "mapper.h"

class OrderList;
class OrderListMapper : public Mapper
{
public:
    OrderListMapper(QSqlDatabase &database);

public:
    OrderList *getOrderList(const QSqlQuery &query);

    QList<OrderList *> select(int oid);
    // 返回订单oid的订单详情

    void insert(const OrderList *orderList);
    // 插入orderList

    void insert(const QList<OrderList *> orderLists);
};

#endif // ORDERLISTMAPPER_H
