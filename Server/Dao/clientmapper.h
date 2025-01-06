#ifndef CLIENTMAPPER_H
#define CLIENTMAPPER_H


#include "mapper.h"

class Client;
class ClientMapper : public Mapper
{
public:
    ClientMapper(QSqlDatabase &database);

public:
    Client *getClient(QSqlQuery &query) const;
    //DAO层，数据转对象

    QList<Client *> select(const QString &name) const;
    //通过用户名查找

    QList<Client *> select(const int id) const;
    //通过id查找

    QList<Client *> select() const;
    //查找全部

    int insert(const Client *client) const;
    //插入用户

    void update(const QString &name,const Client *client) const;
    //根据用户名，修改用户信息

    void update(const int id,const Client *client) const;
    //根据id，修改用户信息

    void delet(const Client *client) const;
    //注销用户
};

#endif // CLIENTMAPPER_H
