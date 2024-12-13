#include "homepage.h"

HomePage::HomePage(Client *cClient, QWidget* parent)
    : ElaScrollPage(parent)
    , client(cClient)
{
    _promotionView = new ElaPromotionView(this);
    _promotionView->setFixedHeight(420);

    ElaPromotionCard* Card1 = new ElaPromotionCard(this);
    Card1->setCardPixmap(QPixmap(":/Resource/card5.jpeg"));

    ElaPromotionCard* Card2 = new ElaPromotionCard(this);
    Card2->setCardPixmap(QPixmap(":/Resource/card2.jpg"));
    Card2->setCardTitle("正義");
    Card2->setPromotionTitle("欢迎购物~");
    Card2->setTitle("果实商店");
    Card2->setSubTitle("世にくんりん君臨するせいぎ正義です");

    ElaPromotionCard* Card3 = new ElaPromotionCard(this);
    Card3->setCardPixmap(QPixmap(":/Resource/card3.jpg"));
    Card3->setCardTitle("海賊");
    Card3->setPromotionTitle("欢迎购物~");
    Card3->setTitle("恶魔商店");
    Card3->setSubTitle("オレは海贼王になる男だ!");

    ElaPromotionCard* Card4 = new ElaPromotionCard(this);
    Card4->setCardPixmap(QPixmap(":/Resource/card4.jpg"));

    _promotionView->appendPromotionCard(Card1);
    _promotionView->appendPromotionCard(Card2);
    _promotionView->appendPromotionCard(Card3);
    _promotionView->appendPromotionCard(Card4);
    _promotionView->setIsAutoScroll(true);

    centralWidget = new QWidget(this);
    setTitleVisible(false);
    centerLayout = new QVBoxLayout(centralWidget);
    centerLayout->setContentsMargins(0, 0, 0, 0);
    centerLayout->addWidget(_promotionView);
    centerLayout->addStretch();

    mainLayout = new QHBoxLayout();
    productArea1 = new ElaScrollPageArea(centralWidget);
    productArea1->setFixedHeight(160);
    productLayout1 = new QHBoxLayout(productArea1);

    image1 = new QLabel(productArea1);
    image1->setFixedSize(145, 145);
    image1->setPixmap(QPixmap(client->getClientImage()));
    image1->setAlignment(Qt::AlignCenter);  // 居中显示图片
    image1->setScaledContents(true);

    name1 = new ElaText(productArea1);
    name1->setFixedWidth(180);
    name1->setText(client->getClientName());
    name1->setTextStyle(ElaTextType::Title);

    price1 = new ElaText(productArea1);
    price1->setText("￥" + QString::number(client->getClientId()));
    price1->setStyleSheet("color: rgb(252, 106, 35); font-weight: bold;");
    price1->setTextStyle(ElaTextType::Subtitle);

    add1 = new ElaPushButton("加入购物车", productArea1);
    add1->setFixedSize(100, 40);
    add1->setLightDefaultColor(QColor(252, 90, 31));
    add1->setLightHoverColor(QColor(255, 107, 48));
    add1->setLightPressColor(QColor(232, 50, 11));
    add1->setLightTextColor(Qt::white);
    // TODO: 加入购物车

    textLayout1 = new QVBoxLayout();
    textLayout1->addWidget(name1);
    textLayout1->addSpacing(5);
    textLayout1->addWidget(price1);
    textLayout1->addSpacing(5);
    textLayout1->addWidget(add1);
    textLayout1->addStretch();

    productLayout1->addStretch();
    productLayout1->addWidget(image1);
    productLayout1->addStretch();
    productLayout1->addLayout(textLayout1);
    productLayout1->addStretch();
    mainLayout->addStretch();
    mainLayout->addWidget(productArea1);

    productArea2 = new ElaScrollPageArea(centralWidget);
    productArea2->setFixedHeight(160);
    productLayout2 = new QHBoxLayout(productArea2);

    image2 = new QLabel(productArea2);
    image2->setPixmap(QPixmap(client->getClientImage()));
    image2->setAlignment(Qt::AlignCenter);  // 居中显示图片
    image2->setScaledContents(true);
    image2->setFixedSize(145, 145);

    name2 = new ElaText(productArea2);
    name2->setText(client->getClientName());
    name2->setTextStyle(ElaTextType::Title);
    name2->setFixedWidth(180);

    price2 = new ElaText(productArea2);
    price2->setText("￥" + QString::number(client->getClientId()));
    price2->setStyleSheet("color: rgb(252, 106, 35); font-weight: bold;");
    price2->setTextStyle(ElaTextType::Subtitle);

    add2 = new ElaPushButton("加入购物车", productArea2);
    add2->setFixedSize(100, 40);
    add2->setLightDefaultColor(QColor(252, 90, 31));
    add2->setLightHoverColor(QColor(255, 107, 48));
    add2->setLightPressColor(QColor(232, 50, 11));
    add2->setLightTextColor(Qt::white);
    // TODO: 加入购物车

    textLayout2 = new QVBoxLayout();
    textLayout2->addWidget(name2);
    textLayout2->addSpacing(5);
    textLayout2->addWidget(price2);
    textLayout2->addSpacing(5);
    textLayout2->addWidget(add2);
    textLayout2->addStretch();

    productLayout2->addStretch();
    productLayout2->addWidget(image2);
    productLayout2->addStretch();
    productLayout2->addLayout(textLayout2);
    productLayout2->addStretch();
    mainLayout->addWidget(productArea2);

    changeBtn = new ElaPushButton("换\n一\n换", centralWidget);
    changeBtn->setFixedSize(30, 80);
    changeBtn->setLightDefaultColor(ElaThemeColor(ElaThemeType::Light, PrimaryNormal));
    changeBtn->setLightHoverColor(ElaThemeColor(ElaThemeType::Light, PrimaryHover));
    changeBtn->setLightPressColor(ElaThemeColor(ElaThemeType::Light, PrimaryPress));
    changeBtn->setLightTextColor(Qt::white);
    connect(changeBtn, &QPushButton::clicked, [=](){
        QJsonObject message;
        ObjectToJson::addSignal(message, QString::number(REQUESTHOME));
        QByteArray array = ObjectToJson::changeJson(message);
        emit sigSendToServer(array);
    });

    mainLayout->addWidget(changeBtn);
    mainLayout->addStretch();

    centerLayout->addLayout(mainLayout);
    centerLayout->addStretch();
    addCentralWidget(centralWidget, true, true, 0);
}

HomePage::~HomePage()
{
}

void HomePage::refreshPage(QList<Product *> proList)
{
    qDebug() << "[homePage] product:" << proList[0]->getProductId();
    image1->setPixmap(QPixmap(proList[0]->getProductImage()));
    name1->setText(proList[0]->getProductName());
    price1->setText("￥" + QString::number(proList[0]->getProductPrice()));

    qDebug() << "[homePage] product:" << proList[1]->getProductId();
    image2->setPixmap(QPixmap(proList[1]->getProductImage()));
    name2->setText(proList[1]->getProductName());
    price2->setText("￥" + QString::number(proList[1]->getProductPrice()));
}
