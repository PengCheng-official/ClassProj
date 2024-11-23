#ifndef CHATROOM_H
#define CHATROOM_H

// 联系客服界面
#include <iostream>
#include <QWidget>
#include <QObject>
#include <QMouseEvent>
#include <QTcpSocket>
#include <QHostAddress>
#include "objects/client.h"
#include "objects/chat.h"
#include "objects/order.h"
#include "objects/orderlist.h"
#include "objects/product.h"
#include "objects/search.h"
#include "objecttojson.h"
#include "statement.h"
#include <QListWidgetItem>
#include "chatmessage/qnchatmessage.h"

#include "ElaWidget.h"
#include "Def.h"
#include "stdafx.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "ElaPushButton.h"
#include "ElaPlainTextEdit.h"
#include "ElaListView.h"
#include "ElaTheme.h"

class TcpSocket;

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
//    ElaWidget *editContainer;
//    ElaPlainTextEdit *textEdit;
//    ElaPushButton *sendBtn;
//    ElaPushButton *returnBtn;
    QGridLayout *mainLayout;
//    QGridLayout *editLayout;
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
