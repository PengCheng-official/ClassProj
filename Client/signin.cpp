#include "signin.h"
#include "ui_signin.h"

SignIn::SignIn(QWidget *parent) :
    ElaWidget(parent),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);
    setWindowButtonFlag(ElaAppBarType::StayTopButtonHint, false);
    setWindowTitle("系统账号注册");
    setWindowIcon(QIcon(":/Resource/signin_icon.png"));
    setFixedSize(450, 500);
    this->setIsFixedSize(true);

    upScreen = new QLabel(this);
    upScreen->setFixedHeight(40);
    upScreen->setText("  欢迎！！(∗ ˊωˋ ∗)つロ");
    upScreen->setStyleSheet("font-size: 32px;");

    ElaToolButton *nameIcon = new ElaToolButton(this);
    nameIcon->setElaIcon(ElaIconType::FaceLaugh);
    nameIcon->setEnabled(false);
    nameIcon->setFixedSize(25, 45);

    NameEdit = new ElaLineEdit(this);
    NameEdit->setFixedSize(270, 45);
    NameEdit->setAlignment(Qt::AlignHCenter);
    NameEdit->setStyleSheet("font-size: 15px;");
    NameEdit->setPlaceholderText("请输入账号，必填");

    NameError = new ElaText(this);
    NameError->setFixedSize(270, 20);
    NameError->setAlignment(Qt::AlignHCenter);

    ElaToolButton *passwordIcon = new ElaToolButton(this);
    passwordIcon->setElaIcon(ElaIconType::BlockQuestion);
    passwordIcon->setEnabled(false);
    passwordIcon->setFixedSize(25, 45);

    PasswordEdit = new ElaLineEdit(this);
    PasswordEdit->setFixedSize(270, 45);
    PasswordEdit->setAlignment(Qt::AlignHCenter);
    PasswordEdit->setEchoMode(QLineEdit::Password);
    PasswordEdit->setStyleSheet("font-size: 15px;");
    PasswordEdit->setPlaceholderText("请输入密码，必填");

    PasswordError = new ElaText(this);
    PasswordError->setFixedSize(270, 20);
    PasswordError->setAlignment(Qt::AlignHCenter);

    ElaToolButton *phoneIcon = new ElaToolButton(this);
    phoneIcon->setElaIcon(ElaIconType::PhonePlus);
    phoneIcon->setEnabled(false);
    phoneIcon->setFixedSize(25, 45);

    PhoneNumEdit = new ElaLineEdit(this);
    PhoneNumEdit->setFixedSize(270, 45);
    PhoneNumEdit->setAlignment(Qt::AlignHCenter);
    PhoneNumEdit->setStyleSheet("font-size: 15px;");
    PhoneNumEdit->setPlaceholderText("请输入手机号");

    ElaToolButton *emailIcon = new ElaToolButton(this);
    emailIcon->setElaIcon(ElaIconType::Mailbox);
    emailIcon->setEnabled(false);
    emailIcon->setFixedSize(25, 45);

    EmailEdit = new ElaLineEdit(this);
    EmailEdit->setFixedSize(270, 45);
    EmailEdit->setAlignment(Qt::AlignHCenter);
    EmailEdit->setStyleSheet("font-size: 15px;");
    EmailEdit->setPlaceholderText("请输入邮箱");

    ElaToolButton *addrIcon = new ElaToolButton(this);
    addrIcon->setElaIcon(ElaIconType::BuildingUser);
    addrIcon->setEnabled(false);
    addrIcon->setFixedSize(25, 45);

    AddrEdit = new ElaLineEdit(this);
    AddrEdit->setFixedSize(270, 45);
    AddrEdit->setAlignment(Qt::AlignHCenter);
    AddrEdit->setStyleSheet("font-size: 15px;");
    AddrEdit->setPlaceholderText("请输入地址");

    AllError = new ElaText(this);
    AllError->setFixedSize(270, 20);
    AllError->setAlignment(Qt::AlignHCenter);

    //注册按钮设计
    createBtn = new ElaPushButton("注册账号", this);
    createBtn->setFixedSize(150, 45);
    createBtn->setLightDefaultColor(ElaThemeColor(ElaThemeType::Light, PrimaryNormal));
    createBtn->setLightHoverColor(ElaThemeColor(ElaThemeType::Light, PrimaryHover));
    createBtn->setLightPressColor(ElaThemeColor(ElaThemeType::Light, PrimaryPress));
    createBtn->setLightTextColor(Qt::white);
    connect(createBtn, &QPushButton::clicked, this, &SignIn::onCreateBtnClicked);

    //返回登录按钮设计
    returnLogBtn = new ElaPushButton("返回登录", this);
    returnLogBtn->setFixedSize(150, 45);
    connect(returnLogBtn, &QPushButton::clicked, this, &SignIn::onReturnLogBtnClicked);

    NameError->setStyleSheet("background-color: transparent; color: red; font-size: 14px;");
    PasswordError->setStyleSheet("background-color: transparent; color: red; font-size: 14px;");
    AllError->setStyleSheet("background-color: transparent; color: red; font-size: 14px;");

    line = new QFrame(this);
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setLineWidth(1);
    line->setStyleSheet("background-color: black;");

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(upScreen);
    mainLayout->addSpacing(25);

    auto midHLayout = [](QWidget *widget) -> QHBoxLayout* {
        QHBoxLayout *layout = new QHBoxLayout;
        layout->addStretch();
        layout->addWidget(widget);
        layout->addStretch();
        return layout;
    };

    auto midHLayout2 = [](QWidget *widget1, QWidget *widget2) -> QHBoxLayout* {
        QHBoxLayout *layout = new QHBoxLayout;
        layout->addStretch();
        layout->addWidget(widget1);
        layout->addWidget(widget2);
        layout->addStretch();
        return layout;
    };
    mainLayout->addLayout(midHLayout2(nameIcon, NameEdit));
    mainLayout->addLayout(midHLayout(NameError));
    mainLayout->addLayout(midHLayout2(passwordIcon, PasswordEdit));
    mainLayout->addLayout(midHLayout(PasswordError));
    mainLayout->addLayout(midHLayout2(phoneIcon, PhoneNumEdit));
    mainLayout->addSpacing(10);
    mainLayout->addLayout(midHLayout2(emailIcon, EmailEdit));
    mainLayout->addSpacing(10);
    mainLayout->addLayout(midHLayout2(addrIcon, AddrEdit));
    mainLayout->addSpacing(15);
    mainLayout->addLayout(midHLayout(AllError));

    QHBoxLayout *twoSide = new QHBoxLayout();
    twoSide->addStretch();
    twoSide->addWidget(returnLogBtn);
    twoSide->addSpacing(10);
    twoSide->addWidget(line);
    twoSide->addSpacing(10);
    twoSide->addWidget(createBtn);
    twoSide->addStretch();

    mainLayout->addStretch();
    mainLayout->addLayout(twoSide);
    mainLayout->addSpacing(10);
}

