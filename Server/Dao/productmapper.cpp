#include "productmapper.h"

#include <QSqlQuery>
#include <QReadWriteLock>
#include "../objects/product.h"
#include "../objects/orderlist.h"

ProductMapper::ProductMapper(QSqlDatabase &database)
    : Mapper(database)
{
}

Product *ProductMapper::getProduct(const QSqlQuery &query) const
{
    Product *product = new Product();
    product->setProductId(query.value(0).toInt());
    product->setProductName(query.value(1).toString());
    product->setProductPrice(query.value(2).toDouble());
    product->setProductNum(query.value(3).toInt());
    product->setProductSales(query.value(4).toInt());
    product->setProductAbout(query.value(5).toString());
    product->setStrategy(query.value(6).toInt(), query.value(7).toDouble(), query.value(8).toDouble());
    product->setProductImage(query.value(9).toString());
    return product;
}

QList<Product *> ProductMapper::selectLike(const QString &name) const
{
    QReadLocker locker(&dbLock);

    qDebug() << "[database] product select... " << name;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM product WHERE product_name LIKE :name OR product_about LIKE :name");
    query.bindValue(":name", '%' + name + '%');
    query.exec();

    QList<Product *> ret;
    while(query.next()) {
        ret.push_back(getProduct(query));
    }
    query.clear();
    return ret;
}

QList<Product *> ProductMapper::selectRand() const
{
    QReadLocker locker(&dbLock);

    QList<Product *> ret;
    qDebug() << "[database] product select rand... ";
    QSqlQuery query(db);
    do {
        // 限制随机选择不会选择到 id=0 的商品
        query.prepare("SELECT DISTINCT * FROM product WHERE product_id != 0 ORDER BY RAND() LIMIT 2;");
        query.exec();

        while(query.next()) {
            ret.push_back(getProduct(query));
        }
    }
    while (ret.size() != 2);
    query.clear();
    return ret;
}

QList<Product *> ProductMapper::select(const int pid) const
{
    QReadLocker locker(&dbLock);

    qDebug() << "[database] product select... " << pid;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM product WHERE product_id = :id");
    query.bindValue(":id", pid);
    query.exec();

    QList<Product *> ret;
    while(query.next()) {
        ret.push_back(getProduct(query));
    }
    query.clear();
    return ret;
}

QList<Product *> ProductMapper::select(const QString &name) const
{
    QReadLocker locker(&dbLock);

    qDebug() << "[database] product select... " << name;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM product WHERE product_name = :name");
    query.bindValue(":name", name);
    query.exec();

    QList<Product *> ret;
    while(query.next()) {
        ret.push_back(getProduct(query));
    }
    query.clear();
    return ret;
}

void ProductMapper::insert(const Product *product) const
{
    QWriteLocker locker(&dbLock);

    qDebug() << "[database] product insert pro ... " << product->getProductName();
    QSqlQuery query(db);
    query.prepare("INSERT INTO product ( product_name, product_price, product_num, product_sales, \
                     product_about, product_strategy, product_discount1, product_discount2, product_image ) \
                  VALUES (:Name, :Price, :Num, :Sales, :About, :Strategy, :Num1, :Num2, :Image);");
    query.bindValue(":Name", product->getProductName());
    query.bindValue(":Price", product->getProductPrice());
    query.bindValue(":Num", product->getProductNum());
    query.bindValue(":Sales", product->getProductSales());
    query.bindValue(":About", product->getProductAbout());
    query.bindValue(":Strategy", QString::number(product->getStrategy()));
    query.bindValue(":Num1", product->getStrategy1());
    query.bindValue(":Num2", product->getStrategy2());
    query.bindValue(":Image", product->getProductImage());
    query.exec();
    query.clear();
}

void ProductMapper::insert(const QList<Product *> proList) const
{
    qDebug() << "[database] product insert proList ...";
    for (auto pro : proList)
    {
        insert(pro);
    }
}

void ProductMapper::update(const Product *product) const
{
    QWriteLocker locker(&dbLock);

    qDebug() << "[database] product update... " << product->getProductId();
    QSqlQuery query(db);
    query.prepare("UPDATE product SET \
                  product_name=:Name, product_price=:Price, product_num=:Num, product_sales=:Sales, \
                  product_about=:About, product_strategy=:Strategy, product_discount1=:Num1, product_discount2=:Num2, product_image=:Image  \
            WHERE product_id=:id;");
    query.bindValue(":id", product->getProductId());
    query.bindValue(":Name", product->getProductName());
    query.bindValue(":Price", product->getProductPrice());
    query.bindValue(":Num", product->getProductNum());
    query.bindValue(":Sales", product->getProductSales());
    query.bindValue(":About", product->getProductAbout());
    query.bindValue(":Strategy", QString::number(product->getStrategy()));
    query.bindValue(":Num1", product->getStrategy1());
    query.bindValue(":Num2", product->getStrategy2());
    query.bindValue(":Image", product->getProductImage());
    query.exec();
    query.clear();
}

void ProductMapper::delet(const int pid) const
{
    QWriteLocker locker(&dbLock);

    qDebug() << "[database] product delete... ";
    QSqlQuery query(db);
    query.prepare("DELETE FROM product WHERE product_id = :id;");
    query.bindValue(":id", pid);
    query.exec();
    query.clear();
}
