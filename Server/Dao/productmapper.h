#ifndef PRODUCTMAPPER_H
#define PRODUCTMAPPER_H

#include "mapper.h"

class ProductMapper : public Mapper
{
public:
    ProductMapper(QSqlDatabase &database);

public:
    Product *getProduct(const QSqlQuery &query);

    QList<Product *> selectLike(const QString &name);

    QList<Product *> select(const int id);

    QList<Product *> select(const QString &name);

    void insert(Product *product);

    void insert(QList<Product *> proList);

    void update(const int id, const Product *product);

    void delet(const int id);
};

#endif // PRODUCTMAPPER_H
