#include "allmain.h"
#include "ui_allmain.h"

Allmain::Allmain(QWidget *parent)
    : ElaWindow(parent)
    , ui(new Ui::Allmain)
{
    ui->setupUi(this);
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
    connect(logIn, &LogIn::sigSendToLogIn, this, &Allmain::onSendToServer);
    connect(signIn, &SignIn::sigSendToSignIn, this, &Allmain::onSendToServer);
    connect(chatRoom, &ChatRoom::sigSendToServer, this, &Allmain::onSendToServer);
    connect(logIn, &LogIn::sigForwardToSignIn, [=](){
        signIn->show();
    });
    connect(logIn, &LogIn::sigForwardToChatRoom, [=](){
        //! 发送请求，得到 admin 的 history。
        //! initHistory()
        chatRoom->show();
    });
    connect(signIn, &SignIn::sigReturnToLogIn, [=](){
        logIn->show();
    });
    connect(signIn, &SignIn::sigSignInSuccessToLogIn, [=](Client *cClient){
        logIn->signInSuccess(cClient);
    });
    connect(chatRoom, &ChatRoom::sigReturnToLogIn, [=](){
        logIn->show();
    });
}

void Allmain::initAllMain(Client *cClient)
{
    client = cClient;
}

void Allmain::connectToServer()
{
    QString server_IP = "127.0.0.1";
    int port = 23333;
    socket->connectToHost(server_IP, port);
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
        QWidget *currentWidget = qApp->activeWindow();
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
            currentWidget->hide();
            logIn->unconnected();
        }
    }
}

void Allmain::onReadyRead()
{
    qDebug() << "[socket] receive message ...";
    while(socket->bytesAvailable() > 0)
    {
        QByteArray datagram;
        datagram = socket->readAll();
        dealMessage(datagram);
    }
}

void Allmain::dealMessage(QByteArray message)
{
    int signal = ObjectToJson::parseSignal(message).toInt();
    qDebug() << "signal: " << signal;
    switch(signal) {
    case LOGIN:
    {
        QList<Client*> clientList = ObjectToJson::parseClient(message);
        client = clientList[0];
        logIn->logInSuccess(client);
        break;
    }
    case LOGINF:
    {
        logIn->logInFail();
        break;
    }
    case SIGNIN:
    {
        QList<Client*> clientList = ObjectToJson::parseClient(message);
        client = clientList[0];
        signIn->signInSuccess(client);
        break;
    }
    case SIGNINF:
    {
        signIn->signInFail();
        break;
    }
    case SENDMSG:
    {
        QString msg = ObjectToJson::parseString(message);
        chatRoom->receiveMessage(msg);
        break;
    }
    }
}
