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
    product->setStrategy(query.value(6).toInt(), query.value(7).toInt(), query.value(8).toInt());
    product->setProductImage(query.value(9).toString());
    return product;
}

QList<Product *> ProductMapper::select(const QString &name)
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
    query.bindValue(":Strategy", product->getStrategy() + '0');
    query.bindValue(":Num1", product->getProductName());
    query.bindValue(":Num2", product->getProductName());
    query.bindValue(":Image", product->getProductName());
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
