#ifndef CHATROOM_H
#define CHATROOM_H

// 联系客服界面
#include <iostream>
#include <QWidget>
#include <QObject>
#include <QMouseEvent>
#include <QTcpSocket>
#include <QHostAddress>
#include "objects.h"
#include "objecttojson.h"
#include "statement.h"

#include "ElaWidget.h"
#include "Def.h"
#include "stdafx.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "ElaPushButton.h"
#include "ElaPlainTextEdit.h"
#include "ElaListView.h"

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

private:
    Ui::ChatRoom *ui;
//    ElaListView *listView;
//    ElaWidget *editContainer;
//    ElaPlainTextEdit *textEdit;
//    ElaPushButton *sendBtn;
//    ElaPushButton *returnBtn;
//    QGridLayout *mainLayout;
//    QGridLayout *editLayout;


private:
    void receiveMessage();

    void dealMessage(QByteArray message);

    void dealMessageTime(QString curMsgTime);

    void ChatMessageSend();


private slots:
    void on_returnBtn_clicked();

signals:
    void sigSendToServer(QByteArray array);
    void sigSendToClient(QString message, qintptr socketDiscriptor);
    void sigReturnToLogIn();

};

#endif // CHATROOM_H
