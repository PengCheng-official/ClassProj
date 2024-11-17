#include "basepage.h"

BasePage::BasePage(QWidget* parent)
    : ElaScrollPage(parent)
{
}

BasePage::~BasePage()
{
}

void BasePage::createCustomWidget()
{
    // 顶部元素
    QWidget* customWidget = new QWidget(this);

    QVBoxLayout* topLayout = new QVBoxLayout(customWidget);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->addSpacing(5);
    topLayout->addSpacing(5);
    setCustomWidget(customWidget);
}
