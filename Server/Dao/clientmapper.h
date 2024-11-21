#ifndef CLIENTMAPPER_H
#define CLIENTMAPPER_H

#include "mapper.h"

class ClientMapper : public Mapper
{
public:
    ClientMapper(QSqlDatabase &database);

public:
    Client* getClient(QSqlQuery &query);
    //DAO层，数据转对象

    QList<Client *> select(QString name);
    //通过用户名查找

    QList<Client *> select(int id);
    //通过id查找

    void insert(Client* client);
    //插入用户
};

#endif // CLIENTMAPPER_H
