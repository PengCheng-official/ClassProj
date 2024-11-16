#include "chatroom.h"
#include "ui_chatroom.h"

ChatRoom::ChatRoom(QWidget *parent) :
    ElaWidget(parent),
    ui(new Ui::ChatRoom)
{
    ui->setupUi(this);
    setWindowButtonFlag(ElaAppBarType::StayTopButtonHint, false);
    setWindowTitle("官方客服");
    setWindowIcon(QIcon(":/Resource/chatroom_icon.png"));
    setFixedSize(450, 500);
    setMinimumSize(320, 380);
}

ChatRoom::ChatRoom(QList<Chat *> &chatList, QWidget *parent) :
    ElaWidget(parent),
    ui(new Ui::ChatRoom)
{
    ui->setupUi(this);
    setWindowButtonFlag(ElaAppBarType::StayTopButtonHint, false);
    setWindowTitle("官方客服");
    setWindowIcon(QIcon(":/Resource/chatroom_icon.png"));
    setFixedSize(450, 500);
    setMinimumSize(320, 380);

    initHistory(chatList);
}

ChatRoom::~ChatRoom()
{
    delete ui;
}

void ChatRoom::initHistory(QList<Chat *> &chatList)
{
    for (auto chat : chatList)
    {
        if (chat->getChatIsserver())
        {
            QString time = QString::number(QDateTime::fromString(chat->getChatTime()).toSecsSinceEpoch());
            dealMessageTime(time);

            QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            dealMessage(messageW, item, chat->getChatText(), time, QNChatMessage::User_She);
        }
        else
        {
            QString time = QString::number(QDateTime::fromString(chat->getChatTime()).toSecsSinceEpoch());
            dealMessageTime(time);

            QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            dealMessage(messageW, item, chat->getChatText(), time, QNChatMessage::User_Me);
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
        qDebug() << "curTime lastTime:" << curTime - lastTime;
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
    QString msg = ui->textEdit->toPlainText();
    ui->textEdit->setPlainText("");
    QString time = QString::number(QDateTime::currentDateTime().toSecsSinceEpoch()); //时间戳

    qDebug() << "[chatroom] send message: " << msg;
    qDebug() << "[chatroom] send time: " << QDateTime::fromSecsSinceEpoch(time.toLongLong());
    dealMessageTime(time);

    QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
    QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
    dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
    messageW->setTextSuccess();

    QJsonObject message;
    ObjectToJson::integrateString(message, msg);
    ObjectToJson::addSignal(message, QString::number(SENDMSG));    //Client发送信息
    QByteArray array = ObjectToJson::changeJson(message);
    emit sigSendToServer(array);
}

void ChatRoom::receiveMessage(QString msg)
{
    QString time = QString::number(QDateTime::currentDateTime().toSecsSinceEpoch()); //时间戳
    if(msg != "") {
        dealMessageTime(time);

        QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
        dealMessage(messageW, item, msg, time, QNChatMessage::User_She);
    }
}

void ChatRoom::on_returnBtn_clicked()
{
    this->hide();
    ui->textEdit->clear();
}

