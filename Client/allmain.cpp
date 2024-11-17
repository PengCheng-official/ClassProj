#include "allmain.h"
#include "ui_allmain.h"

Allmain::Allmain(QWidget *parent)
    : ElaWindow(parent)
    , ui(new Ui::Allmain)
{
    ui->setupUi(this);
    resize(1100, 660);
    setWindowButtonFlag(ElaAppBarType::ThemeChangeButtonHint, false);
    setWindowButtonFlag(ElaAppBarType::StayTopButtonHint, false);
    setWindowIcon(QIcon(":/Resource/allmain_icon.png"));

    logIn = new LogIn();
    signIn = new SignIn();
    chatRoom = new ChatRoom();
    socket = new QTcpSocket();
    connectToServer();

    initAllMain();
    logIn->show();
    connect(logIn, &LogIn::sigBackToMain, [=](Client *cClient){
        initAllMain(cClient);
        logIn->hide();
        this->show();
        setWindowTitle(QString("%1 的主页").arg(client->getClientName()));
    });
}

Allmain::~Allmain()
{
    delete ui;
}

void Allmain::initAllMain()
{
    // 发送 socket 请求的信号
    connect(logIn, &LogIn::sigSendToLogIn, this, &Allmain::onSendToServer);
    connect(signIn, &SignIn::sigSendToSignIn, this, &Allmain::onSendToServer);
    connect(chatRoom, &ChatRoom::sigSendToServer, this, &Allmain::onSendToServer);

    // LogIn 的信号处理
    connect(logIn, &LogIn::sigForwardToSignIn, [=](){
        signIn->show();
    });
    connect(logIn, &LogIn::sigForwardToChatRoom, [=](){
        //发此处为匿名聊天，不会得到 history。
        chatRoom->show();
    });

    // SignIn 的信号处理
    connect(signIn, &SignIn::sigReturnToLogIn, [=](){
        logIn->show();
    });
    connect(signIn, &SignIn::sigSignInSuccessToLogIn, [=](Client *cClient){
        logIn->signInSuccess(cClient);
    });

    // ChatRoom 的信号处理
    connect(chatRoom, &ChatRoom::sigReturnToLogIn, [=](){
        logIn->show();
    });
}

void Allmain::initAllMain(Client *cClient)
{
    // 数据的初始化
    client = cClient;

    // 图形界面的初始化
    addFooterNode("官方客服", nullptr, _chatKey, 0, ElaIconType::Comments);
    connect(this, &ElaWindow::navigationNodeClicked, this, [=](ElaNavigationType::NavigationNodeType nodeType, QString nodeKey) {
        if (nodeKey == _chatKey)
        {
            QJsonObject message;
            ObjectToJson::addNum(message, client->getClientId());
            ObjectToJson::addSignal(message, QString::number(CHATHISTORY));
            QByteArray array = ObjectToJson::changeJson(message);
            onSendToServer(array);
        }
    });
}

void Allmain::connectToServer()
{
    // 连接 Server 端
    QString server_IP = "127.0.0.1";
    int port = 23333;
    socket->connectToHost(server_IP, port);
    // connect来自 socket 的信号
    connect(socket, &QTcpSocket::readyRead, this, &Allmain::onReadyRead);
    connect(socket, &QTcpSocket::stateChanged, this, &Allmain::onStateChanged);

    connect(socket, &QTcpSocket::connected, [=](){
        qDebug() << "[socket] new Connected: ";
        qDebug() << "Addr:" << socket->peerAddress();
        qDebug() << "Port:" << socket->peerPort();
    });
    connect(socket, &QTcpSocket::disconnected, [=](){
        qDebug() << "[socket] disconnected";
        socket->deleteLater();
    });
    connect(socket, &QTcpSocket::errorOccurred, [=](QAbstractSocket::SocketError socketError) {
        qDebug() << "[socket] error: " << socketError;
    });
}

void Allmain::onSendToServer(QByteArray array)
{
    qDebug() << "[socket] send to Server ...";
    socket->write(array);
}

void Allmain::onStateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << "[socket] state changed: " << socketState;
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        // 断开连接了
        QWidget *currentWidget = qApp->activeWindow();  // 获取当前窗口
        // 各窗口处理办法
        if (currentWidget == logIn)
        {
            logIn->unconnected();
        }
        else if (currentWidget == signIn)
        {
            signIn->unconnected();
        }
        else if (currentWidget == this)
        {
//            this->unconnected();
        }
        else
        {
            // 异常则跳转登录界面
            currentWidget->hide();
            logIn->unconnected();
        }
    }
}

void Allmain::onReadyRead()
{
    // 接收到讯息，准备处理
    qDebug() << "[socket] receive message ...";
    while(socket->bytesAvailable() > 0)
    {
        // 有可用信息，开始处理
        QByteArray datagram;
        datagram = socket->readAll();
        dealMessage(datagram);
    }
}

void Allmain::dealMessage(QByteArray message)
{
    // 处理接收到的讯息
    int signal = ObjectToJson::parseSignal(message).toInt();
    qDebug() << "signal: " << signal;
    switch(signal) {
    case LOGIN:
    {
        // 登录成功
        QList<Client*> clientList = ObjectToJson::parseClient(message);
        client = clientList[0];
        logIn->logInSuccess(client);
        break;
    }
    case LOGINFAIL:
    {
        // 登录失败
        logIn->logInFail();
        break;
    }
    case SIGNIN:
    {
        // 注册成功
        QList<Client*> clientList = ObjectToJson::parseClient(message);
        client = clientList[0];
        signIn->signInSuccess(client);
        break;
    }
    case SIGNINFAIL:
    {
        // 注册失败
        signIn->signInFail();
        break;
    }
    case CHATMSG:
    {
        // 接收到一条信息
        QList<Chat *> chatList = ObjectToJson::parseChat(message);
        chatRoom->receiveMessage(chatList[0]);
        break;
    }
    case CHATHISTORY:
    {
        // 接收到消息历史
        QList<Chat *> chatList = ObjectToJson::parseChat(message);
        chatRoom->initHistory(chatList);
        chatRoom->initClient(client);
        chatRoom->show();
        break;
    }
    }
}
