#include "historypage.h"

#include <QJsonObject>

#include "../objects/client.h"
#include "../objects/product.h"
#include "../objects/order.h"
#include "../objects/orderlist.h"
#include "../objecttojson.h"
#include "../statement.h"

#include <QVBoxLayout>
#include <QLabel>
#include "ElaScrollPageArea.h"
#include "ElaText.h"
#include "ElaPushButton.h"
#include "ElaTheme.h"

HistoryPage::HistoryPage(QWidget* parent)
    : ElaScrollPage(parent)
{
    setWindowTitle("订单历史");
    centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("订单历史");
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

void HistoryPage::clearPage(int left)
{
    qDebug() << "[HistoryPage] clearing:" << centerLayout->count();
    // 先清除上次的在线列表，留下搜索layout和空间
    if (centerLayout) {
        // 删除旧的布局
        int cnt = centerLayout->count();
        for (int i = cnt - 1; i >= left; i--)
        {
            QLayoutItem *item = centerLayout->takeAt(i);
            centerLayout->removeItem(item);  // 从布局中移除项

            QWidget *widget = item->widget();
            QSpacerItem *spacer = dynamic_cast<QSpacerItem*>(item);
            if (widget)
            {
                widget->setParent(nullptr);  // 移除父级关系
                delete widget;  // 删除控件
                delete item;    // 从布局中删除项
            }
            else if (spacer)
            {
                delete spacer;  // 删除伸缩项
            }
            else delete item;
        }
    }
}

void HistoryPage::refreshPage(QList<Order *> orders, QList<Product *> products)
{
    initPage();
    int i = 0;
    if (orders.size() == 0)
    {
        ElaScrollPageArea* orderArea = new ElaScrollPageArea(this);
        orderArea->setFixedHeight(60);
        ElaText *noContent = new ElaText("还没有用户买过东西", 18, orderArea);
        QHBoxLayout *orderLayout = new QHBoxLayout(orderArea);
        orderLayout->addWidget(noContent);
        centerLayout->addWidget(orderArea);
        centerLayout->addStretch();
        return;
    }
    for (auto order : orders)
    {
        ElaScrollPageArea* orderArea = new ElaScrollPageArea(this);
        orderArea->setFixedHeight(55);
        ElaText *finishTime = new ElaText(order->getFinishTime(), 16, orderArea);
        ElaText *userId = new ElaText("UID："+QString::number(order->getClientId()), 17, orderArea);
        userId->setFixedWidth(100);
        ElaText *totPrice = new ElaText("小计 ￥"+QString::number(order->getTotalPrice())+" | 共"+QString::number(order->getProductNum())+"件", 17, orderArea);
        ElaText *orderStatus = new ElaText("状态："+order->getOrderStatus(), 17, orderArea);

        QHBoxLayout *orderLayout = new QHBoxLayout(orderArea);
        orderLayout->addWidget(finishTime);
        orderLayout->addWidget(userId);
        orderLayout->addWidget(totPrice);
        orderLayout->addWidget(orderStatus);
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
            price->setText("小计 ￥" + QString::number(product->getProductPrice()));
            price->setTextStyle(ElaTextType::Subtitle);
            price->setStyleSheet("color: rgb(252, 106, 35); font-weight: bold;");

            ElaText *numText = new ElaText(productArea);
            numText->setText("共"+QString::number(product->getProductNum())+"件");
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
    centerLayout->addStretch();
}
