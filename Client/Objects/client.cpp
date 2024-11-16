#include "objects.h"


Client::Client():clientId(0),clientBought(0)
{

}

Client::Client(QString clientName, int clientId, QString clientPhone, QString clientEmail, QString clientPwd, QString clientSalt, int clientBought, QString clientAddr, QString clientGender)
{
    this->clientName = clientName;
    this->clientId = clientId;
    this->clientPhone = clientPhone;
    this->clientEmail = clientEmail;
    this->clientPwd = clientPwd;
    this->clientSalt = clientSalt;
    this->clientBought = clientBought;
    this->clientGender = clientGender;
    this->clientAddr = clientAddr;
}

QString Client::getClientName() const
{
    return clientName;
}

QString Client::getClientGender() const
{
    return clientGender;
}

QString Client::getClientAddr() const
{
    return clientAddr;
}

int Client::getClientId() const
{
    return clientId;
}

QString Client::getClientPhone() const
{
    return clientPhone;
}

QString Client::getClientEmail() const
{
    return clientEmail;
}

QString Client::getClientPwd() const
{
    return clientPwd;
}

QString Client::getClientSalt() const
{
    return clientSalt;
}

int Client::getClientBought() const
{
    return clientBought;
}

void Client::setClientName(QString clientName)
{
    this->clientName = clientName;
}

void Client::setClientId(int clientId)
{
    this->clientId = clientId;
}

void Client::setClientPhone(QString clientPhone)
{
    this->clientPhone = clientPhone;
}

void Client::setClientEmail(QString clientEmail)
{
    this->clientEmail = clientEmail;
}

void Client::setClientPwd(QString clientPwd)
{
    this->clientPwd = clientPwd;
}

void Client::setClientSalt(QString clientSalt)
{
    this->clientSalt = clientSalt;
}

void Client::setClientAddr(QString clientAddr)
{
    this->clientAddr = clientAddr;
}

void Client::setClientBought(int clientBought)
{
    this->clientBought = clientBought;
}

void Client::setClientGender(QString clientGender)
{
    this->clientGender = clientGender;
}
