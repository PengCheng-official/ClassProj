#include "clientmapper.h"

#include <QSqlQuery>
#include <QReadWriteLock>
#include "../objects/client.h"

ClientMapper::ClientMapper(QSqlDatabase &database)
    : Mapper(database)
{
}

Client* ClientMapper::getClient(QSqlQuery &query) const
{
    Client* client = new Client();
    client->setClientId(query.value(0).toInt());
    client->setClientName(query.value(1).toString());
    client->setClientPwd(query.value(2).toString());
    client->setClientSalt(query.value(3).toString());
    client->setClientAddr(query.value(4).toString());
    client->setClientGender(query.value(5).toString());
    client->setClientPhone(query.value(6).toString());
    client->setClientEmail(query.value(7).toString());
    client->setClientImage(query.value(8).toString());
    return client;
}

QList<Client *> ClientMapper::select(const QString &name) const
{
    QReadLocker locker(&dbLock);

    qDebug() << "[database] client select..." << name;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM client WHERE client_name = :name");
    query.bindValue(":name", name);
    query.exec();

    QList<Client *> ret;
    while(query.next()) {
        ret.push_back(getClient(query));
    }
    query.clear();
    return ret;
}

QList<Client *> ClientMapper::select(const int id) const
{
    QReadLocker locker(&dbLock);

    qDebug() << "[database] client select..." << id;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM client WHERE client_id = :id");
    query.bindValue(":id", id);
    query.exec();

    QList<Client *> ret;
    while(query.next()) {
        ret.push_back(getClient(query));
    }
    query.clear();
    return ret;
}

QList<Client *> ClientMapper::select() const
{
    QReadLocker locker(&dbLock);

    qDebug() << "[database] client select... all";
    QSqlQuery query(db);
    query.prepare("SELECT * FROM client");
    query.exec();

    QList<Client *> ret;
    while(query.next()) {
        ret.push_back(getClient(query));
    }
    query.clear();
    return ret;
}

int ClientMapper::insert(const Client *client) const
{
    QWriteLocker locker(&dbLock);

    qDebug() << "[database] client insert ...";
    QSqlQuery query(db);
    query.prepare("INSERT INTO client ( client_name, client_password, client_salt, client_address,\
                  client_phone, client_email, client_image ) VALUES (:name, :pwd, :salt, :addr, :phone, :email, :image)");
    query.bindValue(":name", client->getClientName());
    query.bindValue(":pwd", client->getClientPwd());
    query.bindValue(":salt", client->getClientSalt());
    query.bindValue(":addr", client->getClientAddr());
    query.bindValue(":phone", client->getClientPhone());
    query.bindValue(":email", client->getClientEmail());
    query.bindValue(":image", client->getClientImage());
    query.exec();
    query.clear();

    int cid = query.lastInsertId().toInt();
    query.clear();
    return cid;
}

void ClientMapper::update(const QString &name, const Client *client) const
{
    QWriteLocker locker(&dbLock);

    qDebug() << "[database] client's name update ...";
    QSqlQuery query(db);
    query.prepare("UPDATE client SET \
                  client_address=:Addr, client_gender=:Gender, client_password=:Passwd, \
                  client_salt=:Salt, client_phone=:Phone, client_email=:Email, client_image=:Image  \
            WHERE client_name=:Name;");
    query.bindValue(":Name", name);
    query.bindValue(":Addr", client->getClientAddr());
    query.bindValue(":Gender", client->getClientGender());
    query.bindValue(":Passwd", client->getClientPwd());
    query.bindValue(":Salt", client->getClientSalt());
    query.bindValue(":Phone", client->getClientPhone());
    query.bindValue(":Email", client->getClientEmail());
    query.bindValue(":Image", client->getClientImage());
    query.exec();
    query.clear();
}

void ClientMapper::update(const int id, const Client *client) const
{
    QWriteLocker locker(&dbLock);

    qDebug() << "[database] client's id update ...";
    QSqlQuery query(db);
    query.prepare("UPDATE client SET \
                  client_name=:Name, client_address=:Addr, client_gender=:Gender, client_password=:Passwd, \
                  client_salt=:Salt, client_phone=:Phone, client_email=:Email, client_image=:Image  \
            WHERE client_id=:id;");
    query.bindValue(":id", id);
    query.bindValue(":Name", client->getClientName());
    query.bindValue(":Addr", client->getClientAddr());
    query.bindValue(":Gender", client->getClientGender());
    query.bindValue(":Passwd", client->getClientPwd());
    query.bindValue(":Salt", client->getClientSalt());
    query.bindValue(":Phone", client->getClientPhone());
    query.bindValue(":Email", client->getClientEmail());
    query.bindValue(":Image", client->getClientImage());
    query.exec();
    query.clear();
}

void ClientMapper::delet(const Client *client) const
{
    QWriteLocker locker(&dbLock);

    qDebug() << "[database] client delete... " << client->getClientId();
    QSqlQuery query(db);
    query.prepare("DELETE FROM client WHERE client_id = :id;");
    query.bindValue(":id", client->getClientId());
    query.exec();
    query.clear();
}

