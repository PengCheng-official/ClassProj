#ifndef CHAT_H
#define CHAT_H


#include <QString>
#include <QTime>
#include <QDateTime>

class Chat
{
private:
    int clientId;
    QString chatText;
    int chatIsserver;
    QString chatTime;   //toString("yyyy-MM-dd hh:mm:ss")

public:
    Chat();
    Chat(int cClientId, QString cChatText, int cChatIsserver, QString cChatTime);

    void setClientId(int id);
    void setChatText(const QString& text);
    void setChatIsserver(int isserver);
    void setChatTime(const QString& time);

    int getClientId() const;
    QString getChatText() const;
    int getChatIsserver() const;
    QString getChatTime() const;
};

#endif // CHAT_H
