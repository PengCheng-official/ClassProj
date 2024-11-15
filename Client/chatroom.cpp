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
    setMaximumSize(600, 1000);

    connect(ui->sendBtn, &QPushButton::clicked, [=](){
       ChatMessageSend();
       ui->textEdit->setFocus();
    });
    ui->textEdit->setFocus();
}

ChatRoom::~ChatRoom()
{
    delete ui;
}

void ChatRoom::ChatMessageSend()
{
    qDebug() << "chatroom: send message";
}

void ChatRoom::receiveMessage()
{

}

void ChatRoom::on_returnBtn_clicked()
{
    this->hide();
    ui->textEdit->clear();
    emit sigReturnToLogIn();
}
