#include "login.h"
#include "ui_login.h"

LogIn::LogIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);
    this->setFixedSize(450, 530);
    ui->lineName->setFocus();
    connect(ui->lineName,&QLineEdit::textChanged,[=](){
       ui->wrongEdit2->setText("");
    });
    ui->linePassWord->setEchoMode(QLineEdit::Password);
    ui->wrongEdit2->setReadOnly(true);
    ui->wrongEdit2->setStyleSheet("background-color: transparent; color: red;");

    this->setWindowFlags(Qt::FramelessWindowHint);
//    this->setAttribute(Qt::WA_TranslucentBackground);
    connect(ui->closeBtn,&QPushButton::clicked,[=](){
       this->close();
    });
    connect(ui->minisizeBtn,&QPushButton::clicked,[=](){
       this->showMinimized();
    });
}

LogIn::~LogIn()
{
    delete ui;
}

void LogIn::on_loginbtn_clicked()
{
    qDebug() << "[login] trying to login ...";
    Client* client = new Client;
    if (ui->lineName->text() == "") {
        ui->wrongEdit2->setText("用户名不能为空!");
        return;
    }
    else client->setClientName(ui->lineName->text());
    if (ui->linePassWord->text() == "") {
        ui->wrongEdit2->setText("密码不能为空!");
        return;
    }
    else client->setClientPwd(ui->linePassWord->text());

    QList<Client*> clientList;
    clientList.append(client);
    QJsonObject message;
    ObjectToJson::integrateClientList(message, clientList);
    ObjectToJson::addSignal(message, QString::number(LOGIN));    //登录请求
    QByteArray array = ObjectToJson::changeJson(message);
    emit sigSendToLogIn(array);
    qDebug() << "[login] send to login";
}

void LogIn::logInSuccess(Client* client)
{
    qDebug() << "[login] log in success";
    this->hide();
    ui->lineName->clear();
    ui->linePassWord->clear();
    emit sigBackToMain(client);
}

void LogIn::logInFail()
{
    qDebug() << "[login] log in fail";
    ui->wrongEdit2->setText("账号或密码错误！");
}

void LogIn::signInSuccess(Client *cClient)
{
    qDebug() << "[login] sign in success";
    ui->lineName->setText(cClient->getClientName());
    ui->linePassWord->clear();
    this->show();
}

void LogIn::unconnected()
{
    ui->wrongEdit2->setText("抱歉！服务器连接失败。");
    ui->loginbtn->setEnabled(false);
    ui->signBtn->setEnabled(false);
    ui->chatBtn->setEnabled(false);
}

void LogIn::on_signBtn_clicked()
{
    this->hide();
    emit sigForwardToSignIn();
}

void LogIn::on_chatBtn_clicked()
{
    this->hide();
    emit sigForwardToChatRoom();
}

void LogIn::on_forgetBtn_clicked()
{
    ui->lineName->clear();
    ui->linePassWord->clear();
    ui->lineName->setFocus();
}

void LogIn::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
//        QPainter painter(this);
//        painter.fillRect(this->rect(), QColor(255, 255, 255, 255));  //QColor最后一个参数80代表背景的透明度

}


void LogIn::mousePressEvent(QMouseEvent *event)
{
    int Backwidget = ui->backwidget->height();
    if(event->y() <Backwidget)
    {
        last = event->globalPos(); //获取到按压的位置
    }
}

void LogIn::mouseMoveEvent(QMouseEvent *event)
{
    int Backwidget = ui->backwidget->height();
    if(event->y() <Backwidget)
    {
        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        last = event->globalPos();
        this->move(this->x()+dx,this->y()+dy);
    }
}

void LogIn::mouseReleaseEvent(QMouseEvent *event)
{
    int Backwidget = ui->backwidget->height();
    if(event->y() <Backwidget)
    {
        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        this->move(this->x()+dx,this->y()+dy);
    }
}
