#include "personpage.h"


PersonPage::PersonPage(Client *cClient, QWidget *parent)
    : BasePage(cClient, parent)
{
    setWindowTitle("我的信息");
    centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("我的信息");
    addCentralWidget(centralWidget, true, true, 0);

    //主Layout 初始化
    centerLayout = new QVBoxLayout(centralWidget);
    //复用居中的 水平Layout
    auto midHLayout2 = [](QWidget *widget1, QWidget *widget2) -> QHBoxLayout* {
        QHBoxLayout *layout = new QHBoxLayout;
        layout->addStretch();
        layout->addWidget(widget1);
        layout->addSpacing(10);
        layout->addWidget(widget2);
        layout->addStretch();
        return layout;
    };

    //用户名 初始化
    ElaText *nameText = new ElaText("姓名:", 18, this);
    nameEdit = new ElaLineEdit(this);
    nameEdit->setFixedSize(270, 40);
    nameEdit->setStyleSheet("font-weight: bold; font-size: 16px; color: black; ");

    //头像 初始化
    ElaText *imageText = new ElaText("头像:", 18, this);
    imageBtn = new ElaPushButton("选择图片", this);
    imageBtn->setFixedSize(100, 40);
    QHBoxLayout *imageLayout = new QHBoxLayout();
    imageLayout->addStretch();
    imageLayout->addWidget(imageText);
    imageLayout->addSpacing(11);
    imageLayout->addWidget(imageBtn);
    imageLayout->addSpacing(175);
    imageLayout->addStretch();
    connect(imageBtn, &ElaPushButton::clicked, [=](){
        imagePath = QFileDialog::getOpenFileName(
                    this,
                    tr("Select Image"),
                    "C:\\Users\\PC\\Desktop\\ClassPro\\MyPro\\Client\\include\\Resource",
                    tr("Image Files (*.png *.jpg *.bmp)"
                       ));
        qDebug() << "[personPage] select image: " << imagePath;
    });

    //性别按钮 初始化
    ElaText *genderText = new ElaText("性别:", 18, this);
    maleBtn = new ElaToggleButton("男", this);
    femaleBtn = new ElaToggleButton("女", this);
    unknownBtn = new ElaToggleButton("未知", this);
    QHBoxLayout *genderLayout = new QHBoxLayout();
    genderLayout->addStretch();
    genderLayout->addWidget(genderText);
    genderLayout->addSpacing(22);
    genderLayout->addWidget(maleBtn);
    genderLayout->addWidget(femaleBtn);
    genderLayout->addWidget(unknownBtn);
    genderLayout->addSpacing(5);
    genderLayout->addStretch();

    //只有一个按钮可以被选中
    connect(maleBtn, &ElaToggleButton::toggled, [=](bool check){
        if (check) {
            femaleBtn->setIsToggled(false);
            unknownBtn->setIsToggled(false);
        }
    });
    connect(femaleBtn, &ElaToggleButton::toggled, [=](bool check){
        if (check) {
            maleBtn->setIsToggled(false);
            unknownBtn->setIsToggled(false);
        }
    });
    connect(unknownBtn, &ElaToggleButton::toggled, [=](bool check){
        if (check) {
            femaleBtn->setIsToggled(false);
            maleBtn->setIsToggled(false);
        }
    });

    //密码初始化
    ElaText *prePasswordText = new ElaText("原密码:", 18, this);
    prePasswordEdit = new ElaLineEdit(this);
    prePasswordEdit->setFixedSize(270, 40);
    prePasswordEdit->setStyleSheet("font-size: 16px; color: black; ");
    prePasswordEdit->setEchoMode(QLineEdit::Password);
    ElaText *newPasswordText = new ElaText("新密码:", 18, this);
    newPasswordEdit = new ElaLineEdit(this);
    newPasswordEdit->setFixedSize(270, 40);
    newPasswordEdit->setStyleSheet("font-size: 16px; color: black; ");
    newPasswordEdit->setEchoMode(QLineEdit::Password);


    //地址 初始化
    ElaText *addrText = new ElaText("地址:", 18, this);
    addrEdit = new ElaLineEdit(this);
    addrEdit->setFixedSize(270, 36);
    addrEdit->setStyleSheet("font-size: 16px; color: black; ");

    //手机号 初始化
    ElaText *phoneText = new ElaText("手机:", 18, this);
    phoneEdit = new ElaLineEdit(this);
    phoneEdit->setFixedSize(270, 36);
    phoneEdit->setStyleSheet("font-size: 16px; color: black; ");

    //邮箱 初始化
    ElaText *emailText = new ElaText("邮箱:", 18, this);
    emailEdit = new ElaLineEdit(this);
    emailEdit->setFixedSize(270, 36);
    emailEdit->setStyleSheet("font-size: 16px; color: black; ");

    //确定按钮 初始化
    confirmBtn = new ElaMessageButton("确定修改", this);
    confirmBtn->setFixedSize(120, 50);
    confirmBtn->setPositionPolicy(ElaMessageBarType::BottomRight);

    //连接确定的点击槽函数
    connect(confirmBtn, &QPushButton::clicked, this, &PersonPage::onConFirmBtnClicked);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addSpacing(240);
    btnLayout->addWidget(confirmBtn);
    btnLayout->addStretch();


    //主Layout添加
    centerLayout->addSpacing(25);
    centerLayout->addLayout(midHLayout2(nameText, nameEdit));
    centerLayout->addSpacing(25);
    centerLayout->addLayout(imageLayout);
    centerLayout->addSpacing(25);
    centerLayout->addLayout(genderLayout);
    centerLayout->addSpacing(25);
    centerLayout->addLayout(midHLayout2(prePasswordText, prePasswordEdit));
    centerLayout->addSpacing(25);
    centerLayout->addLayout(midHLayout2(newPasswordText, newPasswordEdit));
    centerLayout->addSpacing(25);
    centerLayout->addLayout(midHLayout2(addrText, addrEdit));
    centerLayout->addSpacing(25);
    centerLayout->addLayout(midHLayout2(phoneText, phoneEdit));
    centerLayout->addSpacing(25);
    centerLayout->addLayout(midHLayout2(emailText, emailEdit));
    centerLayout->addSpacing(25);
    centerLayout->addLayout(btnLayout);
    centerLayout->addStretch();

    initPage(cClient);
}

