#ifndef ALLMAIN_H
#define ALLMAIN_H

#include "ElaWindow.h"
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Allmain; }
QT_END_NAMESPACE

class Client;
class ElaContentDialog;
class LogIn;
class SignIn;
class ChatRoom;
class HomePage;
class PersonPage;
class SearchPage;
class ShoppingPage;
class HistoryPage;
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
    HistoryPage *_historyPage;

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

signals:
    void sigCreateOrderId(int oid);
    void sigCreateOrder();
};
#endif // ALLMAIN_H
