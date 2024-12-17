#include "mapper.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QReadWriteLock>

#include "../objects/client.h"
#include "../objects/chat.h"
#include "../objects/order.h"
#include "../objects/orderlist.h"
#include "../objects/product.h"
#include "../objects/search.h"
#include "../objects/shopping.h"

Mapper::Mapper(QSqlDatabase &database)
    : db(database)
{
}

void Mapper::truncate(const QString &tableName) const
{
    QWriteLocker locker(&dbLock);

    QSqlQuery query(db);
    query.prepare("TRUNCATE TABLE :name");
    query.bindValue(":name", tableName);
    query.exec();
    query.clear();
}

void Mapper::Delete(const QString &tableName) const
{
    QWriteLocker locker(&dbLock);

    QSqlQuery query(db);
    query.prepare("DELETE FROM :name");
    query.bindValue(":name", tableName);
    query.exec();
    query.clear();
}
