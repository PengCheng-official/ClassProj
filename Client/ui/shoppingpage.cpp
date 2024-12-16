#include "shoppingpage.h"

ShoppingPage::ShoppingPage(Client *cClient, QWidget* parent)
    : BasePage(cClient, parent)
{
    setWindowTitle("我的购物车");
    centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("我的购物车");
    addCentralWidget(centralWidget, true, true, 0);
    centerLayout = new QVBoxLayout(centralWidget);

    totPrice = deltaPrice = 0;
    totText = new ElaText("共计 ￥" + QString::number(totPrice), 18, this);
    totText->setTextStyle(ElaTextType::Title);

    deltaText = new ElaText("已省 ￥" + QString::number(deltaPrice), 14, this);
    deltaText->setTextStyle(ElaTextType::Subtitle);

    confirmBtn = new ElaPushButton("去结算", this);
    confirmBtn->setFixedSize(100, 50);
    confirmBtn->setLightDefaultColor(ElaThemeColor(ElaThemeType::Light, PrimaryNormal));
    confirmBtn->setLightHoverColor(ElaThemeColor(ElaThemeType::Light, PrimaryHover));
    confirmBtn->setLightPressColor(ElaThemeColor(ElaThemeType::Light, PrimaryPress));
    confirmBtn->setLightTextColor(Qt::white);
    confirmBtn->setStyleSheet("font-size: 15px;");
    connect(confirmBtn, &QPushButton::clicked, [=](){
        // 结算：创建订单，不通信
        if (checkNum > 3) {
            emit sigShoppingTooMore();
            return;
        }
        if (checkNum == 0) {
            emit sigShoppingTooLess();
            return;
        }
        OrderPage *orderPage = new OrderPage(client, selectList);
        orderPage->moveToCenter();
        orderPage->show();
        connect(orderPage, &OrderPage::sigSendToServer, this, &ShoppingPage::sigSendToServer);
        connect(orderPage, &OrderPage::sigSendMessageBar, this, &ShoppingPage::sigSendMessageBar);
        connect(qobject_cast<Allmain*>(parent), &Allmain::sigCreateOrderId, [=](int oid){
            orderPage->createOrderList(oid);
        });
        //TODO: 返回
    });
}

ShoppingPage::~ShoppingPage()
{
}

void ShoppingPage::initPage()
{
    clearPage(0);
    totPrice = deltaPrice = checkNum = 0;
    confirmChanged();
    selectList.clear();
}

void ShoppingPage::refreshPage(QList<Product *> productList, QList<Shopping *> shoppingList)
{
    initPage();
    int n = productList.size();
    qDebug() << "[shoppingPage] cnt:" << n;

    for (int i = 0; i < n; i++)
    {
        // ElaCheckBox & ElaSpinBox
        qDebug() << "[shoppingPage] product:" << productList[i]->getProductId();
        ElaScrollPageArea* productArea = new ElaScrollPageArea(centralWidget);

        productArea->setFixedHeight(160);
        QGridLayout* productLayout = new QGridLayout(productArea);

        QLabel *image = new QLabel(productArea);
        image->setPixmap(QPixmap(productList[i]->getProductImage()));
        image->setAlignment(Qt::AlignCenter);  // 居中显示图片
        image->setScaledContents(true);
        image->setFixedSize(145, 145);

        ElaText *name = new ElaText(productList[i]->getProductName(), productArea);
        name->setTextStyle(ElaTextType::Title);
        name->setFixedWidth(450);

        ElaText *about = new ElaText(productList[i]->getProductAbout(), productArea);
        about->setTextPixelSize(15);
        about->setStyleSheet("color: rgb(75, 75, 75);");

        ElaText *price = new ElaText(productArea);
        makePriceText(price, productList[i]);
        price->setStyleSheet("color: rgb(252, 106, 35); font-weight: bold;");
        price->setTextStyle(ElaTextType::Subtitle);

        //TODO: 促销价格 delta 也要改
        double nprice = productList[i]->getProductPrice(); int nnum = shoppingList[i]->getShoppingNum();
        productList[i]->applyStrategy(nprice, nnum);
        double delta = nprice - shoppingList[i]->getShoppingPrice();
        ElaText *num = new ElaText(productArea);
        if (delta > 0) {
            num->setText("价格变动: +" + QString::number(delta));
            num->setStyleSheet("color: red;");
        }
        else {
            num->setText("价格变动: " + QString::number(delta));
            num->setStyleSheet("color: green;");
        }
        num->setTextStyle(ElaTextType::Body);

        ElaPushButton *del = new ElaPushButton("删除", productArea);
        del->setFixedSize(60, 40);
        del->setLightDefaultColor(redDefault);
        del->setLightHoverColor(redHover);
        del->setLightPressColor(redPress);
        del->setLightTextColor(Qt::white);

        ElaCheckBox *checkBox = new ElaCheckBox(productArea);
        ElaSpinBox * spinBox = new ElaSpinBox(productArea);
        spinBox->setFixedSize(75, 30);
        spinBox->setMinimum(1);
        spinBox->setValue(shoppingList[i]->getShoppingNum());
        spinMap[spinBox] = spinBox->value();

        connect(checkBox, &QCheckBox::stateChanged, [=](int state){
            if (state == Qt::Checked)
            {
                ++ checkNum;
                double nprice = productList[i]->getProductPrice(); int nnum = shoppingList[i]->getShoppingNum();
                productList[i]->applyStrategy(nprice, nnum);
                selectList.append({productList[i], spinBox->value()});
                //TODO: 促销价格
                totPrice += nprice * spinBox->value();
                deltaPrice -= delta < 0 ? delta * spinBox->value() : 0;
            }
            else if (state == Qt::Unchecked)
            {
                -- checkNum;
                double nprice = productList[i]->getProductPrice(); int nnum = shoppingList[i]->getShoppingNum();
                productList[i]->applyStrategy(nprice, nnum);
                selectList.removeAll({productList[i], spinBox->value()});
                //TODO: 促销价格
                totPrice -= nprice * spinBox->value();
                deltaPrice += delta < 0 ? delta * spinBox->value() : 0;
            }
            confirmChanged();
        });

        connect(spinBox, &QSpinBox::valueChanged, [=](int value){
            selectList.removeAll({productList[i], spinMap[spinBox]});
            selectList.append({productList[i], value});
            //TODO: 促销价格
            double nprice = productList[i]->getProductPrice(); int nnum = shoppingList[i]->getShoppingNum();
            productList[i]->applyStrategy(nprice, nnum);
            totPrice += nprice * (value - spinMap[spinBox]);
            deltaPrice += delta < 0 ? delta * abs(value - spinMap[spinBox]) : 0;
            spinMap[spinBox] = value;
            confirmChanged();
        });

        productLayout->addWidget(checkBox, 0, 0, -1, 1);
        productLayout->addWidget(image, 0, 1, -1, 1);
        productLayout->addWidget(name, 0, 2, 1, 2);
        productLayout->addWidget(about, 1, 2, 1, 2);
        productLayout->addWidget(price, 2, 2, 1, 1);
        productLayout->addWidget(num, 3, 2, 1, 1);
        productLayout->addWidget(del, 2, 3, 1, 2);
        productLayout->addWidget(spinBox, 3, 3, 1, 2);
        centerLayout->addWidget(productArea);
        centerLayout->addSpacing(10);
    }
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

void ShoppingPage::confirmChanged()
{
    totText->setText("共计 ￥" + QString::number(totPrice));
    deltaText->setText("已省 ￥" + QString::number(deltaPrice));
}
