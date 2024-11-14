#ifndef LOGIN_H
#define LOGIN_H

// 登录界面
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include "objects.h"
#include "objecttojson.h"
#include "signin.h"
#include "chatroom.h"
#include "statement.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <ElaScrollPage.h>
#include <QPixmap>
#include "ElaWidget.h"
#include "ElaLineEdit.h"
#include "ElaText.h"
#include "ElaPushButton.h"
#include "ElaImageCard.h"

class SignIn;
class ChatRoom;

namespace Ui {
class LogIn;
}

class LogIn : public ElaWidget
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = nullptr);
    ~LogIn();

    void logInSuccess(Client* cClient);

    void logInFail();

    void signInSuccess(Client* cClient);

    void unconnected();

private:
    Ui::LogIn* ui;
    QPoint last;
    QLabel *upScreen;
    ElaLineEdit *lineName;
    ElaLineEdit *linePassWord;
    ElaText *wrongEdit2;
    ElaPushButton *loginBtn;
    ElaPushButton *signBtn;
    ElaPushButton *chatBtn;
    QFrame *line;

private slots:
    void onLoginBtnClicked();

    void onSignBtnClicked();

    void onChatBtnClicked();

signals:
    void sigSendToLogIn(QByteArray array);
    void sigBackToMain(Client* client);
    void sigForwardToSignIn();
    void sigForwardToChatRoom();
};

#endif // LOGIN_H