SignIn::~SignIn()
{
    delete ui;
}

void SignIn::onCreateBtnClicked()
{
    qDebug() << "[signin] trying to signin";
    AllError->clear();
    NameError->clear();
    PasswordError->clear();
    Client *client = new Client;
    if (NameEdit->text() == "") {
        NameError->setText("账号名不能为空!");
        return;
    }
    else client->setClientName(NameEdit->text());
    if (PasswordEdit->text() == "") {
        PasswordError->setText("密码不能为空!");
        return;
    }
    else client->setClientPwd(PasswordEdit->text());
    if(PhoneNumEdit->text() != "") {
        client->setClientPhone(PhoneNumEdit->text());
    }
    if (EmailEdit->text() != "") {
        client->setClientEmail(EmailEdit->text());
    }
    if (AddrEdit->text() != "") {
        client->setClientAddr(AddrEdit->text());
    }
    QList<Client*> clientList;
    clientList.append(client);
    QJsonObject message;
    ObjectToJson::integrateClientList(message, clientList);
    ObjectToJson::addSignal(message, QString::number(SIGNIN));
    QByteArray array =ObjectToJson::changeJson(message);
    emit sigSendToSignIn(array);
    qDebug() << "[signin] send to sign in";
}

void SignIn::signInSuccess(Client *client)
{
    qDebug() << "[signin] sign in success";
    this->hide();
    NameEdit->clear();
    PasswordEdit->clear();
    PhoneNumEdit->clear();
    EmailEdit->clear();
    AddrEdit->clear();
    emit sigSignInSuccessToLogIn(client);
}

void SignIn::signInFail()
{
    qDebug() << "[signin] sign in fail";
    PasswordEdit->clear();
    AllError->setText("已存在该账号名！请尝试其他。");
}

void SignIn::onReturnLogBtnClicked()
{
    this->hide();
    emit sigReturnToLogIn();
}

void SignIn::unconnected()
{
    AllError->setText("抱歉！服务器连接失败。");
    createBtn->setEnabled(false);
    returnLogBtn->setEnabled(false);
    ElaProgressBar *progressBar = new ElaProgressBar(this);
    progressBar->setMinimum(0);
    progressBar->setMaximum(0);
    mainLayout->insertWidget(13, progressBar);
}
