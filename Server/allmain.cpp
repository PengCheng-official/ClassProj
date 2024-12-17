#include "allmain.h"
#include "ui_allmain.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QTime>
#include <QRandomGenerator>
#include <QSqlError>
#include <QJsonObject>
#include <QReadWriteLock>

#include "ThreadPool.h"
#include "objects/client.h"
#include "objects/chat.h"
#include "objects/order.h"
#include "objects/orderlist.h"
#include "objects/product.h"
#include "objects/search.h"
#include "objects/shopping.h"
#include "objecttojson.h"
#include "dao/clientmapper.h"
#include "dao/chatmapper.h"
#include "dao/productmapper.h"
#include "dao/shoppingmapper.h"
#include "dao/orderlistmapper.h"
#include "dao/ordermapper.h"
#include "statement.h"

#include "ElaMessageBar.h"
#include "ui/chatpage.h"
#include "ui/homepage.h"
#include "ui/searchpage.h"
#include "ui/productpage.h"

QReadWriteLock dbLock;
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
        _productPage->refreshPage(product);
    });

    // 商品界面
    _productPage = new ProductPage(this);
    connect(_productPage, &ProductPage::sigCreateFail, [=](int error){
       switch(error)
       {
       case 0:
           ElaMessageBar::error(ElaMessageBarType::BottomRight, "更改失败", "未设置名称", 2000, this);
           break;
       case 11:
           ElaMessageBar::error(ElaMessageBarType::BottomRight, "更改失败", "价格不是浮点数", 2000, this);
           break;
       case 10:
           ElaMessageBar::error(ElaMessageBarType::BottomRight, "更改失败", "未设置价格", 2000, this);
           break;
       case 21:
           ElaMessageBar::error(ElaMessageBarType::BottomRight, "更改失败", "库存不是整数", 2000, this);
           break;
       case 20:
           ElaMessageBar::error(ElaMessageBarType::BottomRight, "更改失败", "未设置库存", 2000, this);
           break;
       case 31:
           ElaMessageBar::error(ElaMessageBarType::BottomRight, "更改失败", "活动请输入数字", 2000, this);
           break;
       case 4:
           ElaMessageBar::error(ElaMessageBarType::BottomRight, "更改失败", "活动输入非法", 2000, this);
           break;
       case 200:
           ElaMessageBar::success(ElaMessageBarType::BottomRight, "更改成功", "", 2000, this);
           break;
       }
    });

//    addPageNode("首页", _homePage, ElaIconType::House);
    addPageNode("搜索商品", _searchPage, ElaIconType::MagnifyingGlass);
    addPageNode("商品详情操作", _productPage, ElaIconType::Gift);
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
                _searchPage->updatePage(productMapper->selectLike(""));
            }
            else if (nodeKey == _productPage->property("ElaPageKey").toString())
            {
                qDebug() << "[Allmain] enter product Page << empty";
                _productPage->refreshPage();
            }
            break;
        }
        case ElaNavigationType::FooterNode:
        {
            break;
        }
        }
    });
    ProductMapper *productMapper = new ProductMapper(mdb);
    _searchPage->updatePage(productMapper->selectLike(""));

    moveToCenter();
}

Allmain::~Allmain()
{
    delete ui;
}

