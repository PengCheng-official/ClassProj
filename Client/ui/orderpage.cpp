#include "orderpage.h"

OrderPage::OrderPage(Client *cClient, QList<QPair<Product *, int> > selectList, QWidget* parent)
    : ElaWidget(parent)
    , client(cClient)
{
    // 初始化时不建立 order，没有申请 order_id
    setWindowTitle("订单状态：未支付");
    setWindowIcon(QIcon(":/Resource/order_icon.png"));
    this->setFixedHeight(660);
    this->setIsFixedSize(true);
    setWindowModality(Qt::ApplicationModal);
    setWindowButtonFlags(ElaAppBarType::CloseButtonHint);
    totPrice = deltaPrice = 0;

    // 支付实现
    payDialog = new ElaContentDialog(this);
    payDialog->setTitleText("移动支付中...");
    payDialog->setSubTitleText("确定要支付吗？");
    payDialog->setRightButtonText("确定");
    payDialog->setMiddleButtonText("取消");
    payDialog->isLeftButtonVisible(false);
    connect(payDialog, &ElaContentDialog::rightButtonClicked, this, &OrderPage::onRightBtnClicked);
    connect(payDialog, &ElaContentDialog::middleButtonClicked, this, &OrderPage::onMiddleBtnClicked);

    centerLayout = new QVBoxLayout(this);
    for (auto [product, num] : selectList)
    {
        ElaScrollPageArea* productArea = new ElaScrollPageArea(this);
        productArea->setFixedHeight(160);
        QHBoxLayout* productLayout = new QHBoxLayout(productArea);

        QLabel *image = new QLabel(productArea);
        image->setPixmap(QPixmap(product->getProductImage()));
        image->setAlignment(Qt::AlignCenter);  // 居中显示图片
        image->setScaledContents(true);
        image->setFixedSize(145, 145);

        ElaText *name = new ElaText(product->getProductName(), productArea);
        name->setTextStyle(ElaTextType::Title);
        name->setFixedWidth(450);

        ElaText *about = new ElaText(product->getProductAbout(), productArea);
        about->setTextPixelSize(15);
        about->setStyleSheet("color: rgb(75, 75, 75);");

        ElaText *price = new ElaText(productArea);
        double nprice = product->getProductPrice(); int nnum = num;
        product->applyStrategy(nprice, nnum);
        price->setText("小计 ￥" + QString::number(nprice * nnum));
        price->setTextStyle(ElaTextType::Subtitle);
        price->setStyleSheet("color: rgb(252, 106, 35); font-weight: bold;");

        ElaText *numText = new ElaText(productArea);
        if (num == nnum) numText->setText("共"+QString::number(nnum)+"件");
        else numText->setText("共"+QString::number(nnum)+"件 (赠"+QString::number(nnum - num)+"件)");
        numText->setStyleSheet("font-size: 16px;");

        totPrice += nprice * nnum;
        double delta = (product->getProductPrice() * num - nprice * nnum);
        delta = qFloor(delta * 100) / 100.0;
        deltaPrice += delta;

        QVBoxLayout *textLayout = new QVBoxLayout();
        textLayout->addWidget(name);
        textLayout->addSpacing(5);
        textLayout->addWidget(about);
        textLayout->addSpacing(5);
        textLayout->addWidget(price);
        textLayout->addSpacing(5);
        textLayout->addWidget(numText);
        textLayout->addSpacing(5);
        textLayout->addStretch();

        productLayout->addStretch();
        productLayout->addWidget(image);
        productLayout->addStretch();
        productLayout->addLayout(textLayout);
        productLayout->addStretch();
        centerLayout->addWidget(productArea);
        centerLayout->addSpacing(10);
    }
    totText = new ElaText("共计 ￥" + QString::number(qFloor(totPrice*100) / 100), 18, this);
    totText->setTextStyle(ElaTextType::Title);

    deltaText = new ElaText("已省 ￥" + QString::number(qFloor(deltaPrice*100) / 100), 14, this);
    deltaText->setTextStyle(ElaTextType::Subtitle);

    confirmBtn = new ElaPushButton("确定下单", this);
    confirmBtn->setFixedSize(100, 50);
    confirmBtn->setLightDefaultColor(redDefault);
    confirmBtn->setLightHoverColor(redHover);
    confirmBtn->setLightPressColor(redPress);
    confirmBtn->setLightTextColor(Qt::white);
    confirmBtn->setStyleSheet("font-size: 15px;");
    connect(confirmBtn, &QPushButton::clicked, [=](){
        payDialog->exec();
    });

    QHBoxLayout *confirmLayout = new QHBoxLayout();
    confirmLayout->addSpacing(30);
    confirmLayout->addWidget(totText);
    confirmLayout->addSpacing(20);
    confirmLayout->addWidget(deltaText);
    confirmLayout->addStretch();
    confirmLayout->addWidget(confirmBtn);
    confirmLayout->addSpacing(20);
    centerLayout->addLayout(confirmLayout);
    centerLayout->addStretch();
}

OrderPage::~OrderPage()
{
}

void OrderPage::onConfirmBtnClicked()
{

}

void OrderPage::onRightBtnClicked()
{

}

void OrderPage::onMiddleBtnClicked()
{

}
