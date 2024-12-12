#include "productpage.h"

ProductPage::ProductPage(QWidget* parent)
    : ElaScrollPage(parent)
{
    setWindowTitle("修改商品信息");
    centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("修改商品信息");
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

    //商品名称 初始化
    ElaText *nameText = new ElaText("名称:", 18, this);
    nameEdit = new ElaLineEdit(this);
    nameEdit->setFixedSize(270, 40);
    nameEdit->setStyleSheet("font-size: 16px; color: black; ");

    //图片 初始化
    ElaText *imageText = new ElaText("图片:", 18, this);
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

    //价格 初始化
    ElaText *priceText = new ElaText("价格:", 18, this);
    priceEdit = new ElaLineEdit(this);
    priceEdit->setFixedSize(270, 40);
    priceEdit->setStyleSheet("font-size: 16px; color: black; ");

    //库存 初始化
    ElaText *numText = new ElaText("库存:", 18, this);
    numEdit = new ElaLineEdit(this);
    numEdit->setFixedSize(270, 36);
    numEdit->setStyleSheet("font-size: 16px; color: black; ");

    //策略 初始化
    ElaText *strategyText = new ElaText("促销:", 18, this);
    strategyBox = new ElaComboBox(this);
    QStringList strategyList = {
        "无",
        "直接折扣",
        "满减活动",
        "买赠活动",
        "限时促销"
    };
    strategyBox->addItems(strategyList);
    strategyBox->setFixedWidth(140);
    strategyBox->setStyleSheet("font-size: 14px;");
    connect(strategyBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                    this, &ProductPage::onCurrentIndexChanged);
    //    strategyBox->setCurrentIndex(product->getStrategy() - '0');
    //    product->setStrategy(strategyBox->currentlndex())
    QHBoxLayout *strategyLayout = new QHBoxLayout();
    strategyLayout->addStretch();
    strategyLayout->addWidget(strategyText);
    strategyLayout->addSpacing(11);
    strategyLayout->addWidget(strategyBox);
    strategyLayout->addSpacing(135);
    strategyLayout->addStretch();

    // 活动 初始化
    ElaText *activityText = new ElaText("活动:", 18, this);
    _edit1 = new ElaLineEdit(this);
    _edit2 = new ElaLineEdit(this);
    _edit1->setFixedSize(40, 36);
    _edit1->setClearButtonEnabled(false);
    _edit2->setFixedSize(40, 36);
    _edit2->setClearButtonEnabled(false);
    activityLayouts[0] = new QHBoxLayout();
    activityLayouts[1] = new QHBoxLayout();
    activityLayouts[2] = new QHBoxLayout();
    activityLayouts[3] = new QHBoxLayout();
    activityLayouts[4] = new QHBoxLayout();
    createActivityLayout(activityText);

    //简介 初始化 ElaPlainTextEdit
    ElaText *aboutText = new ElaText("简介:", 18, this);
    aboutEdit = new ElaPlainTextEdit(this);
    aboutEdit->setStyleSheet("font-size: 16px;");
//    aboutEdit->setPlainText(product->getProductAbout());

    //确定按钮 初始化
    confirmBtn = new ElaPushButton(this);
    confirmBtn->setFixedSize(120, 50);
    confirmBtn->setText("确认修改");

    //连接确定的点击槽函数
    connect(confirmBtn, &QPushButton::clicked, this, &ProductPage::onConFirmBtnClicked);

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
    centerLayout->addLayout(midHLayout2(priceText, priceEdit));
    centerLayout->addSpacing(25);
    centerLayout->addLayout(midHLayout2(numText, numEdit));
    centerLayout->addSpacing(25);
    centerLayout->addLayout(strategyLayout);
    centerLayout->addSpacing(25);
    centerLayout->addLayout(activityLayouts[0]);
    centerLayout->addSpacing(25);
    centerLayout->addLayout(midHLayout2(aboutText, aboutEdit));
    centerLayout->addSpacing(25);
    centerLayout->addLayout(btnLayout);
    centerLayout->addStretch();

    initPage();
}

ProductPage::~ProductPage()
{
}

void ProductPage::initPage(Product *product)
{
    if (product == nullptr)
    {
        nameEdit->setPlaceholderText("  输入商品名称");
        priceEdit->setPlaceholderText("  输入商品价格");
        numEdit->setPlaceholderText("  输入商品库存量");
        strategyBox->setCurrentIndex(0);
        _edit1->setText("10");
        aboutEdit->setPlaceholderText("  输入商品简介");
    }
    else
    {
        nameEdit->setPlaceholderText("  " + product->getProductName());
        priceEdit->setPlaceholderText("  " + QString::number(product->getProductPrice()));
        numEdit->setPlaceholderText("  " + QString::number(product->getProductNum()));
        strategyBox->setCurrentIndex(product->getStrategy());
        onCurrentIndexChanged(product->getStrategy());
        _edit1->setText(QString::number(product->getStrategy1()));
        _edit1->setText(QString::number(product->getStrategy2()));
        aboutEdit->setPlaceholderText(product->getProductAbout());
    }
}

