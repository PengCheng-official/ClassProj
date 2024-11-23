#ifndef CLIENT_H
#define CLIENT_H


#include <QString>
#include <QDateTime>
#include "objects.h"

class Client
{
PROPERTY_CREATE_H(QString, ClientName);
PROPERTY_CREATE_H(int, ClientId);
PROPERTY_CREATE_H(QString, ClientPhone);
PROPERTY_CREATE_H(QString, ClientEmail);
PROPERTY_CREATE_H(QString, ClientPwd);
PROPERTY_CREATE_H(int, ClientBought);
PROPERTY_CREATE_H(QString, ClientAddr);
PROPERTY_CREATE_H(QString, ClientGender);
PROPERTY_CREATE_H(QString, ClientSalt);
PROPERTY_CREATE_H(QString, ClientImage);

public:
    Client();
    Client(
            QString clientName,
            int clientId,
            QString clientPhone,
            QString clientEmail,
            QString clientPwd,
            int clientBought,
            QString clientAddr,
            QString clientGender,
            QString clientSalt,
            QString clientImage
            );
};

#endif // CLIENT_H
