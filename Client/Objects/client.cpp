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

void Client::setClientName(const QString& clientName)
{
    this->clientName = clientName;
}

void Client::setClientId(int clientId)
{
    this->clientId = clientId;
}

void Client::setClientPhone(const QString& clientPhone)
{
    this->clientPhone = clientPhone;
}

void Client::setClientEmail(const QString& clientEmail)
{
    this->clientEmail = clientEmail;
}

void Client::setClientPwd(const QString& clientPwd)
{
    this->clientPwd = clientPwd;
}

void Client::setClientSalt(const QString& clientSalt)
{
    this->clientSalt = clientSalt;
}

void Client::setClientAddr(const QString& clientAddr)
{
    this->clientAddr = clientAddr;
}

void Client::setClientBought(int clientBought)
{
    this->clientBought = clientBought;
}

void Client::setClientGender(const QString& clientGender)
{
    this->clientGender = clientGender;
}

QString Client::getClientImage() const
{
    return clientImage;
}

void Client::setClientImage(const QString &value)
{
    clientImage = value;
}
