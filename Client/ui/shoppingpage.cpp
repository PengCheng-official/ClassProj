#include "shoppingpage.h"

ShoppingPage::ShoppingPage(Client *cClient, QWidget* parent)
    : BasePage(cClient, parent)
{
    setWindowTitle("我的购物车");
    centralWidget = new QWidget();
    centerLayout = new QVBoxLayout(centralWidget);
}

ShoppingPage::~ShoppingPage()
{
}

void ShoppingPage::refreshPage(QList<Product *> productList, QList<Shopping *> shoppingList)
{
    clearPage(0);
    int n = productList.size();
    for (int i = 0; i < n; i++)
    {
        // ElaCheckBox & ElaSpinBox
        ElaScrollPageArea* productArea = new ElaScrollPageArea(centralWidget);
        ElaCheckBox *checkBox = new ElaCheckBox(productArea);
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
        price->setText("￥" + QString::number(productList[i]->getProductPrice()));
        //TODO: 促销价格
        price->setStyleSheet("color: rgb(252, 106, 35); font-weight: bold;");
        price->setTextStyle(ElaTextType::Subtitle);

        double delta = productList[i]->getProductPrice() - shoppingList[i]->getShoppingPrice();
        ElaText *num = new ElaText("价格变动:" + QString::number(delta), productArea);
        if (delta > 0) num->setStyleSheet("color: green;");
        else num->setStyleSheet("color: rad;");
        num->setTextStyle(ElaTextType::Body);

        ElaPushButton *del = new ElaPushButton("删除", productArea);
        del->setFixedSize(60, 40);
        del->setLightDefaultColor(QColor(252, 90, 31));
        del->setLightHoverColor(QColor(255, 107, 48));
        del->setLightPressColor(QColor(232, 50, 11));
        del->setLightTextColor(Qt::white);

        ElaSpinBox * spinBox = new ElaSpinBox(productArea);
        spinBox->setFixedSize(60, 40);

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
    centerLayout->addStretch();
}
