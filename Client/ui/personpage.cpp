#include "personpage.h"


PersonPage::PersonPage(Client *cClient, QWidget *parent)
    : ElaScrollPage(parent)
    , client(cClient)
{
    setWindowTitle("我的信息");
    centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("我的信息");
    addCentralWidget(centralWidget, true, true, 0);

    QVBoxLayout *centerLayout = new QVBoxLayout(centralWidget);
    auto midHLayout2 = [](QWidget *widget1, QWidget *widget2) -> QHBoxLayout* {
        QHBoxLayout *layout = new QHBoxLayout;
        layout->addStretch();
        layout->addWidget(widget1);
        layout->addWidget(widget2);
        layout->addStretch();
        return layout;
    };
    ElaText *textName = new ElaText("姓名:", 16, this);
    nameEdit = new ElaLineEdit(this);
    nameEdit->setFixedSize(270, 40);
    nameEdit->setStyleSheet("font-weight: bold; font-size: 16px; color: black; ");
    nameEdit->setPlaceholderText("    " + client->getClientName());

    centerLayout->addLayout(midHLayout2(textName, nameEdit));
    centerLayout->addStretch();

}

PersonPage::~PersonPage()
{

}
