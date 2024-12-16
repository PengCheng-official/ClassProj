#include "login.h"
#include "ui_login.h"

LogIn::LogIn(QWidget *parent) :
    ElaWidget(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);
    setWindowButtonFlag(ElaAppBarType::StayTopButtonHint, false);
    setWindowTitle("系统账号登录");
    setWindowIcon(QIcon(":/Resource/login_icon.png"));
    setFixedSize(420, 500);
    this->setIsFixedSize(true);

    upScreen = new QLabel(this);
    QPixmap pixmap(":/Resource/login_background.jpg");
    upScreen->setPixmap(pixmap);
    upScreen->setFixedHeight(150);
    upScreen->setScaledContents(true);
    upScreen->setAlignment(Qt::AlignCenter);
    upScreen->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    lineName = new ElaLineEdit(this);
    lineName->setFixedSize(270, 45);
    lineName->setAlignment(Qt::AlignHCenter);
    lineName->setStyleSheet("font-size: 15px;");
    lineName->setPlaceholderText("请输入账号");

    linePassWord = new ElaLineEdit(this);
    linePassWord->setFixedSize(270, 45);
    linePassWord->setAlignment(Qt::AlignHCenter);
    linePassWord->setEchoMode(QLineEdit::Password);
    linePassWord->setStyleSheet("font-size: 15px;");
    linePassWord->setPlaceholderText("请输入密码");

    wrongEdit2 = new ElaText(this);
    wrongEdit2->setFixedSize(270, 20);
    wrongEdit2->setAlignment(Qt::AlignHCenter);
    connect(lineName,&QLineEdit::textChanged,[=](){
       wrongEdit2->setText("");
    });
    wrongEdit2->setStyleSheet("background-color: transparent; color: red; font-size: 14px;");

    //登录按钮设计
    loginBtn = new ElaPushButton("登录", this);
    loginBtn->setFixedSize(270, 50);
    loginBtn->setLightDefaultColor(ElaThemeColor(ElaThemeType::Light, PrimaryNormal));
    loginBtn->setLightHoverColor(ElaThemeColor(ElaThemeType::Light, PrimaryHover));
    loginBtn->setLightPressColor(ElaThemeColor(ElaThemeType::Light, PrimaryPress));
    loginBtn->setLightTextColor(Qt::white);
    loginBtn->setStyleSheet("font-size: 15px;");
    connect(loginBtn, &QPushButton::clicked, this, &LogIn::onLoginBtnClicked);

    //注册按钮设计
    signBtn = new ElaPushButton("注册账号", this);
    signBtn->setFixedSize(100, 35);
    connect(signBtn, &QPushButton::clicked, this, &LogIn::onSignBtnClicked);

    //联系客服按钮设计
    chatBtn = new ElaPushButton("联系客服", this);
    chatBtn->setFixedSize(100, 35);
    connect(chatBtn, &QPushButton::clicked, this, &LogIn::onChatBtnClicked);

    line = new QFrame(this);
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setLineWidth(1);
    line->setStyleSheet("background-color: black;");

    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(upScreen);
    mainLayout->addSpacing(20);

    auto midHLayout = [](QWidget *widget) -> QHBoxLayout* {
        QHBoxLayout *layout = new QHBoxLayout;
        layout->addStretch();
        layout->addWidget(widget);
        layout->addStretch();
        return layout;
    };
    mainLayout->addLayout(midHLayout(lineName));
    mainLayout->addSpacing(10);
    mainLayout->addLayout(midHLayout(linePassWord));
    mainLayout->addLayout(midHLayout(wrongEdit2));
    mainLayout->addLayout(midHLayout(loginBtn));

    QHBoxLayout *signAndchat = new QHBoxLayout();
    signAndchat->addStretch();
    signAndchat->addWidget(chatBtn);
    signAndchat->addWidget(line);
    signAndchat->addWidget(signBtn);
    signAndchat->addStretch();

    mainLayout->addStretch();
    mainLayout->addLayout(signAndchat);
    mainLayout->addSpacing(10);
}

LogIn::~LogIn()
{
    delete ui;
}

void LogIn::onLoginBtnClicked()
{
    qDebug() << "[login] trying to login ...";
    Client* client = new Client;
    if (lineName->text() == "") {
        wrongEdit2->setText("用户名不能为空!");
        return;
    }
    else client->setClientName(lineName->text());
    if (linePassWord->text() == "") {
        wrongEdit2->setText("密码不能为空!");
        return;
    }
    else client->setClientPwd(linePassWord->text());

    QList<Client*> clientList;
    clientList.append(client);
    QJsonObject message;
    ObjectToJson::addClients(message, clientList);
    ObjectToJson::addSignal(message, QString::number(LOGIN));    //登录请求
    QByteArray array = ObjectToJson::changeJson(message);
    emit sigSendToLogIn(array);
    qDebug() << "[login] send to login";
}

void LogIn::logInSuccess(Client* client)
{
    qDebug() << "[login] log in success";
    this->hide();
    lineName->clear();
    linePassWord->clear();
    emit sigBackToMain(client);
}

void LogIn::logInFail()
{
    qDebug() << "[login] log in fail";
    wrongEdit2->setText("账号或密码错误！");
}

void LogIn::signInSuccess(Client *cClient)
{
    qDebug() << "[login] sign in success";
    lineName->setText(cClient->getClientName());
    linePassWord->clear();
    this->show();
}

void LogIn::unconnected()
{
    wrongEdit2->setText("抱歉！服务器连接失败。");
    loginBtn->setEnabled(false);
    signBtn->setEnabled(false);
    chatBtn->setEnabled(false);
    ElaProgressBar *progressBar = new ElaProgressBar(this);
    progressBar->setMinimum(0);
    progressBar->setMaximum(0);
    mainLayout->insertWidget(7, progressBar);
}

void LogIn::onSignBtnClicked()
{
    this->hide();
    emit sigForwardToSignIn();
}

void LogIn::onChatBtnClicked()
{
    emit sigForwardToChatRoom();
}
