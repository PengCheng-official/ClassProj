#include "chatroom.h"
#include "ui_chatroom.h"

ChatRoom::ChatRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatRoom)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    connect(ui->sendBtn, &QPushButton::clicked, [=](){
       ChatMessageSend();
       ui->textEdit->setFocus();
    });
    ui->textEdit->setFocus();
    ui->textEdit->installEventFilter(this);

    connect(ui->closeBtn,&QPushButton::clicked, [=](){
       this->close();
    });
    connect(ui->minisizeBtn,&QPushButton::clicked, [=](){
       this->showMinimized();
    });
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
    ui->textChat->clear();
    ui->textEdit->clear();
    emit returnToLogIn();
}

bool ChatRoom::eventFilter(QObject *target, QEvent *event)
{
    if(target == ui->textEdit)
    {
        if(event->type() == QEvent::KeyPress)//回车键
        {
             QKeyEvent *k = static_cast<QKeyEvent *>(event);
             if(k->key() == Qt::Key_Return)
             {
                 emit(ui->sendBtn->clicked());
                 return true;
             }
        }
    }
    return QWidget::eventFilter(target,event);
}

Client *ChatRoom::getClient() const
{
    return client;
}

void ChatRoom::setClient(Client *value)
{
    if(value != nullptr) client = value;
    else client = new Client(*value);
}

qintptr ChatRoom::getSockeDiscriptor() const
{
    return sockeDiscriptor;
}

void ChatRoom::setSockeDiscriptor(const qintptr &value)
{
    sockeDiscriptor = value;
}

void ChatRoom::mousePressEvent(QMouseEvent* event)
{
    mouse_pos = event->globalPos();
    window_pos = this->pos();
    diff_pos = mouse_pos - window_pos;
}

void ChatRoom::mouseMoveEvent(QMouseEvent* event)
{
    QPoint pos = event->globalPos();
    //this->move(pos);
    this->move(pos - diff_pos);
}
