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
#include "ThreadPool.h"
#include "objects.h"
#include "objecttojson.h"
#include "Database/clientmapper.h"
#include "statement.h"

#include "ElaWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Allmain; }
QT_END_NAMESPACE

class Allmain : public ElaWindow
{
    Q_OBJECT
public:
    Allmain(QWidget *parent = nullptr);
    ~Allmain();

private:
    Ui::Allmain *ui;
    QTcpServer *server;
    QList<QTcpSocket *> sockets;
//    QSqlDatabase db;
    QHash<qintptr, QTcpSocket*> clients;
    ThreadPool *threadPool;

protected:
    void startToListen();
    //开始监听连接

    QString generateRandomSalt(int length);
    //生成指定长度的随机盐值

    QString sha256Hash(const QString &data, const QString &salt);
    //生成SHA-256哈希加密算法

    void dealMessage(QTcpSocket* socket, QByteArray &message, size_t threadName);
    //服务端处理socket通讯

public slots:
    void on_sendToClient(QTcpSocket* socket, const QByteArray &array);
    //socket发送信息


private slots:
    void onNewConnection();
    //系统函数的重载，在新连接时自动调用

signals:
    void sigSendToClient(QTcpSocket* socket, const QByteArray &array);

};
#endif // ALLMAIN_H
