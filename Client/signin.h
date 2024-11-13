#ifndef SIGNIN_H
#define SIGNIN_H
// 注册界面
#include <QWidget>
#include <QObject>
#include <QMouseEvent>
#include <QTcpSocket>
#include <QHostAddress>
#include "objects.h"
#include "objecttojson.h"
#include "statement.h"

class TcpSocket;

namespace Ui {
class SignIn;
}

class SignIn : public QWidget
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = nullptr);
    ~SignIn();

    void signInSuccess(Client* cClient);

    void signInFail();

private:
    Ui::SignIn* ui;
    Client *client;
    QPoint last;

protected:
    void mousePressEvent(QMouseEvent* event);
    //鼠标移动
    void mouseMoveEvent(QMouseEvent* event);
    //鼠标释放
    void mouseReleaseEvent(QMouseEvent* event);

private slots:
    void on_createBtn_clicked();
    void on_returnLogBtn_clicked();

signals:
    void sigSendToSignIn(QByteArray array);
    void sigSignInSuccessToLogIn(Client* cClient);
    void sigReturnToLogIn();
};

#endif // SIGNIN_H
