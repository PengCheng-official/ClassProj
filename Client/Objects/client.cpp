#include "client.h"

Client::Client()
    : _ClientId(0)
    , _ClientBought(0)
{
}

Client::Client(QString clientName, int clientId, QString clientPhone, QString clientEmail,
               QString clientPwd, int clientBought, QString clientAddr, QString clientGender,
               QString clientSalt, QString clientImage)
    : _ClientName(clientName),
      _ClientId(clientId),
      _ClientPhone(clientPhone),
      _ClientEmail(clientEmail),
      _ClientPwd(clientPwd),
      _ClientBought(clientBought),
      _ClientAddr(clientAddr),
      _ClientGender(clientGender),
      _ClientSalt(clientSalt),
      _ClientImage(clientImage)
{
}
