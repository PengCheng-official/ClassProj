#ifndef CHATROOM_H
#define CHATROOM_H

// 联系客服界面
#include <QWidget>
#include <QObject>
#include <QMouseEvent>
#include <QTcpSocket>
#include <QHostAddress>
#include "objects.h"
#include "objecttojson.h"
#include "statement.h"

class TcpSocket;

namespace Ui {
class ChatRoom;
}

class ChatRoom : public QWidget
{
    Q_OBJECT

public:
    explicit ChatRoom(QWidget *parent = nullptr);
    ~ChatRoom();

    Client *getClient() const;
    void setClient(Client *value);

    qintptr getSockeDiscriptor() const;
    void setSockeDiscriptor(const qintptr &value);

private:
    void receiveMessage();

    void dealMessage(QByteArray message);

    void dealMessageTime(QString curMsgTime);

    void ChatMessageSend();

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;


private:
    Ui::ChatRoom *ui;
    QTcpSocket *socket;
    Client *client;
    QPoint diff_pos;
    QPoint window_pos;
    QPoint mouse_pos;
    qintptr sockeDiscriptor;

private slots:
    bool eventFilter(QObject *target, QEvent *event) override;

    void on_returnBtn_clicked();

signals:
    void sigSendToServer(QByteArray array);
    void sigSendToClient(QString message, qintptr socketDiscriptor);
    void sigReturnToLogIn();

};

#endif // CHATROOM_H
