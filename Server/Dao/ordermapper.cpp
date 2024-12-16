#include "ordermapper.h"

OrderMapper::OrderMapper(QSqlDatabase &database)
    : Mapper(database)
{
}

Order *OrderMapper::getOrder(const QSqlQuery &query)
{
    Order *order = new Order();
    order->setOrderId(query.value(0).toInt());
    order->setClientId(query.value(1).toInt());
    order->setTotalPrice(query.value(2).toDouble());
    order->setOrderStatus(query.value(3).toString());
    order->setCreateTime(query.value(4).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    order->setFinishTime(query.value(5).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    return order;
}

int OrderMapper::insert(const Order *order)
{
    qDebug() << "[database] order insert... ";
    QSqlQuery query(db);
    query.prepare("INSERT `order` ( `client_id`, `total_price`, `order_status`, `create_time`, `finish_time`) \
                  VALUES ( :cId, :Price, :Status, :cTime, :fTime)");
    query.bindValue(":cId", order->getClientId());
    query.bindValue(":Price", order->getTotalPrice());
    query.bindValue(":Status", order->getOrderStatus());
    query.bindValue(":cTime", order->getCreateTime());
    query.bindValue(":fTime", order->getFinishTime());
    query.exec();

    int oid = query.lastInsertId().toInt();
    query.clear();
    return oid;
}

void OrderMapper::update(const Order *order)
{
    qDebug() << "[database] order update..." << order->getOrderId();
    QSqlQuery query(db);
    query.prepare("UPDATE `order` SET \
                  client_id=:cId, total_price=:Price, order_status=:Status, \
                  create_time=:cTime, finish_time=:fTime  \
            WHERE order_id=:oId;");
    query.bindValue(":oId", order->getOrderId());
    query.bindValue(":cId", order->getClientId());
    query.bindValue(":Price", order->getTotalPrice());
    query.bindValue(":Status", order->getOrderStatus());
    query.bindValue(":cTime", order->getCreateTime());
    query.bindValue(":fTime", order->getFinishTime());
    query.exec();
    query.clear();
}
