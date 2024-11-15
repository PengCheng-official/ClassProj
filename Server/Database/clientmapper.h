#ifndef CLIENTMAPPER_H
#define CLIENTMAPPER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "objects.h"

class ClientMapper
{
public:
    ClientMapper(QSqlDatabase &database);

public:
    Client* getClient(QSqlQuery &query);

    QList<Client *> select(QString name);
    //通过用户名查找

    QList<Client *> select(int id);
    //通过id查找

    void insert(Client* client);

private:
    QSqlDatabase &db;
};

#endif // CLIENTMAPPER_H
