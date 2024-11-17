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
    setWindowIcon(QIcon(":/Resource/icon.png"));

    threadPool = new ThreadPool(1024);
    server = new QTcpServer;
    connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    startToListen();
    connectToDB();

    // 图形界面的初始化
    _homePage = new HomePage(this);
    _chatPage = new ChatPage(this);
    connect(_chatPage, &ChatPage::sigSendToClient, [=](Client* client, QByteArray array){
        QTcpSocket *socket = socketHash.value(client, nullptr);
        if (socket != nullptr)
        {
            qDebug() << "[server] send to client: signal-" << ObjectToJson::parseSignal(array).toInt();
            socket->write(array);
        }
    });

    addPageNode("首页", _homePage, ElaIconType::House);
    addFooterNode("联系卖家", _chatPage, _chatKey, 0, ElaIconType::Comments);

    connect(this, &ElaWindow::navigationNodeClicked, this, [=](ElaNavigationType::NavigationNodeType nodeType, QString nodeKey) {
        if (nodeKey == _chatKey)
        {
            qDebug() << "[allmain] enter chat online: " << clients.size();
            _chatPage->setClientList(clients);
            ChatPage::restMsg = 0;
        }
    });

    moveToCenter();
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
    qDebug() << QString("[thread_%1]|[database] Connected to MySql!").arg(threadName);

    Client* client = new Client;
    int signal = ObjectToJson::parseSignal(message).toInt();
    qDebug() << "signal: " << signal;
    switch(signal) {
    case LOGIN:
    {
        QList<Client*> clientList = ObjectToJson::parseClient(message);
        client = new Client(*clientList[0]);
        QJsonObject message;

        ClientMapper *clientMapper = new ClientMapper(db);
        QList<Client*> db_client = clientMapper->select(client->getClientName());
        if (!db_client.empty() && db_client[0]->getClientPwd() == sha256Hash(client->getClientPwd(), db_client[0]->getClientSalt()))
        {
            ObjectToJson::addSignal(message, QString::number(LOGIN));    //登录成功
            clientList[0] = db_client[0];
            clients.append(clientList[0]);
            clientHash.insert(socket, clientList[0]);
            socketHash.insert(clientList[0], socket);
        }
        else
        {
            ObjectToJson::addSignal(message, QString::number(LOGINFAIL));    //登录失败
            clientList.pop_front();
        }

        ObjectToJson::addClientList(message, clientList);
        QByteArray array = ObjectToJson::changeJson(message);
        emit sigSendToClient(socket, array);
        break;
    }
    case SIGNIN:
    {
        QList<Client*> clientList = ObjectToJson::parseClient(message);
        client = new Client(*clientList[0]);
        ClientMapper *clientMapper = new ClientMapper(db);
        QList<Client*> db_client = clientMapper->select(client->getClientName());

        QJsonObject message;
        if (db_client.size() > 0) {
            ObjectToJson::addSignal(message, QString::number(SIGNINFAIL));  //注册失败
            clientList.pop_front();
        }
        else
        {
            QString rawPasswd = client->getClientPwd();
            QString salt = generateRandomSalt(16);
            client->setClientSalt(salt);
            client->setClientPwd(sha256Hash(rawPasswd, salt));
            clientMapper->insert(client);
            ObjectToJson::addSignal(message, QString::number(SIGNIN));    //注册成功
            clientList[0] = db_client[0];
        }
        ObjectToJson::addClientList(message, clientList);
        QByteArray array = ObjectToJson::changeJson(message);
        emit sigSendToClient(socket, array);
        break;
    }
    case CHATHISTORY:
    {
        // 处理 Client 对聊天记录的请求
        int id = ObjectToJson::parseNum(message);
        ChatMapper *chatMapper = new ChatMapper(db);
        QList<Chat *> chatList = chatMapper->select(id);
        qDebug() << QString("[thread_%1]|[server] request chat history for Client%2").arg(threadName).arg(id);
        qDebug() << chatList.size();

        QJsonObject message;
        ObjectToJson::addSignal(message, QString::number(CHATHISTORY));
        ObjectToJson::addChatList(message, chatList);
        QByteArray array = ObjectToJson::changeJson(message);
        emit sigSendToClient(socket, array);
        break;
    }
    case CHATMSG:
    {
        // 处理 Client 发来的信息，就一条
        QList<Chat *> chatList = ObjectToJson::parseChat(message);
        ChatMapper *chatMapper = new ChatMapper(db);
        chatMapper->insert(chatList);
        //TODO 发送失败

        _chatPage->sigReceiveMessage(chatList[0]);
        setNodeKeyPoints(_chatKey, ++ChatPage::restMsg);
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
        qDebug() << "[server] disconnected...";
        Client* disClient = clientHash.value(socket, nullptr);
        if (disClient == nullptr) return;

        qDebug() << disClient->getClientName();
        clients.removeAll(disClient);
        sockets.removeAll(socket);
        socket->deleteLater();
        _chatPage->setClientList(clients);
    });
    connect(socket, &QTcpSocket::stateChanged, [=](QAbstractSocket::SocketState socketState){
        qDebug() << "[server] state changed: " << socketState;
    });
    connect(socket, &QTcpSocket::readyRead,[this, socket](){
        qDebug() << "[server] receive message...";
        //接受到通讯请求，启动新的线程处理请求
        //QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
        threadPool->enqueue([this, socket]{
            qDebug() << "[threadPool] create a new thread";
            while(socket->bytesAvailable() > 0)
            {
                QByteArray datagram;
                datagram = socket->readAll();
                dealMessage(socket, datagram, this->threadPool->getThreadName());
            }
        });
    });
    sockets.append(socket);
}

void Allmain::startToListen()
{
    QString IP = "127.0.0.1";
    int port = 23333;
    server->listen(QHostAddress(IP), port);
    connect(this, &Allmain::sigSendToClient, this, &Allmain::on_sendToClient);
    qDebug() << "[server] listening...";
}

void Allmain::connectToDB()
{
    mdb = QSqlDatabase::addDatabase("QODBC", "main");
    mdb.setHostName("localhost");
    mdb.setPort(3306);
    mdb.setDatabaseName("MySql");
    mdb.setUserName("root");
    mdb.setPassword("pengcheng_050210");
    if(!mdb.open()) {
        qDebug() << "[database] Failed to connect to db: " << mdb.lastError();
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

void Allmain::on_sendToClient(QTcpSocket *socket, const QByteArray &array)
{
    // 子线程外，传输通讯
    socket->write(array);
    qDebug() << "[server] send to client: signal-" << ObjectToJson::parseSignal(array).toInt();
}

