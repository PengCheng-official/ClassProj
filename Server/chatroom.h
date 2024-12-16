#ifndef CHATROOM_H
#define CHATROOM_H

// 联系客服界面
#include <QWidget>
#include "ElaWidget.h"
#include <QSqlDatabase>
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
    explicit ChatRoom(Client *cClient, QWidget *parent = nullptr);
    ~ChatRoom();

    void initHistory();
    void initClient(Client* cClient);
    void receiveMessage(Chat* chatMsg);


private:
    void dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type);
    void dealMessageTime(QString curMsgTime);
    void resizeEvent(QResizeEvent *event) override;
    void connectToDB();
    //连接数据库
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::ChatRoom *ui;
    QSqlDatabase db;
    ElaListView *listView;
    QGridLayout *mainLayout;
    Client* client;
    ElaContentDialog* _closeDialog{nullptr};

private slots:
    void on_returnBtn_clicked();

    void on_sendBtn_clicked();

signals:
    void sigSendToClient(QByteArray array);
    void sigUnlocked();
};

#endif // CHATROOM_H
