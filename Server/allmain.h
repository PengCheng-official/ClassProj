#ifndef ALLMAIN_H
#define ALLMAIN_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QThread>
#include <QThreadPool>
#include "worker.h"
#include "objects.h"
#include "objecttojson.h"
#include "Database/clientmapper.h"
#include "statement.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Allmain; }
QT_END_NAMESPACE

class Allmain : public QWidget
{
    Q_OBJECT
protected:
    void startToListen();
    //开始监听连接

    void connectToDB();
    //连接数据库

    QString generateRandomSalt(int length);
    //生成指定长度的随机盐值

    QString sha256Hash(const QString &data, const QString &salt);
    //生成SHA-256哈希加密算法

public:
    Allmain(QWidget *parent = nullptr);
    ~Allmain();

public slots:
    void on_newConnection(qintptr socketDescriptor);
    //系统函数的重载，在新连接时自动调用

    void receiveMessage();
    //socket接受信息

    void sendMessage(qintptr socketDescriptor, const QByteArray &array);
    //socket发送信息

    void dealMessage(QByteArray &message);
    //服务端处理socket通讯

private slots:
    void on_newConnection();

private:
    Ui::Allmain *ui;
    QTcpServer *server;
    QTcpSocket *socket;
    QSqlDatabase db;
    QHash<qintptr, QTcpSocket*> clients;
    QThreadPool *threadPool;
};
#endif // ALLMAIN_H
