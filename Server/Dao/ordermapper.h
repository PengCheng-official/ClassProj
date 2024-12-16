#ifndef ORDERMAPPER_H
#define ORDERMAPPER_H


#include "mapper.h"

class OrderMapper : public Mapper
{
public:
    OrderMapper(QSqlDatabase &database);

public:
    Order *getOrder(const QSqlQuery &query);

    int insert(const Order *order);
    // 返回订单号

    void update(const Order *order);
};

#endif // ORDERMAPPER_H
