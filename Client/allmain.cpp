#include "allmain.h"
#include "ui_allmain.h"

Allmain::Allmain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Allmain)
{
    ui->setupUi(this);
//    this->setWindowFlag(Qt::FramelessWindowHint);
    logIn = new LogIn();
    signIn = new SignIn();
    chatRoom = new ChatRoom();
    socket = new TcpSocket();
    connectToServer();

    initAllMain();
    logIn->show();
    connect(logIn, &LogIn::backToMain, [=](Client *cClient){
        initAllMain(cClient);
        logIn->hide();
        this->show();
    });
}

Allmain::~Allmain()
{
    delete ui;
}

void Allmain::initAllMain()
{
    connect(logIn, &LogIn::sendToLogIn, this, &Allmain::sendToServer);
    connect(logIn, &LogIn::forwardToSignIn, [=](){
        signIn->show();
    });
    connect(logIn, &LogIn::forwardToChatRoom, [=](){
        chatRoom->show();
    });
    connect(signIn, &SignIn::sendToSignIn, this, &Allmain::sendToServer);
    connect(signIn, &SignIn::returnToLogIn, [=](){
        logIn->show();
    });
    connect(signIn, &SignIn::signInSuccessToLogIn, [=](Client *cClient){
        logIn->signInSuccess(cClient);
    });
    connect(chatRoom, &ChatRoom::returnToLogIn, [=](){
        logIn->show();
    });
}

void Allmain::initAllMain(Client *cClient)
{
    client = cClient;
    ui->testHello->setText(client->getClientName());
}

void Allmain::connectToServer()
{
    QString server_IP = "127.0.0.1";
    int port = 23333;
    socket->connectToHost(server_IP, port);
    connect(socket, &QTcpSocket::readyRead, this, &Allmain::on_readyRead);
    connect(socket, &QTcpSocket::stateChanged, this, &Allmain::on_stateChanged);

    connect(socket, &QTcpSocket::connected, [=](){
        qDebug() << "[socket] new Connected: ";
        qDebug() << "Addr:" << socket->peerAddress();
        qDebug() << "Port:" << socket->peerPort();
    });
    connect(socket, &QTcpSocket::disconnected, [=](){
        qDebug() << "[socket] disconnected";
        socket->deleteLater();
    });
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), [=](){
        qDebug() << "[socket] error:" << socket->errorString();
    });
}

void Allmain::sendToServer(QByteArray array)
{
    qDebug() << "[socket] send to Server ...";
    socket->write(array);
}

void Allmain::on_stateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << "[socket] state changed: " << socketState;
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        this->hide();
        logIn->show();
        logIn->unconnected();
    }
}

void Allmain::on_readyRead()
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
    QString signal = ObjectToJson::parseSignal(message);
    qDebug() << signal;
    if (signal == QString::number(LOGIN))   //登录成功
    {
        QList<Client*> clientList = ObjectToJson::parseClient(message);
        client = clientList[0];
        logIn->logInSuccess(client);
    }
    else if (signal == QString::number(LOGINF)) //登录失败
    {
        logIn->logInFail();
    }
    else if (signal == QString::number(SIGNIN)) //注册成功
    {
        QList<Client*> clientList = ObjectToJson::parseClient(message);
        client = clientList[0];
        signIn->signInSuccess(client);
    }
    else if (signal == QString::number(SIGNINF))    //注册失败
    {
        signIn->signInFail();
    }
}
