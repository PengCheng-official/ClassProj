#ifndef PRODUCTMAPPER_H
#define PRODUCTMAPPER_H


#include "mapper.h"

class Product;
class OrderList;
class ProductMapper : public Mapper
{
public:
    ProductMapper(QSqlDatabase &database);

public:
    Product *getProduct(const QSqlQuery &query) const;
    //DAO层，数据转对象

    QList<Product *> selectLike(const QString &name) const;
    //通过商品名，模糊查找

    QList<Product *> selectRand() const;
    //随机推送查找

    QList<Product *> select(const int pid) const;
    //通过pid，查找商品

    QList<Product *> select(const QString &name) const;
    //通过商品名，查找商品

    void insert(const Product *product) const;
    //插入product

    void insert(const QList<Product *> proList) const;
    //插入多个product

    void update(const Product *product) const;
    //更新product

    void delet(const int pid) const;
    //通过pid，删除商品
};

#endif // PRODUCTMAPPER_H
