#ifndef MAPPER_H
#define MAPPER_H


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "../objects/client.h"
#include "../objects/chat.h"
#include "../objects/order.h"
#include "../objects/orderlist.h"
#include "../objects/product.h"
#include "../objects/search.h"

class Mapper
{
public:
    Mapper(QSqlDatabase &database);

    void truncate(QString tableName);
    void Delete(QString tableName);

protected:
    QSqlDatabase db;
};

#endif // MAPPER_H
