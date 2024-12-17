#ifndef MAPPER_H
#define MAPPER_H


#include <QSqlDatabase>
#include <QString>
#include "../allmain.h"

class Mapper
{
public:
    Mapper(QSqlDatabase &database);

    void truncate(const QString &tableName) const;
    // truncate 速度快，无法回滚

    void Delete(const QString &tableName) const;
    // delete 速度慢，但是可以回滚

protected:
    QSqlDatabase& db;
};

#endif // MAPPER_H
