#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <ElaScrollPage.h>
#include <ElaScrollPageArea.h>
#include "objects/objects.h"
#include "ElaMenu.h"
#include "ElaText.h"
#include "ElaWindow.h"
#include <QHBoxLayout>
#include <QHeaderView>
#include <QVBoxLayout>

#include <QMouseEvent>
#include "ElaToggleSwitch.h"
#include "ElaPushButton.h"
#include "chatroom.h"

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
    virtual void mouseReleaseEvent(QMouseEvent* event);

signals:
    void lockBtn();
    void unlockBtn();
    void sigReceiveMessage(Chat* chatMsg);
    void sigSendToClient(Client* client, QByteArray array);

};

#endif // CHATPAGE_H
