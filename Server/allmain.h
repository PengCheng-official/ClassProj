#ifndef ALLMAIN_H
#define ALLMAIN_H

#include "ElaWindow.h"
#include <QSqlDatabase>

class QTcpSocket;
class QTcpServer;
class QReadWriteLock;
class Client;
class Chat;
class ThreadPool;
class HomePage;
class ChatPage;
class SearchPage;
class ProductPage;
class HistoryPage;

QT_BEGIN_NAMESPACE
namespace Ui { class Allmain; }
QT_END_NAMESPACE

extern QReadWriteLock dbLock;
class Allmain : public ElaWindow
{
    Q_OBJECT
public:
    Allmain(QWidget *parent = nullptr);
    ~Allmain();

private:
    Ui::Allmain *ui;
    QTcpServer *server;
    QSqlDatabase mdb;
    ThreadPool *threadPool;

    QList<QTcpSocket *> sockets;
    QList<Client *> clients;
    QHash<QTcpSocket *, Client *> clientHash;
    QHash<Client *, QTcpSocket *> socketHash;

    HomePage *_homePage{nullptr};
    ChatPage *_chatPage{nullptr};
    SearchPage *_searchPage{nullptr};
    ProductPage *_productPage{nullptr};
    HistoryPage *_historyPage{nullptr};

protected:
    void startToListen();
    //开始监听连接

    void connectToDB();
    //连接数据库

    QString generateRandomSalt(int length);
    //生成指定长度的随机盐值

    QString sha256Hash(const QString &data, const QString &salt);
    //生成SHA-256哈希加密算法

    void dealMessage(QTcpSocket* socket, QByteArray &message, QString threadName);
    //服务端处理socket通讯

public slots:
    void onSendToClient(QTcpSocket* socket, const QByteArray &array);
    //socket发送信息

private slots:
    void onNewConnection();
    //系统函数的重载，在新连接时自动调用

signals:
    void sigSendToClient(QTcpSocket* socket, const QByteArray &array);
    void sigLoginSuccess(QTcpSocket* socket, Client* client);
    void sigReceiveMessage(Chat *chat);

};
#endif // ALLMAIN_H
