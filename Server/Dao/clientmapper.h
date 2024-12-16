#ifndef CLIENTMAPPER_H
#define CLIENTMAPPER_H

#include "mapper.h"

class Client;
class ClientMapper : public Mapper
{
public:
    ClientMapper(QSqlDatabase &database);

public:
    Client* getClient(QSqlQuery &query);
    //DAO层，数据转对象

    QList<Client *> select(const QString &name);
    //通过用户名查找

    QList<Client *> select(int id);
    //通过id查找

    void insert(Client *client);
    //插入用户

    void update(const QString &name, Client *client);
    //根据用户名，修改用户信息

    void update(const int id, Client *client);
    //根据id，修改用户信息
};

#endif // CLIENTMAPPER_H
