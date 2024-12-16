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

    void insert(const OrderList *orderList);
    void insert(const QList<OrderList *> orderLists);
};

#endif // ORDERLISTMAPPER_H
