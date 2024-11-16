#include "clientmapper.h"

ClientMapper::ClientMapper(QSqlDatabase &database)
    : Mapper(database)
{
}

Client* ClientMapper::getClient(QSqlQuery &query)
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
    client->setClientBought(query.value(8).toInt());
    return client;
}

QList<Client *> ClientMapper::select(QString name)
{
    qDebug() << "[database] client select...";
    QSqlQuery query(db);
    query.prepare("SELECT * FROM client WHERE client_name = :name");
    query.bindValue(":name", name);
    query.exec();

    QList<Client *> ret;
    while(query.next()) {
        ret.push_back(getClient(query));
    }
    query.finish();
    return ret;
}

QList<Client *> ClientMapper::select(int id)
{
    qDebug() << "[database] client select...";
    QSqlQuery query(db);
    query.prepare("SELECT * FROM client WHERE client_id = :id");
    query.bindValue(":id", id);
    query.exec();

    QList<Client *> ret;
    while(query.next()) {
        ret.push_back(getClient(query));
    }
    query.finish();
    return ret;
}

void ClientMapper::insert(Client *client)
{
    qDebug() << "[database] client insert ...";
    QSqlQuery query(db);
    query.prepare("INSERT INTO client ( client_name, client_password, client_salt, client_address,\
                  client_phone, client_email ) VALUES (:name, :pwd, :salt, :addr, :phone, :email)");
    query.bindValue(":name", client->getClientName());
    query.bindValue(":pwd", client->getClientPwd());
    query.bindValue(":salt", client->getClientSalt());
    query.bindValue(":addr", client->getClientAddr());
    query.bindValue(":phone", client->getClientPhone());
    query.bindValue(":email", client->getClientEmail());
    query.exec();
    query.finish();
}

