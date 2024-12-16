#include "chatroom.h"
#include "ui_chatroom.h"


#include <QHostAddress>
#include <QSqlError>

#include "objects/client.h"
#include "objects/chat.h"
#include "objecttojson.h"
#include "dao/chatmapper.h"
#include "statement.h"

#include <QGridLayout>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "ElaWidget.h"
#include "Def.h"
#include "stdafx.h"
#include "ElaPushButton.h"
#include "ElaPlainTextEdit.h"
#include "ElaListView.h"
#include "ElaTheme.h"
#include "ElaContentDialog.h"

ChatRoom::ChatRoom(Client *cClient, QWidget *parent) :
    ElaWidget(parent),
    ui(new Ui::ChatRoom),
    client(cClient)
{
    ui->setupUi(this);
    setWindowButtonFlag(ElaAppBarType::StayTopButtonHint, false);

    setWindowTitle(QString("用户%1:%2").arg(client->getClientId()).arg(client->getClientName()));

    setWindowIcon(QIcon(":/Resource/chatroom_icon.png"));
    setMinimumSize(500, 400);
    resize(550, 600);

    ui->sendBtn->setLightDefaultColor(ElaThemeColor(ElaThemeType::Light, PrimaryNormal));
    ui->sendBtn->setLightHoverColor(ElaThemeColor(ElaThemeType::Light, PrimaryHover));
    ui->sendBtn->setLightPressColor(ElaThemeColor(ElaThemeType::Light, PrimaryPress));
    ui->sendBtn->setLightTextColor(Qt::white);
    ui->listWidget->clear();

    connectToDB();
    initHistory();
    this->setIsDefaultClosed(false);
    connect(this, &ChatRoom::closeButtonClicked, [=](){
        qDebug() << "[chatroom] close";
        emit sigUnlocked();
        window()->close();
    });
}

ChatRoom::~ChatRoom()
{
    delete ui;
}

void ChatRoom::initHistory()
{
    ChatMapper *chatMapper = new ChatMapper(db);
    QList<Chat *> chatList = chatMapper->select(client->getClientId());
    qDebug() << "[chatroom] history size: " << chatList.size();
    for (auto chatMsg : chatList)
    {
        QString time = QString::number(QDateTime::fromString(chatMsg->getChatTime(), "yyyy-MM-dd hh:mm:ss").toSecsSinceEpoch());
        QString msg = chatMsg->getChatText() + " l";
        qDebug() << msg << " " << time;

        if (!chatMsg->getChatIsserver())
        {
            dealMessageTime(time);

            QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            dealMessage(messageW, item, msg, time, QNChatMessage::User_She);
        }
        else
        {
            dealMessageTime(time);

            QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
        }
    }
}

void ChatRoom::dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type)
{
    messageW->setFixedWidth(this->width());
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setText(text, time, size, type);
    ui->listWidget->setItemWidget(item, messageW);
}

void ChatRoom::dealMessageTime(QString curMsgTime)
{
    bool isShowTime = false;
    if(ui->listWidget->count() > 0) {
        QListWidgetItem* lastItem = ui->listWidget->item(ui->listWidget->count() - 1);
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差超过一分钟
    } else {
        isShowTime = true;
    }
    if(isShowTime) {
        QNChatMessage* messageTime = new QNChatMessage(ui->listWidget->parentWidget());
        QListWidgetItem* itemTime = new QListWidgetItem(ui->listWidget);

        QSize size = QSize(this->width(), 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, QNChatMessage::User_Time);
        ui->listWidget->setItemWidget(itemTime, messageTime);
    }

}

void ChatRoom::on_sendBtn_clicked()
{
    // 处理信息并展示
    QString msg = ui->textEdit->toPlainText();
    ui->textEdit->setPlainText("");
    QString time = QString::number(QDateTime::currentDateTime().toSecsSinceEpoch()); //时间戳

//    SetConsoleOutputCP(CP_UTF8);
    qDebug() << "[chatroom] send message: " << msg;
    qDebug() << "[chatroom] send time: " << QDateTime::fromSecsSinceEpoch(time.toLongLong());
    dealMessageTime(time);

    QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
    QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
    dealMessage(messageW, item, msg+" l", time, QNChatMessage::User_Me);
    messageW->setTextSuccess();

    // 存聊天信息
    Chat* chat = new Chat(client->getClientId(), msg, 1, QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    ChatMapper *chatMapper = new ChatMapper(db);
    chatMapper->insert(chat);

    // 发送信息
    QList<Chat *> chatList;
    chatList.append(chat);

    QJsonObject message;
    ObjectToJson::addChats(message, chatList);
    ObjectToJson::addSignal(message, QString::number(CHATMSG));    //向 Client 发送信息
    QByteArray array = ObjectToJson::changeJson(message);
    emit sigSendToClient(array);
}

void ChatRoom::receiveMessage(Chat* chatMsg)
{
    QString msg = chatMsg->getChatText();
    QString time = QString::number(QDateTime::fromString(chatMsg->getChatTime()).toSecsSinceEpoch());
    if(msg != "") {
        dealMessageTime(time);

        QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
        dealMessage(messageW, item, msg, time, QNChatMessage::User_She);
    }
}

void ChatRoom::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    for(int i = 0; i < ui->listWidget->count(); i++) {
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
        QListWidgetItem* item = ui->listWidget->item(i);

        dealMessage(messageW, item, messageW->text(), messageW->time(), messageW->userType());
    }
}

void ChatRoom::connectToDB()
{
    db = QSqlDatabase::addDatabase("QODBC", "chatroom");
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

void ChatRoom::on_returnBtn_clicked()
{
    this->hide();
    ui->textEdit->clear();
    ui->listWidget->clear();
}

void ChatRoom::closeEvent(QCloseEvent *event)
{
    qDebug() << "[chatroom] close";
    emit sigUnlocked();
    event->accept();
}

