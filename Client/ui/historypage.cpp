#include "historypage.h"

#include "../objects/client.h"
#include "../objects/product.h"
#include "../objects/order.h"
#include "../objects/orderlist.h"
#include "../statement.h"

#include <QVBoxLayout>
#include <QLabel>
#include "ElaScrollPageArea.h"
#include "ElaText.h"
#include "ElaPushButton.h"
#include "ElaTheme.h"

HistoryPage::HistoryPage(Client *cClient, QWidget* parent)
    : BasePage(cClient, parent)
{
    setWindowTitle("我的订单历史");
    centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("我的订单历史");
    addCentralWidget(centralWidget, true, true, 0);
    centerLayout = new QVBoxLayout(centralWidget);
}

HistoryPage::~HistoryPage()
{
}

void HistoryPage::initPage()
{
    clearPage(0);
}

void HistoryPage::refreshPage(QList<Order *> orders, QList<Product *> products)
{
    initPage();
    int i = 0;
    if (orders.size() == 0)
    {
        ElaScrollPageArea* orderArea = new ElaScrollPageArea(this);
        orderArea->setFixedHeight(65);
        ElaText *noContent = new ElaText("还没买过东西，快去逛逛吧~", 18, orderArea);
        QHBoxLayout *orderLayout = new QHBoxLayout(orderArea);
        orderLayout->addWidget(noContent);
        centerLayout->addWidget(orderArea);
        centerLayout->addStretch();
        return;
    }
    for (auto order : orders)
    {
        ElaScrollPageArea* orderArea = new ElaScrollPageArea(this);
        orderArea->setFixedHeight(65);
        ElaText *finishTime = new ElaText(order->getFinishTime(), 16, orderArea);
        ElaText *totPrice = new ElaText("小计 ￥"+QString::number(order->getTotalPrice())+" | 共"+QString::number(order->getProductNum())+"件", 17, orderArea);
        ElaText *orderStatus = new ElaText("状态："+order->getOrderStatus(), 17, orderArea);

        ElaPushButton *returnBtn = new ElaPushButton("退款", orderArea);
        returnBtn->setFixedSize(70, 40);
        returnBtn->setLightDefaultColor(redDefault);
        returnBtn->setLightHoverColor(redHover);
        returnBtn->setLightPressColor(redPress);
        returnBtn->setLightTextColor(Qt::white);

        QHBoxLayout *orderLayout = new QHBoxLayout(orderArea);
        orderLayout->addWidget(finishTime);
        orderLayout->addWidget(totPrice);
        orderLayout->addWidget(orderStatus);
        orderLayout->addWidget(returnBtn);
        centerLayout->addWidget(orderArea);
        centerLayout->addSpacing(5);

        for (int j = i; j < i + order->getProductNum(); j++)
        {
            Product *product = products[j];
            qDebug() << "[historyPage] product:" << product->getProductName();
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
            double nprice = product->getProductPrice(); int nnum = product->getProductNum();
            product->applyStrategy(nprice, nnum);
            price->setText("小计 ￥" + QString::number(nprice * nnum));
            price->setTextStyle(ElaTextType::Subtitle);
            price->setStyleSheet("color: rgb(252, 106, 35); font-weight: bold;");

            ElaText *numText = new ElaText(productArea);
            if (product->getProductNum() == nnum) numText->setText("共"+QString::number(nnum)+"件");
            else numText->setText("共"+QString::number(nnum)+"件 (赠"+QString::number(nnum - product->getProductNum())+"件)");
            numText->setStyleSheet("font-size: 16px;");

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
        i += order->getProductNum();
        centerLayout->addSpacing(15);
    }
}
