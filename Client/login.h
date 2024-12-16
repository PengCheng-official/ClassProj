#ifndef LOGIN_H
#define LOGIN_H

// 登录界面
#include "ElaWidget.h"

class SignIn;
class ChatRoom;
class Client;
class QVBoxLayout;
class QLabel;
class QFrame;
class ElaLineEdit;
class ElaText;
class ElaPushButton;
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
