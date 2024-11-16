#include "chat.h"

Chat::Chat()
{

}

Chat::Chat(int cClientId, QString cChatText, int cChatIsserver, QString cChatTime)
    : clientId(cClientId)
    , chatText(cChatText)
    , chatIsserver(cChatIsserver)
    , chatTime(cChatTime)
{
}

void Chat::setClientId(int id)
{
    clientId = id;
}

void Chat::setChatText(QString text)
{
    chatText = text;
}

void Chat::setChatIsserver(int isserver)
{
    chatIsserver = isserver;
}

void Chat::setChatTime(QString time)
{
    chatTime = time;
}

int Chat::getClientId() const
{
    return clientId;
}

QString Chat::getChatText() const
{
    return chatText;
}

int Chat::getChatIsserver() const
{
    return chatIsserver;
}

QString Chat::getChatTime() const
{
    return chatTime;
}
