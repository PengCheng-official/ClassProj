#include "allmain.h"
#include "ui_allmain.h"

#include <iostream>
#include <QWidget>
#include "login.h"
#include "signin.h"
#include "chatroom.h"
#include "objects/client.h"
#include "objects/chat.h"
#include "objects/order.h"
#include "objects/orderlist.h"
#include "objects/product.h"
#include "objects/search.h"
#include "objecttojson.h"
#include "statement.h"

#include "ui/personpage.h"
#include "ui/searchpage.h"
#include "ui/homepage.h"
#include "ui/shoppingpage.h"
#include "ui/historypage.h"
#include "ElaContentDialog.h"
#include "ElaMessageBar.h"

Allmain::Allmain(QWidget *parent)
    : ElaWindow(parent)
    , ui(new Ui::Allmain)
{
    ui->setupUi(this);
    resize(1050, 720);
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

    setUserInfoCardPixmap(QPixmap(":/Resource/T.jpg"));
    setUserInfoCardTitle(client->getClientName());
    setUserInfoCardSubTitle("欢迎您( つ•̀ω•́)つ");

    // 图形界面的初始化
    // 首页
    _homePage = new HomePage(client, this);
    connect(_homePage, &HomePage::sigSendToServer, this, &Allmain::onSendToServer);

    // 个人信息
    _personPage = new PersonPage(client, this);
    connect(_personPage, &PersonPage::sigSendToServer, this, &Allmain::onSendToServer);
    connect(_personPage, &PersonPage::sigClientChanged, [=](Client *nClient){
        client = nClient;
        setUserInfoCardPixmap(QPixmap(client->getClientImage()));
        setUserInfoCardTitle(client->getClientName());
        setWindowTitle(QString("%1 的主页").arg(client->getClientName()));
        qDebug() << "[Allmain] client changed";
    });

    // 搜索商品
    _searchPage = new SearchPage(client, this);
    connect(_searchPage, &SearchPage::sigSendToServer, this, &Allmain::onSendToServer);

    // 购物车界面
    _shoppingPage = new ShoppingPage(client, this);
    connect(_shoppingPage, &ShoppingPage::sigSendToServer, this, &Allmain::onSendToServer);
    connect(_shoppingPage, &ShoppingPage::sigSendMessageBar, [=](bool success, QString title, QString subTitle){
        if (success) ElaMessageBar::success(ElaMessageBarType::BottomRight, title, subTitle, 2000, this);
        else ElaMessageBar::error(ElaMessageBarType::BottomRight, title, subTitle, 2000, this);
    });
    connect(_shoppingPage, &ShoppingPage::sigRefreshPage, [=](){
        qDebug() << "[Allmain] refresh shopping Page...";
        QList<Client *> clientList = {client};
        QJsonObject message;
        ObjectToJson::addClients(message, clientList);
        ObjectToJson::addSignal(message, QString::number(REQUESTSHOPPING));
        QByteArray array = ObjectToJson::changeJson(message);
        onSendToServer(array);
    });

    // 订单历史界面
    _historyPage = new HistoryPage(client, this);
    connect(_historyPage, &HistoryPage::sigSendToServer, this, &Allmain::onSendToServer);

    addPageNode("首页", _homePage, ElaIconType::House);
    addPageNode("搜索商品", _searchPage, ElaIconType::MagnifyingGlass);
    addPageNode("我的购物车", _shoppingPage, ElaIconType::CartShopping);
    addPageNode("我的订单历史", _historyPage, ElaIconType::RectangleHistoryCircleUser);
    addFooterNode("官方客服", nullptr, _chatKey, 0, ElaIconType::Comments);
    addFooterNode("我的信息", _personPage, _personKey, 0, ElaIconType::User);
    connect(this, &ElaWindow::navigationNodeClicked, this, [=](ElaNavigationType::NavigationNodeType nodeType, QString nodeKey) {
        switch(nodeType) {
        case ElaNavigationType::PageNode:
        {
            if (nodeKey == _searchPage->property("ElaPageKey").toString())
            {
                qDebug() << "[Allmain] enter search Page...";
                QJsonObject message;
                QList<QString> strList = {""};
                QList<Client *> clientList = {client};
                ObjectToJson::addStrings(message, strList);
                ObjectToJson::addClients(message, clientList);
                ObjectToJson::addSignal(message, QString::number(SEARCHPRODUCT));
                QByteArray array = ObjectToJson::changeJson(message);
                onSendToServer(array);
            }
            else if (nodeKey == _homePage->property("ElaPageKey").toString())
            {
                qDebug() << "[Allmain] enter home Page...";
                QJsonObject message;
                ObjectToJson::addSignal(message, QString::number(REQUESTHOME));
                QByteArray array = ObjectToJson::changeJson(message);
                onSendToServer(array);
            }
            else if (nodeKey == _shoppingPage->property("ElaPageKey").toString())
            {
                qDebug() << "[Allmain] enter shopping Page...";
                QList<Client *> clientList = {client};
                QJsonObject message;
                ObjectToJson::addClients(message, clientList);
                ObjectToJson::addSignal(message, QString::number(REQUESTSHOPPING));
                QByteArray array = ObjectToJson::changeJson(message);
                onSendToServer(array);
            }
            else if (nodeKey == _historyPage->property("ElaPageKey").toString())
            {
                qDebug() << "[Allmain] enter history Page...";
                QList<Client *> clientList = {client};
                QJsonObject message;
                ObjectToJson::addClients(message, clientList);
                ObjectToJson::addSignal(message, QString::number(REQUESTORDER));
                QByteArray array = ObjectToJson::changeJson(message);
                onSendToServer(array);
            }
            break;
        }
        case ElaNavigationType::FooterNode:
        {
            if (nodeKey == _chatKey)
            {
                qDebug() << "[Allmain] enter chat Page...";
                QJsonObject message;
                QList<int> numList = {client->getClientId()};
                ObjectToJson::addNums(message, numList);
                ObjectToJson::addSignal(message, QString::number(CHATHISTORY));
                QByteArray array = ObjectToJson::changeJson(message);
                onSendToServer(array);
            }
            else if (nodeKey == _personKey)
            {
                qDebug() << "[Allmain] enter person Page...";
            }
            break;
        }
        }
    });
    QJsonObject message;
    ObjectToJson::addSignal(message, QString::number(REQUESTHOME));
    QByteArray array = ObjectToJson::changeJson(message);
    onSendToServer(array);
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
    qDebug() << "[socket] send to Server: signal-" << ObjectToJson::parseSignal(array).toInt();
    socket->write(array);
}

