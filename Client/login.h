#ifndef LOGIN_H
#define LOGIN_H

// 登录界面
#include <QWidget>
#include <QObject>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QTcpSocket>
#include <QHostAddress>
#include "objects.h"
#include "signin.h"
#include "chatroom.h"
#include "objecttojson.h"
#include "statement.h"

class TcpSocket;
class SignIn;
class ChatRoom;

namespace Ui {
class LogIn;
}

class LogIn : public QWidget
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = nullptr);
    ~LogIn();

    void paintEvent(QPaintEvent *event);

    void logInSuccess(Client* cClient);

    void logInFail();

    void signInSuccess(Client* cClient);

    void unconnected();

private:
    Ui::LogIn* ui;
    QPoint last;

protected:
    void mousePressEvent(QMouseEvent* event);
    //鼠标移动
    void mouseMoveEvent(QMouseEvent* event);
    //鼠标释放
    void mouseReleaseEvent(QMouseEvent* event);

private slots:
    void on_loginbtn_clicked();

    void on_signBtn_clicked();

    void on_forgetBtn_clicked();

    void on_chatBtn_clicked();

signals:
    void sigSendToLogIn(QByteArray array);
    void sigBackToMain(Client* client);
    void sigForwardToSignIn();
    void sigForwardToChatRoom();
};

#endif // LOGIN_H
