#include "shoppingmapper.h"


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
    qDebug() << "[database] shopping select... " << cid;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM shopping WHERE client_id = :id;");
    query.bindValue(":id", cid);
    query.exec();

    QList<Shopping *> ret;
    while(query.next()) {
        ret.push_back(getShopping(query));
    }
    query.finish();
    return ret;
}

int ShoppingMapper::select(const Shopping *shopping)
{
    qDebug() << "[database] shopping select... " << shopping->getClientId() << shopping->getProductId();
    QSqlQuery query(db);
    query.prepare("SELECT * FROM shopping WHERE client_id = :cid AND product_id = :pid;");
    query.bindValue(":cid", shopping->getClientId());
    query.bindValue(":pid", shopping->getProductId());
    query.exec();

    int ret = 0;
    if (query.next())
        ret = getShopping(query)->getShoppingNum();
    query.finish();
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
    query.finish();
}

void ShoppingMapper::delet(const Shopping *shopping)
{
    qDebug() << "[database] shopping delete...";
    QSqlQuery query(db);
    query.prepare("DELETE FROM shopping \
                  WHERE client_id = :cid AND product_id = :pid;");
    query.bindValue(":cid", shopping->getClientId());
    query.bindValue(":pid", shopping->getProductId());
    query.exec();
    query.finish();
}

void ShoppingMapper::insert(const Shopping *shopping)
{
    qDebug() << "[database] shopping insert shopping...";
    QSqlQuery query(db);
    query.prepare("INSERT INTO shopping ( client_id, product_id, shopping_num, shopping_price)\
                VALUES (:CId, :PId, :Num, :Price);");
    query.bindValue(":CId", shopping->getClientId());
    query.bindValue(":PId", shopping->getProductId());
    query.bindValue(":Num", shopping->getShoppingNum());
    query.bindValue(":Price", shopping->getShoppingPrice());
    query.exec();
    query.finish();
}