void Allmain::onStateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << "[socket] state changed: " << socketState;
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        // 断开连接了
        QWidget *currentWidget = nullptr;
        foreach (QWidget *widget, QApplication::topLevelWidgets()) {
            if (widget->isVisible()) {
                currentWidget = widget;
                break;  // 找到第一个可见的窗口
            }
        }
        // 各窗口处理办法
        if (currentWidget == logIn)
        {
            logIn->unconnected();
        }
        else if (currentWidget == signIn)
        {
            signIn->unconnected();
        }
        else if (currentWidget != nullptr)
        {
            // 主页面异常则跳转登录界面
            currentWidget->hide();
            logIn->show();
            logIn->unconnected();
        }
        else
        {
            logIn->show();
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
        QByteArray buffer;
        buffer = socket->readAll();
        while (buffer.contains("\r\n"))
        {
            int index = buffer.indexOf("\r\n");
            QByteArray completeMsg = buffer.left(index); // 提取完整消息
            buffer.remove(0, index + 2);
            dealMessage(completeMsg);
        }
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
        QList<Client*> clientList = ObjectToJson::parseClients(message);
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
        QList<Client*> clientList = ObjectToJson::parseClients(message);
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
        QList<Chat *> chatList = ObjectToJson::parseChats(message);
        chatRoom->receiveMessage(chatList[0]);
        break;
    }
    case CHATHISTORY:
    {
        // 接收到消息历史
        QList<Chat *> chatList = ObjectToJson::parseChats(message);
        chatRoom->initHistory(chatList);
        chatRoom->initClient(client);
        chatRoom->show();
        break;
    }
    case PERSONCHANGE:
    {
        // 修改个人信息成功
        ElaMessageBar::success(ElaMessageBarType::BottomRight, "修改成功", "", 2000, this);
        _personPage->showMessageWindow(true);
        break;
    }
    case PERSONCHANGEFAIL:
    {
        // 修改个人信息失败
        ElaMessageBar::error(ElaMessageBarType::BottomRight, "修改失败", "用户名已存在", 2000, this);
        _personPage->showMessageWindow(false);
        break;
    }
    case PERSONCHANGEERROR:
    {
        // 修改个人密码错误
        ElaMessageBar::error(ElaMessageBarType::BottomRight, "修改失败", "原密码输入错误", 2000, this);
        _personPage->showMessageWindow(false);
        break;
    }
    case SEARCHPRODUCT:
    {
        // 收到搜索结果
        QList<Product *> productList = ObjectToJson::parseProducts(message);
        _searchPage->refreshPage(productList);
        break;
    }
    case REQUESTHOME:
    {
        // 收到首页传送
        QList<Product *> productList = ObjectToJson::parseProducts(message);
        _homePage->refreshPage(productList);
        break;
    }
    case ADDSHOPPING:
    {
        // 添加购物车成功
        ElaMessageBar::success(ElaMessageBarType::BottomRight, "添加成功", "", 2000, this);
        //TODO: 刷新购物车页面
        break;
    }
    case REQUESTSHOPPING:
    {
        // 刷新购物车
        QList<Product *> productList = ObjectToJson::parseProducts(message);
        QList<Shopping *> shoppingList = ObjectToJson::parseShoppings(message);
        _shoppingPage->refreshPage(productList, shoppingList);
        break;
    }
    case CREATEORDER:
    {
        // 返回订单号
        int oid = ObjectToJson::parseNums(message)[0];
        emit sigCreateOrderId(oid);
        break;
    }
    case REQUESTORDER:
    {
        // 接收订单历史
        QList<Order *> orders = ObjectToJson::parseOrders(message);
        QList<Product *> products = ObjectToJson::parseProducts(message);
        _historyPage->refreshPage(orders, products);
        break;
    }
    case CHECKORDER:
    {
        // 返回库存是否充足
        int ok = ObjectToJson::parseNums(message)[0];
        if (!ok) ElaMessageBar::error(ElaMessageBarType::BottomRight, "下单失败", "商品库存不足", 2000, this);
        else {
            ElaMessageBar::success(ElaMessageBarType::BottomRight, "下单成功", "", 2000, this);
            emit sigCreateOrder();
        }
        break;
    }
    default:
        qDebug() << "[Allmain] ERROR: Unknown signal" << signal;
        break;
    }
}
