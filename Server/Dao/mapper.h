#ifndef MAPPER_H
#define MAPPER_H


#include <QSqlDatabase>
#include <QString>
#include "../allmain.h"

class Mapper
{
public:
    Mapper(QSqlDatabase &database);

    void truncate(QString tableName);
    void Delete(QString tableName);

protected:
    QSqlDatabase& db;
};

#endif // MAPPER_H
