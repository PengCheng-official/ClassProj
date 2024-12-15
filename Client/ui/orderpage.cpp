#include "orderpage.h"

OrderPage::OrderPage(Client *cClient, QList<QPair<Product *, int> > selectList, QWidget* parent)
    : BasePage(cClient, parent)
{
    // 初始化时不建立 order，没有申请 order_id
    centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("订单状态：未支付");
    addCentralWidget(centralWidget, true, true, 0);

    centerLayout = new QVBoxLayout(centralWidget);
    for (auto [product, num] : selectList)
    {
        ElaScrollPageArea* productArea = new ElaScrollPageArea(centralWidget);
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
        price->setStyleSheet("color: rgb(252, 106, 35); font-weight: bold;");
        price->setTextStyle(ElaTextType::Subtitle);

        ElaText *numText = new ElaText(productArea);
        if (num == nnum) numText->setText("共"+QString::number(nnum)+"件");
        else numText->setText("共"+QString::number(nnum)+"件 (赠"+QString::number(nnum - num)+"件)");

        totPrice += nprice * nnum;
        deltaPrice += (product->getProductPrice() * num - nprice * nnum);

        QVBoxLayout *textLayout = new QVBoxLayout();
        textLayout->addWidget(name);
        textLayout->addSpacing(5);
        textLayout->addWidget(about);
        textLayout->addSpacing(5);
        textLayout->addWidget(numText);
        textLayout->addSpacing(5);
        textLayout->addWidget(price);
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
    totText = new ElaText("共计 ￥" + QString::number(totPrice), 18, this);
    totText->setTextStyle(ElaTextType::Title);

    deltaText = new ElaText("已省 ￥" + QString::number(deltaPrice), 14, this);
    deltaText->setTextStyle(ElaTextType::Subtitle);

    confirmBtn = new ElaPushButton("确定下单", this);
    confirmBtn->setFixedSize(270, 50);
    confirmBtn->setLightDefaultColor(redDefault);
    confirmBtn->setLightHoverColor(redHover);
    confirmBtn->setLightPressColor(redPress);
    confirmBtn->setLightTextColor(Qt::white);
    confirmBtn->setStyleSheet("font-size: 15px;");

    centerLayout->addWidget(confirmBtn);
    centerLayout->addStretch();
}

OrderPage::~OrderPage()
{
}

void OrderPage::onConfirmBtnClicked()
{

}
