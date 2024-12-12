#ifndef PRODUCTMAPPER_H
#define PRODUCTMAPPER_H

#include "mapper.h"

class ProductMapper : public Mapper
{
public:
    ProductMapper(QSqlDatabase &database);

public:
    Product *getProduct(const QSqlQuery &query);

    QList<Product *> select(const QString &name);

    void insert(Product *product);

    void insert(QList<Product *> proList);
};

#endif // PRODUCTMAPPER_H
