#include "basepage.h"

#include <QSqlError>

#include "../objects/product.h"
#include "objecttojson.h"
#include "statement.h"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QVBoxLayout>
#include "ElaScrollPageArea.h"
#include "ElaMenu.h"
#include "ElaText.h"
#include "ElaWindow.h"
#include "ElaPushButton.h"
#include "ElaLineEdit.h"
#include "ElaTheme.h"

BasePage::BasePage(QWidget* parent)
    : ElaScrollPage(parent)
{
//    centralWidget = new QWidget(this);
//    centerLayout = new QVBoxLayout(centralWidget);
}

BasePage::~BasePage()
{
}

void BasePage::clearPage(int left)
{
    qDebug() << "[basePage] clearing:" << centerLayout->count();
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

void BasePage::makePriceText(ElaText *price, Product *product)
{
    if (!product->getStrategy()) price->setText("￥" + QString::number(formatNum(product->getProductPrice())));
    else
    {
        double nprice = product->getProductPrice(); int num = 1;
        product->applyStrategy(nprice, num);
        nprice = formatNum(nprice);
        switch(product->getStrategy())
        {
        case 1:
            price->setText("促销 ￥"+QString::number(nprice)+" | "+QString::number(product->getStrategy1())+"折");
            break;
        case 2:
            price->setText("促销 ￥"+QString::number(nprice)+" | 满￥"+QString::number(product->getStrategy1())+"减￥"+QString::number(product->getStrategy2()));
            break;
        case 3:
            price->setText("促销 ￥"+QString::number(nprice)+" | 满"+QString::number(product->getStrategy1())+"赠"+QString::number(product->getStrategy2()));
            break;
        case 4:
            price->setText("促销 ￥"+QString::number(nprice)+" | 共"+QString::number(product->getStrategy1())+"件");
            break;
        }
    }
}

double BasePage::formatNum(double num)
{
    return qFloor(num * 100) / 100.0;
}

void BasePage::connectToDB(const QString pageName)
{
    db = QSqlDatabase::addDatabase("QODBC", pageName);
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("MySql");
    db.setUserName("root");
    db.setPassword("pengcheng_050210");
    if(!db.open()) {
        qDebug() << "[database] Failed to connect to db: " << db.lastError();
        return;
    }
    qDebug() << "[database] Connected to MySql";
}