PersonPage::~PersonPage()
{
}

void PersonPage::initPage(Client *cClient)
{
    nameEdit->setText("");
    addrEdit->setText("");
    phoneEdit->setText("");
    emailEdit->setText("");

    client = cClient;
    nameEdit->setPlaceholderText("    " + client->getClientName());
    if (client->getClientGender() == "男")
        maleBtn->setIsToggled(true);
    else if (client->getClientGender() == "女")
        femaleBtn->setIsToggled(true);
    else
        unknownBtn->setIsToggled(true);

    prePasswordEdit->setPlaceholderText("    请输入你的原密码");
    newPasswordEdit->setPlaceholderText("    请输入你的新密码");

    if (client->getClientAddr() == "") {
        addrEdit->setPlaceholderText("    请输入你的地址");
    } else {
        addrEdit->setPlaceholderText("    " + client->getClientAddr());
    }

    if (client->getClientPhone() == "") {
        phoneEdit->setPlaceholderText("    请输入你的手机号");
    } else {
        phoneEdit->setPlaceholderText("    " + client->getClientPhone());
    }

    if (client->getClientEmail() == "") {
        phoneEdit->setPlaceholderText("    请输入你的邮箱");
    } else {
        emailEdit->setPlaceholderText("    " + client->getClientEmail());
    }
}

void PersonPage::showMessageWindow(bool success)
{
    prePasswordEdit->setText("");
    newPasswordEdit->setText("");
    if (success)
    {
        client = nClient;
        emit sigClientChanged(nClient);
        initPage(client);
    }
//    confirmBtn->connectShow();
}

void PersonPage::onConFirmBtnClicked()
{
    QList<QString> stringList;
    if (nClient != nullptr) {
        nClient = client;
    }
    else nClient = new Client(*client);
    if (nameEdit->text() != "")
    {
        nClient->setClientName(nameEdit->text());
    }
    if (imagePath != "") {
        nClient->setClientImage(imagePath);
    }
    if (maleBtn->getIsToggled()) {
        nClient->setClientGender("男");
    }
    else if (femaleBtn->getIsToggled()) {
        nClient->setClientGender("女");
    }
    else {
        nClient->setClientGender("未知");
    }
    if (prePasswordEdit->text() != "")
    {
        if (newPasswordEdit->text() == "")
        {
            confirmBtn->setBarTitle("修改失败");
            confirmBtn->setBarText("请输入新密码");
            confirmBtn->setMessageMode(ElaMessageBarType::Error);
            showMessageWindow(false);
            confirmBtn->connectShow();
            return;
        }
        nClient->setClientPwd(newPasswordEdit->text());
        stringList.append(prePasswordEdit->text());
    }
    if (addrEdit->text() != "") {
        nClient->setClientAddr(addrEdit->text());
    }
    if (phoneEdit->text() != "") {
        nClient->setClientPhone(phoneEdit->text());
    }
    if (emailEdit->text() != "") {
        nClient->setClientEmail(emailEdit->text());
    }

    QList<Client*> clientList;
    clientList.append(nClient);
    QJsonObject message;
    ObjectToJson::addClients(message, clientList);
    ObjectToJson::addStrings(message, stringList);  //输入的原密码
    ObjectToJson::addSignal(message, QString::number(PERSONCHANGE));    //个人信息修改请求
    QByteArray array = ObjectToJson::changeJson(message);
    emit sigSendToServer(array);

    QThread::msleep(100);
}
