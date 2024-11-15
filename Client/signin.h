#ifndef SIGNIN_H
#define SIGNIN_H

// 注册界面
#include <iostream>
#include <QLabel>
#include <QObject>
#include <QMouseEvent>
#include <QTcpSocket>
#include <QHostAddress>
#include "objects.h"
#include "objecttojson.h"
#include "statement.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <ElaScrollPage.h>
#include "Def.h"
#include "stdafx.h"
#include "ElaWidget.h"
#include "ElaLineEdit.h"
#include "ElaPushButton.h"
#include "ElaImageCard.h"
#include "ElaTheme.h"
#include "ElaText.h"
#include "ElaIcon.h"
#include "ElaToolButton.h"
#include "ElaProgressBar.h"

class TcpSocket;

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
