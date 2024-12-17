#include "ordermapper.h"

#include <QSqlQuery>
#include <QTime>
#include <QReadWriteLock>
#include "../objects/order.h"

OrderMapper::OrderMapper(QSqlDatabase &database)
    : Mapper(database)
{
}

Order *OrderMapper::getOrder(const QSqlQuery &query) const
{
    Order *order = new Order();
    order->setOrderId(query.value(0).toInt());
    order->setClientId(query.value(1).toInt());
    order->setProductNum(query.value(2).toInt());
    order->setTotalPrice(query.value(3).toDouble());
    order->setOrderStatus(query.value(4).toString());
    order->setCreateTime(query.value(5).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    order->setFinishTime(query.value(6).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    return order;
}

QList<Order *> OrderMapper::select(const int cid) const
{
    QReadLocker locker(&dbLock);

    qDebug() << "[database] order select..." << cid;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM `order` WHERE client_id=:cid");
    query.bindValue(":cid", cid);
    query.exec();

    QList<Order *> ret;
    while (query.next()) {
        ret.push_back(getOrder(query));
    }
    query.clear();
    return ret;
}

QList<Order *> OrderMapper::select() const
{
    QReadLocker locker(&dbLock);

    qDebug() << "[database] order select... all";
    QSqlQuery query(db);
    query.prepare("SELECT * FROM `order`");
    query.exec();

    QList<Order *> ret;
    while (query.next()) {
        ret.push_back(getOrder(query));
    }
    query.clear();
    return ret;
}

int OrderMapper::insert(const Order *order) const
{
    QWriteLocker locker(&dbLock);

    qDebug() << "[database] order insert... ";
    QSqlQuery query(db);
    query.prepare("INSERT `order` ( `client_id`, `product_num`, `total_price`, `order_status`, `create_time`, `finish_time`) \
                  VALUES ( :cId, :Num, :Price, :Status, :cTime, :fTime)");
    query.bindValue(":cId", order->getClientId());
    query.bindValue(":Num", order->getProductNum());
    query.bindValue(":Price", order->getTotalPrice());
    query.bindValue(":Status", order->getOrderStatus());
    query.bindValue(":cTime", order->getCreateTime());
    query.bindValue(":fTime", order->getFinishTime());
    query.exec();

    int oid = query.lastInsertId().toInt();
    query.clear();
    return oid;
}

void OrderMapper::update(const Order *order) const
{
    QWriteLocker locker(&dbLock);

    qDebug() << "[database] order update..." << order->getOrderId();
    QSqlQuery query(db);
    query.prepare("UPDATE `order` SET \
                  client_id=:cId, product_num=:Num, total_price=:Price, order_status=:Status, \
                  create_time=:cTime, finish_time=:fTime  \
            WHERE order_id=:oId;");
    query.bindValue(":oId", order->getOrderId());
    query.bindValue(":cId", order->getClientId());
    query.bindValue(":Num", order->getProductNum());
    query.bindValue(":Price", order->getTotalPrice());
    query.bindValue(":Status", order->getOrderStatus());
    query.bindValue(":cTime", order->getCreateTime());
    query.bindValue(":fTime", order->getFinishTime());
    query.exec();
    query.clear();
}
