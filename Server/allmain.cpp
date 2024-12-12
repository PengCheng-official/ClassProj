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
    setUserInfoCardPixmap(QPixmap(":/Resource/icon.jpg"));
    setUserInfoCardTitle("WORLD GOVT");
    setUserInfoCardSubTitle("pengcheng050210@foxmail.com");

    threadPool = new ThreadPool(1024);
    server = new QTcpServer;
    connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    startToListen();
    connectToDB();

    // 图形界面的初始化
    // 主页
    _homePage = new HomePage(this);

    // 聊天界面
    _chatPage = new ChatPage(this);
    connect(_chatPage, &ChatPage::sigSendToClient, [=](Client* client, QByteArray array){
        QTcpSocket *socket = socketHash.value(client, nullptr);
        if (socket != nullptr)
        {
            qDebug() << "[server] send to client: signal-" << ObjectToJson::parseSignal(array).toInt();
            socket->write(array);
        }
    });

    // 搜索界面
    _searchPage = new SearchPage(this);
    connect(_searchPage, &SearchPage::sigTurnToProduct, [=](Product *product){
//        emit navigationNodeClicked(ElaNavigationType::PageNode, _productPage->property("ElaPageKey").toString());
        _searchPage->hide();
        _productPage->show();
        _productPage->initPage(product);
    });

    // 商品界面
    _productPage = new ProductPage(this);

    addPageNode("首页", _homePage, ElaIconType::House);
    addPageNode("搜索商品", _searchPage, ElaIconType::MagnifyingGlass);
    addPageNode("商品详情操作", _productPage, ElaIconType::Comments);
    addPageNode("联系卖家", _chatPage, ElaIconType::Comments);
    connect(this, &ElaWindow::navigationNodeClicked, this, [=](ElaNavigationType::NavigationNodeType nodeType, QString nodeKey) {
        switch(nodeType) {
        case ElaNavigationType::PageNode:
        {
            if (nodeKey == _chatPage->property("ElaPageKey").toString())
            {
                qDebug() << "[Allmain] enter chat online: " << clients.size();
                _chatPage->setClientList(clients);
                ChatPage::restMsg = 0;
                setNodeKeyPoints(_chatPage->property("ElaPageKey").toString(), 0);
            }
            else if (nodeKey == _searchPage->property("ElaPageKey").toString())
            {
                qDebug() << "[Allmain] enter search Page";
                ProductMapper *productMapper = new ProductMapper(mdb);
                _searchPage->updatePage(productMapper->select(""));
            }
            else if (nodeKey == _productPage->property("ElaPageKey").toString())
            {
                qDebug() << "[Allmain] enter product Page << empty";
                _productPage->initPage();
            }
            break;
        }
        case ElaNavigationType::FooterNode:
        {
            break;
        }
        }
    });

    moveToCenter();
}

Allmain::~Allmain()
{
    delete ui;
}

