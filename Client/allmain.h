#ifndef ALLMAIN_H
#define ALLMAIN_H

#include <iostream>
#include <QWidget>
#include "login.h"
#include "signin.h"
#include "chatroom.h"
#include "objects/client.h"
#include "objects/chat.h"
#include "objects/order.h"
#include "objects/orderlist.h"
#include "objects/product.h"
#include "objects/search.h"
#include "objecttojson.h"
#include "statement.h"

#include "ui/personpage.h"
#include "ui/searchpage.h"
#include "ui/homepage.h"
#include "ui/shoppingpage.h"
#include "ElaWindow.h"
#include "ElaContentDialog.h"
#include "ElaMessageBar.h"


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
    ElaContentDialog *unconnectDialog;

    HomePage *_homePage;
    PersonPage *_personPage;
    QString _chatKey{""};
    QString _personKey{""};
    SearchPage *_searchPage;
    ShoppingPage *_shoppingPage;

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
