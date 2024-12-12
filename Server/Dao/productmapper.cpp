#include "productmapper.h"

ProductMapper::ProductMapper(QSqlDatabase &database)
    : Mapper(database)
{
}

Product *ProductMapper::getProduct(const QSqlQuery &query)
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

QList<Product *> ProductMapper::selectLike(const QString &name)
{
    qDebug() << "[database] product select... " << name;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM product WHERE product_name LIKE :name");
    query.bindValue(":name", '%' + name + '%');
    query.exec();

    QList<Product *> ret;
    while(query.next()) {
        ret.push_back(getProduct(query));
    }
    query.finish();
    return ret;
}

QList<Product *> ProductMapper::selectRand()
{
    QList<Product *> ret;
    qDebug() << "[database] product select rand... ";
    QSqlQuery query(db);
    do {
        query.prepare("SELECT DISTINCT * FROM product ORDER BY RAND() LIMIT 2;");
        query.exec();

        while(query.next()) {
            ret.push_back(getProduct(query));
        }
    }
    while (ret.size() != 2);
    query.finish();
    return ret;
}

QList<Product *> ProductMapper::select(const int id)
{
    qDebug() << "[database] product select... " << id;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM product WHERE product_id = :id");
    query.bindValue(":id", id);
    query.exec();

    QList<Product *> ret;
    while(query.next()) {
        ret.push_back(getProduct(query));
    }
    query.finish();
    return ret;
}

QList<Product *> ProductMapper::select(const QString &name)
{
    qDebug() << "[database] product select... " << name;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM product WHERE product_name = :name");
    query.bindValue(":name", name);
    query.exec();

    QList<Product *> ret;
    while(query.next()) {
        ret.push_back(getProduct(query));
    }
    query.finish();
    return ret;
}

void ProductMapper::insert(Product *product)
{
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
    query.finish();
}

void ProductMapper::insert(QList<Product *> proList)
{
    qDebug() << "[database] chat insert proList ...";
    for (auto pro : proList)
    {
        insert(pro);
    }
}

void ProductMapper::update(const int id, const Product *product)
{
    qDebug() << "[database] product update... " << id;
    QSqlQuery query(db);
    query.prepare("UPDATE product SET \
                  product_name=:Name, product_price=:Price, product_num=:Num, product_sales=:Sales, \
                  product_about=:About, product_strategy=:Strategy, product_discount1=:Num1, product_discount2=:Num2, product_image=:Image  \
            WHERE product_id=:id;");
    query.bindValue(":id", id);
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
    query.finish();
}

void ProductMapper::delet(const int id)
{
    qDebug() << "[database] product delete... ";
    QSqlQuery query(db);
    query.prepare("DELETE FROM product WHERE product_id = :id;");
    query.bindValue(":id", id);
    query.exec();
    query.finish();
}
