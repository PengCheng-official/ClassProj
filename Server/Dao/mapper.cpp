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

void Mapper::truncate(QString tableName)
{
    QWriteLocker locker(&dbLock);

    // truncate 速度快，无法回滚
    QSqlQuery query(db);
    query.prepare("TRUNCATE TABLE :name");
    query.bindValue(":name", tableName);
    query.exec();
    query.clear();
}

void Mapper::Delete(QString tableName)
{
    QWriteLocker locker(&dbLock);

    // delete 速度慢，但是可以回滚
    QSqlQuery query(db);
    query.prepare("DELETE FROM :name");
    query.bindValue(":name", tableName);
    query.exec();
    query.clear();
}