void Allmain::dealMessage(QTcpSocket* socket, QByteArray &socketData, size_t threadName)
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
    int signal = ObjectToJson::parseSignal(socketData).toInt();
    qDebug() << "signal: " << signal;
    switch(signal) {
    case LOGIN:
    {
        QList<Client*> clientList = ObjectToJson::parseClient(socketData);
        client = new Client(*clientList[0]);
        QJsonObject message;

        ClientMapper *clientMapper = new ClientMapper(db);
        QList<Client*> dbClient = clientMapper->select(client->getClientName());
        if (!dbClient.empty() && dbClient[0]->getClientPwd() == sha256Hash(client->getClientPwd(), dbClient[0]->getClientSalt()))
        {
            ObjectToJson::addSignal(message, QString::number(LOGIN));    //登录成功
            clientList[0] = dbClient[0];
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
        QList<Client*> clientList = ObjectToJson::parseClient(socketData);
        client = new Client(*clientList[0]);
        ClientMapper *clientMapper = new ClientMapper(db);
        QList<Client*> dbClient = clientMapper->select(client->getClientName());

        QJsonObject message;
        if (dbClient.size() > 0) {
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
            clientList[0] = dbClient[0];
        }
        ObjectToJson::addClientList(message, clientList);
        QByteArray array = ObjectToJson::changeJson(message);
        emit sigSendToClient(socket, array);
        break;
    }
    case CHATHISTORY:
    {
        // 处理 Client 对聊天记录的请求
        QList<int> idList = ObjectToJson::parseNums(socketData);
        int id = idList[0];
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
        QList<Chat *> chatList = ObjectToJson::parseChat(socketData);
        ChatMapper *chatMapper = new ChatMapper(db);
        chatMapper->insert(chatList);
        //TODO 发送失败

        _chatPage->sigReceiveMessage(chatList[0]);
        setNodeKeyPoints(_chatPage->property("ElaPageKey").toString(), ++ChatPage::restMsg);
        break;
    }
    case PERSONCHANGE:
    {
        // 查询用户名是否合法，修改并返回
        QList<Client*> clientList = ObjectToJson::parseClient(socketData);
        QList<QString> stringList = ObjectToJson::parseStrings(socketData);   //原密码
        bool pwd = stringList.size() == 0 ? false : true;
        QString rawPassword;
        if (pwd) rawPassword = stringList[0];
        ClientMapper *clientMapper = new ClientMapper(db);
        QList<Client *> dbClient = clientMapper->select(clientList[0]->getClientId());
        if (clientList[0]->getClientName() != dbClient[0]->getClientName())
        {
            QList<Client *> nameCheck = clientMapper->select(clientList[0]->getClientName());
            if (nameCheck.size() != 0)
            {
                // 有重名，返回失败
                qDebug() << "[socket] rename";
                QJsonObject message;
                ObjectToJson::addSignal(message, QString::number(PERSONCHANGEFAIL));
                QByteArray array = ObjectToJson::changeJson(message);
                emit sigSendToClient(socket, array);
                break;
            }
        }
        if (pwd)
        {
            if (dbClient[0]->getClientPwd() != sha256Hash(rawPassword, dbClient[0]->getClientSalt()))
            {
                // 输入的密码不正确，返回错误
                qDebug() << "[socket] wrong pwd";
                QJsonObject message;
                ObjectToJson::addSignal(message, QString::number(PERSONCHANGEERROR));
                QByteArray array = ObjectToJson::changeJson(message);
                emit sigSendToClient(socket, array);
                break;
            }
        }

        if (clientList[0]->getClientName() != dbClient[0]->getClientName())
        {
            // 修改名字
            qDebug() << "[socket] change name";
            clientMapper->update(clientList[0]->getClientId(), clientList[0]);
        }
        if (pwd)
        {
            // 修改密码
            QString newPasswd = clientList[0]->getClientPwd();
            QString salt = generateRandomSalt(16);
            qDebug() << "[socket] change pwd: " << clientList[0]->getClientId() << newPasswd;

            clientList[0]->setClientSalt(salt);
            clientList[0]->setClientPwd(sha256Hash(newPasswd, salt));
            clientMapper->update(clientList[0]->getClientId(), clientList[0]);
        }
        // 其他信息修改
        clientMapper->update(clientList[0]->getClientId(), clientList[0]);

        QJsonObject message;
        ObjectToJson::addSignal(message, QString::number(PERSONCHANGE));
        QByteArray array = ObjectToJson::changeJson(message);
        emit sigSendToClient(socket, array);
        break;
    }
    case SEARCHPRODUCT:
    {
        // 处理商品搜索
        QList<QString> strList = ObjectToJson::parseStrings(socketData);
        QList<Client *> clientList = ObjectToJson::parseClient(socketData);

        ProductMapper *productMapper = new ProductMapper(db);
        QList<Product *> productList = productMapper->select(strList[0]);

        QJsonObject message;
        ObjectToJson::addProductList(message, productList);
        ObjectToJson::addSignal(message, QString::number(SEARCHPRODUCT));
        QByteArray array = ObjectToJson::changeJson(message);
        emit sigSendToClient(socket, array);

        // 处理搜索记录
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

