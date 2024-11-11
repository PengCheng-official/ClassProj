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
    void receiveMessage();
    void dealMessage(QByteArray message);
    //同Client

    void setSlots();
    //统一初始化信号和槽的链接

private slots:
    void on_newConnection();

private:
    Ui::Allmain *ui;
    QTcpServer *server;
    QTcpSocket *socket;
    QSqlDatabase db;
};
#endif // ALLMAIN_H
