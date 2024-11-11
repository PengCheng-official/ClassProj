#ifndef FORGETPWD_H
#define FORGETPWD_H

#include <QWidget>
#include <QObject>
#include <QMouseEvent>
#include <QTcpSocket>
#include <QHostAddress>
#include "objects.h"
#include "objecttojson.h"
#include "statement.h"

namespace Ui {
class ForgetPwd;
}

class ForgetPwd : public QWidget
{
    Q_OBJECT

public:
    explicit ForgetPwd(QWidget *parent = nullptr);
    ~ForgetPwd();

    QTcpSocket *getSocket() const;
    void setSocket(QTcpSocket *value);

    Client *getClient() const;
    void setClient(Client *value);
    void getSelect(QByteArray message);

    void receiveMessage();
    void dealMessage(QByteArray message);

private:
    Ui::ForgetPwd *ui;
    QTcpSocket* socket;
    Client* client;
    QPoint last;

protected:
    void mousePressEvent(QMouseEvent* event);
    //鼠标移动
    void mouseMoveEvent(QMouseEvent* event);
    //鼠标释放
    void mouseReleaseEvent(QMouseEvent* event);

signals:
    void resetPwdSuccess(Client *client, QTcpSocket *socket);
    void returnToLogIn();
};

#endif // FORGETPWD_H
