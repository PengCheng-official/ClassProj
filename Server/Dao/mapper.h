#ifndef MAPPER_H
#define MAPPER_H


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "../Objects/objects.h"

class Mapper
{
public:
    Mapper(QSqlDatabase &database);

protected:
    QSqlDatabase db;
};

#endif // MAPPER_H
