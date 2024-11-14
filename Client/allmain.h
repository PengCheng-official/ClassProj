#ifndef ALLMAIN_H
#define ALLMAIN_H

#include <QWidget>
#include "login.h"
#include "signin.h"
#include "chatroom.h"
#include "objects.h"
#include "objecttojson.h"
#include "statement.h"

#include "ElaWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Allmain; }
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class Allmain; }
QT_END_NAMESPACE

class Allmain : public ElaWindow
{
    Q_OBJECT
private:
    Ui::Allmain *ui;
    QList<Client*> ClientList;
    QTcpSocket *socket;
    LogIn *logIn;
    SignIn *signIn;
    ChatRoom *chatRoom;
    Client* client;

public:
    Allmain(QWidget *parent = nullptr);
    ~Allmain();

protected:
    void initAllMain();
    void initAllMain(Client* cClient);

    void connectToServer();

    void dealMessage(QByteArray message);

private slots:
    void onSendToServer(QByteArray array);
    void onReadyRead();
    void onStateChanged(QAbstractSocket::SocketState socketState);


};
#endif // ALLMAIN_H
