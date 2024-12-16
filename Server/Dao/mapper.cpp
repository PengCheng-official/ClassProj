#include "mapper.h"

Mapper::Mapper(QSqlDatabase &database)
    : db(database)
{
}

void Mapper::truncate(QString tableName)
{
    // truncate 速度快，无法回滚
    QSqlQuery query(db);
    query.prepare("TRUNCATE TABLE :name");
    query.bindValue(":name", tableName);
    query.exec();
    query.clear();
}

void Mapper::Delete(QString tableName)
{
    // delete 速度慢，但是可以回滚
    QSqlQuery query(db);
    query.prepare("DELETE FROM :name");
    query.bindValue(":name", tableName);
    query.exec();
    query.clear();
}
