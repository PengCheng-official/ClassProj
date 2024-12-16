#ifndef CHATROOM_H
#define CHATROOM_H

// 联系客服界面
#include "ElaWidget.h"
#include "chatmessage/qnchatmessage.h"

class TcpSocket;
class QNChatMessage;
class QListWidgetItem;
class Client;
class Chat;
class QGridLayout;
class ElaListView;
class ElaContentDialog;

namespace Ui {
class ChatRoom;
}

class ChatRoom : public ElaWidget
{
    Q_OBJECT

public:
    explicit ChatRoom(QWidget *parent = nullptr);
    ~ChatRoom();

    void initHistory(QList<Chat *> &chatList);
    void initClient(Client* cClient);
    void receiveMessage(Chat* chatMsg);

private:
    void dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type);
    void dealMessageTime(QString curMsgTime);
    void resizeEvent(QResizeEvent *event);

private:
    Ui::ChatRoom *ui;
    ElaListView *listView;
    QGridLayout *mainLayout;
    Client* client;
    bool unKnown;

private slots:
    void on_returnBtn_clicked();

    void on_sendBtn_clicked();

signals:
    void sigSendToServer(QByteArray array);
    void sigReturnToLogIn();

};

#endif // CHATROOM_H
