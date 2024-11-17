#ifndef LOGIN_H
#define LOGIN_H

// 登录界面
#include <iostream>
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include "objects/objects.h"
#include "objecttojson.h"
#include "signin.h"
#include "chatroom.h"
#include "statement.h"

#include <QWidget>
#include "ElaWidget.h"
#include "Def.h"
#include "stdafx.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <ElaScrollPage.h>
#include <QPixmap>
#include <QGraphicsOpacityEffect>
#include "ElaLineEdit.h"
#include "ElaText.h"
#include "ElaPushButton.h"
#include "ElaImageCard.h"
#include "ElaTheme.h"
#include "ElaProgressBar.h"

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
    QLabel *upScreen;
    ElaLineEdit *lineName;
    ElaLineEdit *linePassWord;
    ElaText *wrongEdit2;
    ElaPushButton *loginBtn;
    ElaPushButton *signBtn;
    ElaPushButton *chatBtn;
    QFrame *line;
    QVBoxLayout *mainLayout;

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
