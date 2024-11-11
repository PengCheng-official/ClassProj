#include "allmain.h"
#include "ui_allmain.h"

Allmain::Allmain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Allmain)
{
    ui->setupUi(this);
    connectToDB();

    server = new QTcpServer;
    connect(server, SIGNAL(newConnection()), this, SLOT(on_newConnection()));
    socket = new QTcpSocket(this);

    startToListen();
}

Allmain::~Allmain()
{
    delete ui;
}

void Allmain::setSlots()
{

}


void Allmain::dealMessage(QByteArray message)
{
    Client* client;
    QString signal = ObjectToJson::parseSignal(message);
    qDebug() << signal;
    if (signal == QString::number(LOGIN))
    {
        QList<Client*> clientList = ObjectToJson::parseClient(message);
        client = new Client(*clientList[0]);
        QJsonObject message;

        ClientMapper *mapper = new ClientMapper(db);
        QList<Client*> db_client = mapper->select(client->getClientName());
        if (!db_client.empty() && db_client[0]->getClientPwd() == sha256Hash(client->getClientPwd(), db_client[0]->getClientSalt()))
        {
            ObjectToJson::addSignal(message, QString::number(LOGIN));    //登录成功
        }
        else
        {
            ObjectToJson::addSignal(message, QString::number(LOGINF));    //登录失败
            clientList.pop_front();
        }

        ObjectToJson::integrateClientList(message, clientList);
        QByteArray array = ObjectToJson::changeJson(message);
        socket->write(array);
    }
    else if (signal == QString::number(SIGNIN))
    {
        QList<Client*> clientList = ObjectToJson::parseClient(message);
        client = new Client(*clientList[0]);
        QJsonObject message;

        ClientMapper *mapper = new ClientMapper(db);
        QList<Client*> db_client = mapper->select(client->getClientName());
        if (db_client.size() > 0) {
            ObjectToJson::addSignal(message, QString::number(SIGNINF));  //注册失败
            clientList.pop_front();
        }
        else
        {
            QString rawPasswd = client->getClientPwd();
            QString salt = generateRandomSalt(16);
            client->setClientSalt(salt);
            client->setClientPwd(sha256Hash(rawPasswd, salt));
            mapper->insert(client);
            ObjectToJson::addSignal(message, QString::number(SIGNIN));    //注册成功
        }
        ObjectToJson::integrateClientList(message, clientList);
        QByteArray array = ObjectToJson::changeJson(message);
        socket->write(array);
    }
}

void Allmain::on_newConnection()
{
    socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::connected,[=](){
        qDebug() << "[scoket] new Connected ...";
        qDebug() << "Addr:" << socket->peerAddress();
        qDebug() << "Port:" << socket->peerPort();
    });
    connect(socket, &QTcpSocket::disconnected,[=](){
        qDebug() << "[scoket] disconnected";
        socket->deleteLater();
    });
    connect(socket, &QTcpSocket::stateChanged, [=](QAbstractSocket::SocketState socketState){
        qDebug() << "[scoket] state changed: " << socketState;
    });
    connect(socket, &QTcpSocket::readyRead,[=](){
        qDebug() << "[scoket] receive message ...";
        receiveMessage();
    });
}

void Allmain::startToListen()
{
    QString IP = "127.0.0.1";
    int port = 23333;
    server->listen(QHostAddress(IP), port);
    qDebug() << "[socket] listening ...";
}

void Allmain::connectToDB()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("MySql");
    db.setUserName("root");
    db.setPassword("pengcheng_050210");

    if(!db.open()) {
        qDebug() << "[database] Failed to connect to db: " << db.lastError();
        return;
    }

    qDebug() << "[database] Connected to MySql";
}

QString Allmain::generateRandomSalt(int length)
{
    QByteArray salt;
    salt.resize(length);
    for (int i = 0; i < length; ++i) {
        salt[i] = static_cast<char>(QRandomGenerator::global()->bounded(0, 256));
    }
    return QString::fromUtf8(salt.toHex());
}

QString Allmain::sha256Hash(const QString &data, const QString &salt)
{
    QByteArray combinedData = data.toUtf8() + salt.toUtf8();
    QByteArray hash = QCryptographicHash::hash(combinedData, QCryptographicHash::Sha256);
    return QString::fromUtf8(hash.toHex());
}

void Allmain::receiveMessage()
{
    while(socket->bytesAvailable() > 0)
    {
        QByteArray datagram;
        datagram = socket->readAll();
        dealMessage(datagram);
    }
}

