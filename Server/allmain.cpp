#include "allmain.h"
#include "ui_allmain.h"

Allmain::Allmain(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Allmain)
{
    ui->setupUi(this);

    threadPool = new ThreadPool(1024);

    server = new QTcpServer;
    connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    startToListen();
}

Allmain::~Allmain()
{
    delete ui;
}

void Allmain::dealMessage(QTcpSocket* socket, QByteArray &message, size_t threadName)
{
    qDebug() << QString("[thread_%1]|[server] deal with message ...").arg(threadName);

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QODBC", QString::number(threadName));
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("MySql");
    db.setUserName("root");
    db.setPassword("pengcheng_050210");

    if(!db.open()) {
        qDebug() << QString("[thread_%1]|[database] Failed to connect to db: ").arg(threadName) << db.lastError();
        return;
    }
    qDebug() << QString("[thread_%1]|[database] Connected to MySql").arg(threadName);

    Client* client = new Client;
    int signal = ObjectToJson::parseSignal(message).toInt();
    qDebug() << signal;
    switch(signal) {
    case LOGIN:
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
        emit sigSendToClient(socket, array);
        break;
    }
    case SIGNIN:
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
        emit sigSendToClient(socket, array);
        break;
    }
    }

    db.close();
    QSqlDatabase::removeDatabase(QString::number(threadName));
    qDebug() << QString("[thread_%1]|[database] disconnect to database").arg(threadName);
}

void Allmain::onNewConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();
    qDebug() << "[server] receive new connection ...";
    connect(socket, &QTcpSocket::connected,[=](){
        qDebug() << "[server] new Connected ...";
        qDebug() << "Addr:" << socket->peerAddress();
        qDebug() << "Port:" << socket->peerPort();
    });
    connect(socket, &QTcpSocket::disconnected,[=](){
        qDebug() << "[server] disconnected";
        sockets.removeAll(socket);
        socket->deleteLater();
    });
    connect(socket, &QTcpSocket::stateChanged, [=](QAbstractSocket::SocketState socketState){
        qDebug() << "[server] state changed: " << socketState;
    });
    connect(socket, &QTcpSocket::readyRead,[this, socket](){
        qDebug() << "[server] receive message...";
        //接受到通讯请求，启动新的线程处理请求
        //QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
        connect(this, &Allmain::sigSendToClient, this, &Allmain::on_sendToClient);

        threadPool->enqueue([this, socket]{
            qDebug() << "[threadPool] create a new thread";
            while(socket->bytesAvailable() > 0)
            {
                qDebug() << "[server] message available...";
                QByteArray datagram;
                datagram = socket->readAll();
                dealMessage(socket, datagram, this->threadPool->getThreadName());
            }
        });
    });
    sockets.append(sockets);
}

void Allmain::startToListen()
{
    QString IP = "127.0.0.1";
    int port = 23333;
    server->listen(QHostAddress(IP), port);
    qDebug() << "[server] listening ...";
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

void Allmain::on_sendToClient(QTcpSocket *socket, const QByteArray &array)
{
    // 子线程外，传输通讯
    socket->write(array);
}

