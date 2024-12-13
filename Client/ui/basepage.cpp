#include "basepage.h"

BasePage::BasePage(Client *cClient, QWidget* parent)
    : ElaScrollPage(parent)
    , client(cClient)
{
    centralWidget = new QWidget(this);
    centerLayout = new QVBoxLayout(centralWidget);
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
