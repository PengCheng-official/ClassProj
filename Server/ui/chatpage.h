#ifndef CHATPAGE_H
#define CHATPAGE_H


#include "ElaScrollPage.h"

class Client;
class ElaToggleSwitch;
class ChatRoom;
class Chat;
class ChatPage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit ChatPage(QWidget* parent = nullptr);
    ~ChatPage();
    static int restMsg;

    void setClientList(QList<Client *> &cClientList);

private:
    QList<Client *> clientList;
    ElaToggleSwitch* _toggleSwitch{nullptr};
    QWidget* centralWidget;
    ChatRoom *chatRoom;

protected:
    void mouseReleaseEvent(QMouseEvent* event) override;

signals:
    void sigLockBtn();
    void sigUnlockBtn();
    void sigReceiveMessage(Chat* chatMsg);
    void sigSendToClient(Client* client, QByteArray array);
};

#endif // CHATPAGE_H
