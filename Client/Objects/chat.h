#ifndef CHAT_H
#define CHAT_H


#include <QString>
#include "objects.h"

class Chat
{
PROPERTY_CREATE_H(int, ChatId);
PROPERTY_CREATE_H(int, ClientId);
PROPERTY_CREATE_H(QString, ChatText);
PROPERTY_CREATE_H(int, ChatIsserver);
PROPERTY_CREATE_H(QString, ChatTime);   //toString("yyyy-MM-dd hh:mm:ss")

public:
    Chat();
    Chat(int cClientId, QString cChatText, int cChatIsserver, QString cChatTime);
};

#endif // CHAT_H
