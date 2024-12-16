#include "orderlistmapper.h"

OrderListMapper::OrderListMapper(QSqlDatabase &database)
    : Mapper(database)
{
}

OrderList *OrderListMapper::getOrderList(const QSqlQuery &query)
{
    OrderList *orderList = new OrderList();
    orderList->setOrderListId(query.value(0).toInt());
    orderList->setOrderId(query.value(1).toInt());
    orderList->setProductId(query.value(2).toInt());
    orderList->setProductNum(query.value(3).toInt());
    orderList->setProductPrice(query.value(4).toDouble());
    return orderList;
}

void OrderListMapper::insert(const OrderList *orderList)
{
    qDebug() << "[database] orderList insert...";
    QSqlQuery query(db);
    query.prepare("INSERT orderlist ( `order_id`, `product_id`, `product_num`, `product_price` ) \
                  VALUES ( :oId, :pId, :Num, :Price)");
    query.bindValue(":oId", orderList->getOrderId());
    query.bindValue(":pId", orderList->getProductId());
    query.bindValue(":Num", orderList->getProductNum());
    query.bindValue(":Price", orderList->getProductPrice());
    query.exec();
    query.clear();
}

void OrderListMapper::insert(const QList<OrderList *> orderLists)
{
    qDebug() << "[database] orderList insert list...";
    for (auto orderList : orderLists)
    {
        insert(orderList);
    }
}
