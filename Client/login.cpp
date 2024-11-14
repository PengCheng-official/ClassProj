#include "login.h"
#include "ui_login.h"

LogIn::LogIn(QWidget *parent) :
    ElaWidget(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);
    setWindowButtonFlag(ElaAppBarType::StayTopButtonHint, false);
    setWindowTitle("系统账号登录");
    setWindowIcon(QIcon(":/include/Image/icon.jpg"));
    setFixedSize(450, 530);
    this->setIsFixedSize(true);

    upScreen = new QLabel(this);
    QPixmap pixmap(":/include/Resource/login_background.jpg");
    upScreen->setPixmap(pixmap);
    upScreen->setFixedHeight(150);
    upScreen->setScaledContents(true);
    upScreen->setAlignment(Qt::AlignCenter);
    upScreen->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    lineName = new ElaLineEdit(this);
    lineName->setFixedHeight(50);
    lineName->setFixedWidth(240);
    lineName->setAlignment(Qt::AlignHCenter);
    lineName->setStyleSheet("font-size: 15px;");
    lineName->setPlaceholderText("请输入账号");
    lineName->setFocus();

    linePassWord = new ElaLineEdit(this);
    linePassWord->setFixedHeight(50);
    linePassWord->setFixedWidth(240);
    linePassWord->setAlignment(Qt::AlignHCenter);
    linePassWord->setEchoMode(QLineEdit::Password);
    linePassWord->setStyleSheet("font-size: 15px;");
    linePassWord->setPlaceholderText("请输入密码");

    wrongEdit2 = new ElaText(this);
    wrongEdit2->setFixedHeight(20);
    wrongEdit2->setFixedWidth(240);
    wrongEdit2->setAlignment(Qt::AlignHCenter);
    connect(lineName,&QLineEdit::textChanged,[=](){
       wrongEdit2->setText("");
    });
    wrongEdit2->setStyleSheet("background-color: transparent; color: red; font-size: 14px;");

    loginBtn = new ElaPushButton("登录", this);
    loginBtn->setFixedHeight(60);
    loginBtn->setFixedWidth(240);
//    loginBtn->setLightTextColor(QColor("white"));
    loginBtn->setStyleSheet("font-size: 14px;");
    connect(loginBtn, &QPushButton::clicked, this, &LogIn::onLoginBtnClicked);

    signBtn = new ElaPushButton("注册账号", this);
    signBtn->setFixedHeight(40);
    signBtn->setFixedWidth(100);
    connect(signBtn, &QPushButton::clicked, this, &LogIn::onSignBtnClicked);

    chatBtn = new ElaPushButton("联系客服", this);
    chatBtn->setFixedHeight(40);
    chatBtn->setFixedWidth(100);
    connect(chatBtn, &QPushButton::clicked, this, &LogIn::onChatBtnClicked);

    line = new QFrame(this);
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setLineWidth(1);
    line->setStyleSheet("background-color: black;");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(upScreen);
    layout->addSpacing(20);

    QHBoxLayout *HlineName = new QHBoxLayout();
    HlineName->addStretch();
    HlineName->addWidget(lineName);
    HlineName->addStretch();
    layout->addLayout(HlineName);

    layout->addSpacing(10);

    QHBoxLayout *HlinePassWord = new QHBoxLayout();
    HlinePassWord->addStretch();
    HlinePassWord->addWidget(linePassWord);
    HlinePassWord->addStretch();
    layout->addLayout(HlinePassWord);

    QHBoxLayout *HwrongEdit2 = new QHBoxLayout();
    HwrongEdit2->addStretch();
    HwrongEdit2->addWidget(wrongEdit2);
    HwrongEdit2->addStretch();
    layout->addLayout(HwrongEdit2);

    QHBoxLayout *HloginBtn = new QHBoxLayout();
    HloginBtn->addStretch();
    HloginBtn->addWidget(loginBtn);
    HloginBtn->addStretch();
    layout->addLayout(HloginBtn);

    QHBoxLayout *signAndchat = new QHBoxLayout();
    signAndchat->addStretch();
    signAndchat->addWidget(signBtn);
    signAndchat->addWidget(line);
    signAndchat->addWidget(chatBtn);
    signAndchat->addStretch();

    layout->addStretch();
    layout->addLayout(signAndchat);
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
    ObjectToJson::integrateClientList(message, clientList);
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
}

void LogIn::onSignBtnClicked()
{
    this->hide();
    emit sigForwardToSignIn();
}

void LogIn::onChatBtnClicked()
{
    this->hide();
    emit sigForwardToChatRoom();
}
