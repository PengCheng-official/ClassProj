#include "signin.h"
#include "ui_signin.h"

SignIn::SignIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignIn)
{
    ui->setupUi(this);
    this->setFixedSize(450, 530);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->PasswordEdit->setEchoMode(QLineEdit::Password);
    ui->NameEdit->setFocus();
    ui->NameError->setReadOnly(true);
    ui->NameError->setStyleSheet("background-color: transparent; color: red;");
    ui->PasswordError->setReadOnly(true);
    ui->PasswordError->setStyleSheet("background-color: transparent; color: red;");
    ui->AllError->setReadOnly(true);
    ui->AllError->setStyleSheet("background-color: transparent; color: red;");
    connect(ui->closeBtn,&QPushButton::clicked, [=](){
       this->close();
    });
    connect(ui->minisizeBtn,&QPushButton::clicked, [=](){
       this->showMinimized();
    });
}

SignIn::~SignIn()
{
    delete ui;
}

void SignIn::on_createBtn_clicked()
{
    qDebug() << "[signin] trying to signin";
    ui->AllError->clear();
    ui->NameError->clear();
    ui->PasswordError->clear();
    client = new Client;
    if (ui->NameEdit->text() == "") {
        ui->NameError->setText("账号名不能为空!");
        return;
    }
    else client->setClientName(ui->NameEdit->text());
    if (ui->PasswordEdit->text() == "") {
        ui->PasswordError->setText("密码不能为空!");
        return;
    }
    else client->setClientPwd(ui->PasswordEdit->text());
    if(ui->PhoneNumEdit->text() != "") {
        client->setClientPhone(ui->PhoneNumEdit->text());
    }
    if (ui->EmailEdit->text() != "") {
        client->setClientEmail(ui->EmailEdit->text());
    }
    if (ui->AddrEdit->text() != "") {
        client->setClientAddr(ui->AddrEdit->text());
    }
    QList<Client*> clientList;
    clientList.append(client);
    QJsonObject message;
    ObjectToJson::integrateClientList(message, clientList);
    ObjectToJson::addSignal(message, QString::number(SIGNIN));
    QByteArray array =ObjectToJson::changeJson(message);
    emit sendToSignIn(array);
    qDebug() << "[signin] send to sign in";
}

void SignIn::signInSuccess(Client *cClient)
{
    qDebug() << "[signin] sign in success";
    client = cClient;
    this->hide();
    ui->NameEdit->clear();
    ui->PasswordEdit->clear();
    ui->PhoneNumEdit->clear();
    ui->EmailEdit->clear();
    ui->AddrEdit->clear();
    emit signInSuccessToLogIn(client);
}

void SignIn::signInFail()
{
    qDebug() << "[signin] sign in fail";
    ui->PasswordEdit->clear();
    ui->AllError->setText("已存在该账号名！请尝试其他。");
}

void SignIn::on_returnLogBtn_clicked()
{
    this->hide();
    emit returnToLogIn();
}

void SignIn::mousePressEvent(QMouseEvent *event)
{
    int Backwidget = ui->backwidget->height();
    if(event->y() <Backwidget)
    {
        last = event->globalPos(); //获取到按压的位置
    }
}

void SignIn::mouseMoveEvent(QMouseEvent *event)
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

void SignIn::mouseReleaseEvent(QMouseEvent *event)
{
    int Backwidget = ui->backwidget->height();
    if(event->y() <Backwidget)
    {
        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        this->move(this->x()+dx,this->y()+dy);
    }
}
