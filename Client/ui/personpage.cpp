#include "personpage.h"


PersonPage::PersonPage(Client *cClient, QWidget *parent)
    : ElaScrollPage(parent)
    , client(cClient)
{
    setWindowTitle("我的信息");
    centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("我的信息");
    addCentralWidget(centralWidget, true, true, 0);

    //主Layout 初始化
    QVBoxLayout *centerLayout = new QVBoxLayout(centralWidget);
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
    nameEdit->setFixedSize(270, 36);
    nameEdit->setStyleSheet("font-weight: bold; font-size: 16px; color: black;}");
    nameEdit->setPlaceholderText("    " + client->getClientName());

    //性别按钮 初始化
    ElaText *genderText = new ElaText("性别:", 18, this);
    maleBtn = new ElaToggleButton("男", this);
    femaleBtn = new ElaToggleButton("女", this);
    unknownBtn = new ElaToggleButton("未知", this);
    QHBoxLayout *genderLayout = new QHBoxLayout();
    genderLayout->addStretch();
    genderLayout->addWidget(genderText);
    genderLayout->addSpacing(25);
    genderLayout->addWidget(maleBtn);
    genderLayout->addWidget(femaleBtn);
    genderLayout->addWidget(unknownBtn);
    genderLayout->addStretch();
    if (client->getClientGender() == "男")
        maleBtn->setIsToggled(true);
    else if (client->getClientGender() == "女")
        femaleBtn->setIsToggled(true);
    else
        unknownBtn->setIsToggled(true);

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

    //地址 初始化
    ElaText *addrText = new ElaText("地址:", 18, this);
    addrEdit = new ElaLineEdit(this);
    addrEdit->setFixedSize(270, 36);
    addrEdit->setStyleSheet("font-weight: bold; font-size: 16px; color: black; ");
    addrEdit->setPlaceholderText("    " + client->getClientAddr());

    //手机号 初始化
    ElaText *phoneText = new ElaText("手机:", 18, this);
    phoneEdit = new ElaLineEdit(this);
    phoneEdit->setFixedSize(270, 36);
    phoneEdit->setStyleSheet("font-weight: bold; font-size: 16px; color: black; ");
    phoneEdit->setPlaceholderText("    " + client->getClientPhone());

    //邮箱 初始化
    ElaText *emailText = new ElaText("邮箱:", 18, this);
    emailEdit = new ElaLineEdit(this);
    emailEdit->setFixedSize(270, 36);
    emailEdit->setStyleSheet("font-weight: bold; font-size: 16px; color: black; ");
    emailEdit->setPlaceholderText("    " + client->getClientEmail());

    //确定按钮 初始化
    confirmBtn = new ElaMessageButton("确定修改", this);
//    confirmBtn->setBarTitle("修改失败");
//    confirmBtn->setBarText("已存在相同账号");
//    confirmBtn->setMessageMode(ElaMessageBarType::Error);
//    confirmBtn->setPositionPolicy(ElaMessageBarType::BottomRight);
    confirmBtn->setFixedSize(100, 40);
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addSpacing(240);
    btnLayout->addWidget(confirmBtn);
    btnLayout->addStretch();

    //连接确定的点击槽函数
    connect(confirmBtn, &QPushButton::clicked, this, &PersonPage::onConFirmBtnClicked);

    //主Layout添加
    centerLayout->addSpacing(25);
    centerLayout->addLayout(midHLayout2(nameText, nameEdit));
    centerLayout->addSpacing(25);
    centerLayout->addLayout(genderLayout);
    centerLayout->addSpacing(25);
    centerLayout->addLayout(midHLayout2(addrText, addrEdit));
    centerLayout->addSpacing(25);
    centerLayout->addLayout(midHLayout2(phoneText, phoneEdit));
    centerLayout->addSpacing(25);
    centerLayout->addLayout(midHLayout2(emailText, emailEdit));
    centerLayout->addSpacing(25);
    centerLayout->addLayout(btnLayout);
    centerLayout->addStretch();
    qDebug() << nameEdit->text();
}

PersonPage::~PersonPage()
{

}

void PersonPage::onConFirmBtnClicked()
{
    Client *cClient = new Client;
    if (nameEdit->text() == "")
    {
        //没有修改用户名
    }
    else
    {
        //修改了用户名
    }
}