void Allmain::dealMessage(QTcpSocket* socket, QByteArray &socketData, QString threadName)
{
    qDebug() << QString("[thread_%1]|[server] deal with message ...").arg(threadName);

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QODBC", threadName);
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
        QList<Client*> clientList = ObjectToJson::parseClients(socketData);
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

        ObjectToJson::addClients(message, clientList);
        QByteArray array = ObjectToJson::changeJson(message);
        emit sigSendToClient(socket, array);
        break;
    }
    case SIGNIN:
    {
        QList<Client *> clientList = ObjectToJson::parseClients(socketData);
        client = new Client(*clientList[0]);
        ClientMapper *clientMapper = new ClientMapper(db);
        QList<Client *> dbClient = clientMapper->select(client->getClientName());

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
            clientList[0]->setClientId(clientMapper->insert(client));
            ObjectToJson::addSignal(message, QString::number(SIGNIN));    //注册成功
        }
        ObjectToJson::addClients(message, clientList);
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

        QJsonObject message;
        ObjectToJson::addSignal(message, QString::number(CHATHISTORY));
        ObjectToJson::addChats(message, chatList);
        QByteArray array = ObjectToJson::changeJson(message);
        emit sigSendToClient(socket, array);
        break;
    }
    case CHATMSG:
    {
        // 处理 Client 发来的信息，就一条
        QList<Chat *> chatList = ObjectToJson::parseChats(socketData);
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
        QList<Client*> clientList = ObjectToJson::parseClients(socketData);
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
        QList<Client *> clientList = ObjectToJson::parseClients(socketData);

        ProductMapper *productMapper = new ProductMapper(db);
        QList<Product *> productList = productMapper->selectLike(strList[0]);

        QJsonObject message;
        ObjectToJson::addProducts(message, productList);
        ObjectToJson::addSignal(message, QString::number(SEARCHPRODUCT));
        QByteArray array = ObjectToJson::changeJson(message);
        emit sigSendToClient(socket, array);

        //TODO: 处理搜索记录
        break;
    }
    case REQUESTHOME:
    {
        // 首页信息请求
        ProductMapper *productMapper = new ProductMapper(db);
        QList<Product *> proList = productMapper->selectRand();
        QJsonObject message;
        ObjectToJson::addProducts(message, proList);
        ObjectToJson::addSignal(message, QString::number(REQUESTHOME));
        QByteArray array = ObjectToJson::changeJson(message);
        emit sigSendToClient(socket, array);
        break;
    }
    case ADDSHOPPING:
    {
        // 添加购物车: 新增或者累加
        ShoppingMapper *shoppingMapper = new ShoppingMapper(db);
        QList<Shopping *> shopList = ObjectToJson::parseShoppings(socketData);
        for (auto shopping : shopList)
        {
            int num = shoppingMapper->select(shopping);
            if (num)
            {
                shopping->setShoppingNum(num + shopping->getShoppingNum());
                shoppingMapper->update(shopping);
            }
            else shoppingMapper->insert(shopping);
        }

        // 返回添加成功
        QJsonObject message;
        ObjectToJson::addSignal(message, QString::number(ADDSHOPPING));
        QByteArray array = ObjectToJson::changeJson(message);
        emit sigSendToClient(socket, array);
        break;
    }
    case REQUESTSHOPPING:
    {
        // 购物车请求
        Client *client = ObjectToJson::parseClients(socketData)[0];
        ShoppingMapper *shoppingMapper = new ShoppingMapper(db);
        QList<Shopping *> shopList =  shoppingMapper->select(client->getClientId());
        QList<Product *> productList;
        ProductMapper *productMapper = new ProductMapper(db);
        for (auto shopping : shopList)
        {
            Product *product = productMapper->select(shopping->getProductId())[0];
            productList.append(product);
        }

        QJsonObject message;
        ObjectToJson::addShoppings(message, shopList);
        ObjectToJson::addProducts(message, productList);
        ObjectToJson::addSignal(message, QString::number(REQUESTSHOPPING));
        QByteArray array = ObjectToJson::changeJson(message);
        emit sigSendToClient(socket, array);
        break;
    }
    case DELSHOPPING:
    {
        // 删除购物车
        QList<Shopping *> shoppingList = ObjectToJson::parseShoppings(socketData);
        ShoppingMapper *shoppingMapper = new ShoppingMapper(db);
        shoppingMapper->delet(shoppingList);
        break;
    }
    case CREATEORDER:
    {
        // 创建订单
        Order *order = ObjectToJson::parseOrders(socketData)[0];
        OrderMapper *orderMapper = new OrderMapper(db);
        QList<int> oids = {orderMapper->insert(order)};

        QJsonObject message;
        ObjectToJson::addNums(message, oids);
        ObjectToJson::addSignal(message, QString::number(CREATEORDER));
        QByteArray array = ObjectToJson::changeJson(message);
        emit sigSendToClient(socket, array);
        break;
    }
    case CREATEORDERLIST:
    {
        // 创建关联订单List
        QList<OrderList *> orderLists = ObjectToJson::parseOrderLists(socketData);
        OrderListMapper *orderListMapper = new OrderListMapper(db);
        orderListMapper->insert(orderLists);
        break;
    }
    case UPDATEORDER:
    {
        // 更新订单
        Order *order = ObjectToJson::parseOrders(socketData)[0];
        OrderMapper *orderMapper = new OrderMapper(db);
        orderMapper->update(order);
        break;
    }
    case REQUESTORDER:
    {
        // 请求订单历史
        client = ObjectToJson::parseClients(socketData)[0];
        OrderMapper *orderMapper = new OrderMapper(db);
        OrderListMapper *orderListMapper = new OrderListMapper(db);

        QList<Order *> orders = orderMapper->select(client->getClientId());
        QList<OrderList *> orderLists;
        QList<Product *> products;
        for (auto order : orders)
        {
            QList<OrderList *> orderListList = orderListMapper->select(order->getOrderId());
            // product_id 可能为 0，表示商品已被下架
            for (auto orderList : orderListList)
            {
                ProductMapper *productMapper = new ProductMapper(db);
                Product *product = productMapper->select(orderList->getProductId())[0];
                // 用product中的 price 和 num 暂存数据
                product->setProductNum(orderList->getProductNum());
                product->setProductPrice(orderList->getProductPrice());
                products.append(product);
            }
        }

        QJsonObject message;
        ObjectToJson::addOrders(message, orders);
        ObjectToJson::addProducts(message, products);
        ObjectToJson::addSignal(message, QString::number(REQUESTORDER));
        QByteArray array = ObjectToJson::changeJson(message);
        emit sigSendToClient(socket, array);
        break;
    }
    default:
        qDebug() << QString("[thread_%1]|[database] ERROR:unknown signal").arg(threadName);
        break;
    }

    db.close();
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
        qDebug() << "[server] receive message:" << socket->bytesAvailable();
        //接受到通讯请求，启动新的线程处理请求
        //QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());

        threadPool->enqueue([this, socket]{
            qDebug() << "[threadPool] create a new thread";

            while(socket->bytesAvailable() > 0)
            {
                QByteArray buffer;
                buffer = socket->readAll();
                int cnt = 0;
                while (buffer.contains("\r\n"))
                {
                    int index = buffer.indexOf("\r\n");
                    QByteArray completeMsg = buffer.left(index); // 提取完整消息
                    buffer.remove(0, index + 2);
                    QString threadName = QString::number(this->threadPool->getThreadName())+"_"+QString::number(cnt++);
                    dealMessage(socket, completeMsg, threadName);
                    QSqlDatabase::removeDatabase(threadName);
                }
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
    connect(this, &Allmain::sigSendToClient, this, &Allmain::onSendToClient);
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

void Allmain::onSendToClient(QTcpSocket *socket, const QByteArray &array)
{
    // 子线程外，传输通讯
    socket->write(array);
    qDebug() << "[server] send to client: signal-" << ObjectToJson::parseSignal(array).toInt();
}

