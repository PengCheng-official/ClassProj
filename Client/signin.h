#ifndef SIGNIN_H
#define SIGNIN_H

// 注册界面
#include "ElaWidget.h"

class TcpSocket;
class Client;
class QVBoxLayout;
class QLabel;
class QFrame;
class ElaLineEdit;
class ElaText;
class ElaPushButton;
namespace Ui {
class SignIn;
}

class SignIn : public ElaWidget
{
    Q_OBJECT

public:
    explicit SignIn(QWidget *parent = nullptr);
    ~SignIn();

    void signInSuccess(Client* cClient);

    void signInFail();

    void unconnected();

private:
    Ui::SignIn* ui;
    QLabel *upScreen;
    ElaLineEdit *NameEdit;
    ElaLineEdit *PasswordEdit;
    ElaLineEdit *PhoneNumEdit;
    ElaLineEdit *EmailEdit;
    ElaLineEdit *AddrEdit;
    ElaText *NameError;
    ElaText *PasswordError;
    ElaText *AllError;
    ElaPushButton *createBtn;
    ElaPushButton *returnLogBtn;
    QFrame *line;
    QVBoxLayout *mainLayout;


private slots:
    void onCreateBtnClicked();
    void onReturnLogBtnClicked();

signals:
    void sigSendToSignIn(QByteArray array);
    void sigSignInSuccessToLogIn(Client* cClient);
    void sigReturnToLogIn();
};

#endif // SIGNIN_H
