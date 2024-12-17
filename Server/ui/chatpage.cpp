#include "chatpage.h"

#include <QMouseEvent>
#include <QSqlError>

#include "chatroom.h"
#include "../objects/client.h"
#include "../dao/clientmapper.h"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QVBoxLayout>
#include "ElaScrollPageArea.h"
#include "ElaMenu.h"
#include "ElaText.h"
#include "ElaWindow.h"
#include "ElaToggleSwitch.h"
#include "ElaPushButton.h"

int ChatPage::restMsg = 0;
ChatPage::ChatPage(QWidget *parent)
    : ElaScrollPage(parent)
{
    setWindowTitle("联系卖家");

    centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("联系在线卖家");
    addCentralWidget(centralWidget, true, true, 0);
    connectToDB();
}

ChatPage::~ChatPage()
{
}

void ChatPage::setClientList(QList<Client *> &cClientList)
{
    // 先清除上次的在线列表
    QLayout *oldLayout = centralWidget->layout();
    if (oldLayout) {
        // 删除旧的布局
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget(); // 删除布局中的所有小部件
            delete item;           // 删除布局项
        }
        delete oldLayout;          // 删除旧布局
    }

    // 创建新的布局
    QVBoxLayout *centerLayout = new QVBoxLayout(centralWidget);

    clientList = cClientList;
    qDebug() << "[chatpage] online : " << clientList.size();
    if (clientList.size() == 0)
    {
        ElaScrollPageArea* clientArea = new ElaScrollPageArea(this);
        QHBoxLayout* clientLayout = new QHBoxLayout(clientArea);
        ElaText* text = new ElaText("无人在线", this);
        text->setTextPixelSize(15);
        clientLayout->addWidget(text);
        clientLayout->addStretch();
        centerLayout->addWidget(clientArea);
    }

    QMap<Client *, int> clientMap;
    for (auto client : clientList)
    {
        clientMap[client] = 1;

        ElaScrollPageArea* clientArea = new ElaScrollPageArea(this);
        QHBoxLayout* clientLayout = new QHBoxLayout(clientArea);
        ElaText *uid = new ElaText("在线： UID："+QString::number(client->getClientId()), this);
        uid->setTextPixelSize(17);
        uid->setFixedWidth(200);
        ElaText *name = new ElaText("名称："+client->getClientName(), this);
        name->setTextPixelSize(17);
        name->setFixedWidth(250);
        clientLayout->addWidget(uid);
        clientLayout->addWidget(name);
        clientLayout->addStretch();

        ElaPushButton* connectBtn = new ElaPushButton("联系他", this);
        connect(connectBtn, &QPushButton::clicked, [=](){
            emit sigLockBtn();
            chatRoom = new ChatRoom(client);
            chatRoom->show();
            connect(this, &ChatPage::sigReceiveMessage, chatRoom, &ChatRoom::receiveMessage);
            connect(chatRoom, &ChatRoom::sigSendToClient, [=](QByteArray array){
                emit sigSendToClient(client, array);
            });
            connect(chatRoom, &ChatRoom::sigUnlocked, [=]{
                qDebug() << "[chatPage] sigUnlocked";
                emit sigUnlockBtn();
            });
        });
        connect(this, &ChatPage::sigLockBtn, [=](){
            qDebug() << "[chatPage] locked";
            connectBtn->setEnabled(false);
        });
        connect(this, &ChatPage::sigUnlockBtn, [=](){
            qDebug() << "[chatPage] unlocked";
            connectBtn->setEnabled(true);
        });

        clientLayout->addWidget(connectBtn);
        clientLayout->addSpacing(10);
        centerLayout->addWidget(clientArea);
    }

    ClientMapper *clientMapper = new ClientMapper(db);
    QList<Client *> clients = clientMapper->select();
    for (auto client : clients)
    {
        if (clientMap[client]) continue;

        ElaScrollPageArea* clientArea = new ElaScrollPageArea(this);
        QHBoxLayout* clientLayout = new QHBoxLayout(clientArea);
        ElaText *uid = new ElaText("离线： UID："+QString::number(client->getClientId()), this);
        uid->setTextPixelSize(17);
        uid->setFixedWidth(200);
        ElaText *name = new ElaText("名称："+client->getClientName(), this);
        name->setTextPixelSize(17);
        name->setFixedWidth(250);
        clientLayout->addWidget(uid);
        clientLayout->addWidget(name);
        clientLayout->addStretch();

        ElaPushButton* connectBtn = new ElaPushButton("联系他", this);
        connect(connectBtn, &QPushButton::clicked, [=](){
            emit sigLockBtn();
            chatRoom = new ChatRoom(client);
            chatRoom->show();
            connect(this, &ChatPage::sigReceiveMessage, chatRoom, &ChatRoom::receiveMessage);
            connect(chatRoom, &ChatRoom::sigSendToClient, [=](QByteArray array){
                emit sigSendToClient(client, array);
            });
            connect(chatRoom, &ChatRoom::sigUnlocked, [=]{
                qDebug() << "[chatPage] sigUnlocked";
                emit sigUnlockBtn();
            });
        });
        connect(this, &ChatPage::sigLockBtn, [=](){
            qDebug() << "[chatPage] locked";
            connectBtn->setEnabled(false);
        });
        connect(this, &ChatPage::sigUnlockBtn, [=](){
            qDebug() << "[chatPage] unlocked";
            connectBtn->setEnabled(true);
        });

        clientLayout->addWidget(connectBtn);
        clientLayout->addSpacing(10);
        centerLayout->addWidget(clientArea);
    }
    centerLayout->addStretch();
}

void ChatPage::mouseReleaseEvent(QMouseEvent *event)
{
    switch (event->button())
    {
    case Qt::LeftButton:
    {
        break;
    }
    case Qt::BackButton:
    {
        this->navigation(0);
        break;
    }
    case Qt::ForwardButton:
    {
        this->navigation(1);
        break;
    }
    case Qt::MiddleButton:
    {
        this->navigation(2);
        break;
    }
    default:
    {
        break;
    }
    }
    ElaScrollPage::mouseReleaseEvent(event);
}

void ChatPage::connectToDB()
{
    db = QSqlDatabase::addDatabase("QODBC", "ChatPage");
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
