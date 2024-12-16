#include "chat.h"

Chat::Chat()
{
}

Chat::Chat(int cClientId, QString cChatText, int cChatIsserver, QString cChatTime)
    : _ClientId(cClientId)
    , _ChatText(cChatText)
    , _ChatIsserver(cChatIsserver)
    , _ChatTime(cChatTime)
{
}