void ProductPage::onCurrentIndexChanged(int cur)
{
    // 11
    centerLayout->removeItem(centerLayout->itemAt(11));
    centerLayout->insertLayout(11, activityLayouts[cur]);

    switch (cur) {
    case 0:
        _edit1->hide();
        _edit2->hide();
        _text1->show();
        _text2->hide();
        _text3->hide();
        _text4->hide();
        _text5->hide();
        _text6->hide();
        _text7->hide();
        break;
    case 1:
        _edit1->show();
        _edit2->hide();
        _text1->hide();
        _text2->show();
        _text3->hide();
        _text4->hide();
        _text5->hide();
        _text6->hide();
        _text7->hide();
        break;
    case 2:
        _edit1->show();
        _edit2->show();
        _text1->hide();
        _text2->hide();
        _text3->show();
        _text4->show();
        _text5->hide();
        _text6->hide();
        _text7->hide();
        break;
    case 3:
        _edit1->show();
        _edit2->show();
        _text1->hide();
        _text2->hide();
        _text3->show();
        _text4->hide();
        _text5->show();
        _text6->hide();
        _text7->hide();
        break;
    case 4:
        _edit1->show();
        _edit2->show();
        _text1->hide();
        _text2->show();
        _text3->hide();
        _text4->hide();
        _text5->hide();
        _text6->show();
        _text7->show();
        break;
    default:
        _edit1->hide();
        _edit2->hide();
        _text1->hide();
        _text2->hide();
        _text3->hide();
        _text4->hide();
        _text5->hide();
        _text6->hide();
        _text7->hide();
        break;
    }
}

void ProductPage::createActivityLayout(ElaText *activityText)
{
    activityLayouts[0]->addStretch();
    activityLayouts[0]->addWidget(activityText);
    activityLayouts[0]->addSpacing(11);
    _text1 = new ElaText("不参加活动", 17, this);
    _text1->setFixedSize(100, 36);
    activityLayouts[0]->addWidget(_text1);
    activityLayouts[0]->addSpacing(170);
    activityLayouts[0]->addStretch();

    activityLayouts[1]->addStretch();
    activityLayouts[1]->addWidget(activityText);
    activityLayouts[1]->addSpacing(11);
    _text2 = new ElaText("折", 17, this);
    _text2->setFixedSize(30, 36);
    activityLayouts[1]->addWidget(_edit1);
    activityLayouts[1]->addWidget(_text2);
    activityLayouts[1]->addSpacing(195);
    activityLayouts[1]->addStretch();

    activityLayouts[2]->addStretch();
    activityLayouts[2]->addWidget(activityText);
    activityLayouts[2]->addSpacing(11);
    _text3 = new ElaText("满", 17, this);
    _text4 = new ElaText("减", 17, this);
    _text3->setFixedSize(30, 36);
    _text4->setFixedSize(30, 36);
    activityLayouts[2]->addWidget(_text3);
    activityLayouts[2]->addWidget(_edit1);
    activityLayouts[2]->addWidget(_text4);
    activityLayouts[2]->addWidget(_edit2);
    activityLayouts[2]->addSpacing(110);
    activityLayouts[2]->addStretch();

    activityLayouts[3]->addStretch();
    activityLayouts[3]->addWidget(activityText);
    activityLayouts[3]->addSpacing(11);
    _text5 = new ElaText("赠", 17, this);
    _text5->setFixedSize(30, 36);
    activityLayouts[3]->addWidget(_text3);
    activityLayouts[3]->addWidget(_edit1);
    activityLayouts[3]->addWidget(_text5);
    activityLayouts[3]->addWidget(_edit2);
    activityLayouts[3]->addSpacing(110);
    activityLayouts[3]->addStretch();

    activityLayouts[4]->addStretch();
    activityLayouts[4]->addWidget(activityText);
    activityLayouts[4]->addSpacing(11);
    _text6 = new ElaText("限时", 17, this);
    _text7 = new ElaText("秒", 17, this);
    _text6->setFixedSize(40, 36);
    _text7->setFixedSize(30, 36);
    _edit1->setFixedSize(40, 36);
    _edit1->setClearButtonEnabled(false);
    _edit2->setFixedSize(40, 36);
    _edit2->setClearButtonEnabled(false);
    activityLayouts[4]->addWidget(_text6);
    activityLayouts[4]->addWidget(_edit1);
    activityLayouts[4]->addWidget(_text7);
    activityLayouts[4]->addWidget(_edit2);
    activityLayouts[4]->addWidget(_text2);
    activityLayouts[4]->addSpacing(65);
    activityLayouts[4]->addStretch();

    _edit1->hide();
    _edit2->hide();
    _text1->show();
    _text2->hide();
    _text3->hide();
    _text4->hide();
    _text5->hide();
    _text6->hide();
    _text7->hide();
}
