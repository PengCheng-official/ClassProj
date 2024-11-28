#include "client.h"

Client::Client()
{
}

Client::Client(QString clientName, int clientId, QString clientPhone, QString clientEmail,
               QString clientPwd, QString clientAddr, QString clientGender,
               QString clientSalt, QString clientImage)
    : _ClientName(clientName),
      _ClientId(clientId),
      _ClientPhone(clientPhone),
      _ClientEmail(clientEmail),
      _ClientPwd(clientPwd),
      _ClientAddr(clientAddr),
      _ClientGender(clientGender),
      _ClientSalt(clientSalt),
      _ClientImage(clientImage)
{
}
