#include "shoppingmapper.h"

#include <QSqlQuery>
#include <QReadWriteLock>
#include "../objects/shopping.h"


ShoppingMapper::ShoppingMapper(QSqlDatabase &database)
    : Mapper(database)
{
}

Shopping *ShoppingMapper::getShopping(const QSqlQuery &query)
{
    Shopping *shopping = new Shopping();
    shopping->setShoppingId(query.value(0).toInt());
    shopping->setClientId(query.value(1).toInt());
    shopping->setProductId(query.value(2).toInt());
    shopping->setShoppingNum(query.value(3).toInt());
    shopping->setShoppingPrice(query.value(4).toDouble());
    return shopping;
}

QList<Shopping *> ShoppingMapper::select(const int cid)
{
    QReadLocker locker(&dbLock);

    qDebug() << "[database] shopping select... " << cid;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM shopping WHERE client_id = :id;");
    query.bindValue(":id", cid);
    query.exec();

    QList<Shopping *> ret;
    while(query.next()) {
        ret.push_back(getShopping(query));
    }
    query.clear();
    return ret;
}

int ShoppingMapper::select(const Shopping *shopping)
{
    QReadLocker locker(&dbLock);

    qDebug() << "[database] shopping select... " << shopping->getClientId() << shopping->getProductId();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM shopping WHERE client_id = :cid AND product_id = :pid;");
    query.bindValue(":cid", shopping->getClientId());
    query.bindValue(":pid", shopping->getProductId());
    query.exec();

    int ret = 0;
    if (query.next())
        ret = getShopping(query)->getShoppingNum();
    query.clear();
    return ret;
}

void ShoppingMapper::insert(const QList<Shopping *> shopList)
{
    qDebug() << "[database] shopping insert shopList...";
    for (auto shopping : shopList)
    {
        insert(shopping);
    }
}

void ShoppingMapper::update(const Shopping *shopping)
{
    QWriteLocker locker(&dbLock);

    qDebug() << "[database] shopping update...";
    QSqlQuery query(db);
    query.prepare("UPDATE shopping SET \
                  shopping_num = :Num, shopping_price = :Price \
                  WHERE client_id = :cid AND product_id = :pid;");
    query.bindValue(":cid", shopping->getClientId());
    query.bindValue(":pid", shopping->getProductId());
    query.bindValue(":Num", shopping->getShoppingNum());
    query.bindValue(":Price", shopping->getShoppingPrice());
    query.exec();
    query.clear();
}

void ShoppingMapper::delet(const Shopping *shopping)
{
    QWriteLocker locker(&dbLock);

    qDebug() << "[database] shopping delete...";
    QSqlQuery query(db);
    query.prepare("DELETE FROM shopping WHERE client_id=:cid AND product_id=:pid;");
    query.bindValue(":cid", shopping->getClientId());
    query.bindValue(":pid", shopping->getProductId());
    query.exec();
    query.clear();
}

void ShoppingMapper::delet(const QList<Shopping *> shoppings)
{
    qDebug() << "[database] shopping delete list...";
    for (auto shopping : shoppings)
    {
        delet(shopping);
    }
}

void ShoppingMapper::insert(const Shopping *shopping)
{
    QWriteLocker locker(&dbLock);

    qDebug() << "[database] shopping insert shopping...";
    QSqlQuery query(db);
    query.prepare("INSERT INTO shopping ( client_id, product_id, shopping_num, shopping_price)\
                VALUES (:CId, :PId, :Num, :Price);");
    query.bindValue(":CId", shopping->getClientId());
    query.bindValue(":PId", shopping->getProductId());
    query.bindValue(":Num", shopping->getShoppingNum());
    query.bindValue(":Price", shopping->getShoppingPrice());
    query.exec();
    query.clear();
}
