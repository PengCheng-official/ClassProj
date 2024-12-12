#include "searchpage.h"

SearchPage::SearchPage(Client *cClient, QWidget* parent)
    : ElaScrollPage(parent)
    , client(cClient)
{
    setWindowTitle("搜索商品");

    searchEdit = new ElaLineEdit(this);
    searchEdit->setFixedSize(500, 45);
    searchEdit->setPlaceholderText("  搜索商品名称");
    searchEdit->setStyleSheet("font-size: 16px;");

    searchBtn = new ElaPushButton("搜索", this);
    searchBtn->setFixedSize(70, 45);
    searchBtn->setLightDefaultColor(ElaThemeColor(ElaThemeType::Light, PrimaryNormal));
    searchBtn->setLightHoverColor(ElaThemeColor(ElaThemeType::Light, PrimaryHover));
    searchBtn->setLightPressColor(ElaThemeColor(ElaThemeType::Light, PrimaryPress));
    searchBtn->setLightTextColor(Qt::white);
    connect(searchBtn, &QPushButton::clicked, this, &SearchPage::onSearchBtnClicked);

    centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("搜索商品");
    addCentralWidget(centralWidget, true, true, 0);

    mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLayout->addStretch();
    searchLayout->addWidget(searchEdit);
    searchLayout->addSpacing(10);
    searchLayout->addWidget(searchBtn);
    searchLayout->addStretch();
    mainLayout->addLayout(searchLayout);
    mainLayout->addSpacing(20);
    mainLayout->addStretch();
}

SearchPage::~SearchPage()
{
}

void SearchPage::clearPage()
{
    qDebug() << "[searchPage] clearing:" << mainLayout->count();
    // 先清除上次的在线列表，留下搜索layout和空间
    if (mainLayout) {
        // 删除旧的布局
        int cnt = mainLayout->count();
        for (int i = cnt - 1; i >= 2; i--)
        {
            QLayoutItem *item = mainLayout->takeAt(i);
            mainLayout->removeItem(item);  // 从布局中移除项

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

void SearchPage::refreshPage(QList<Product *> productList)
{
    clearPage();

    qDebug() << "[searchPage] update products...";
    if (productList.size() == 0)
    {
        qDebug() << "[searchPage] no found";
        ElaScrollPageArea* productArea = new ElaScrollPageArea(centralWidget);
        QHBoxLayout* productLayout = new QHBoxLayout(productArea);
        ElaText* text = new ElaText("没有找到商品", productArea);
        text->setTextPixelSize(15);
        productLayout->addWidget(text);
        productLayout->addStretch();
        mainLayout->addWidget(productArea);
    }
    else
    {
        qDebug() << "[searchPage] found:" << productList.size();
        for (auto product : productList)
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

            ElaText *price = new ElaText("￥" + QString::number(product->getProductPrice()), productArea);
            price->setStyleSheet("color: rgb(252, 106, 35); font-weight: bold;");
            price->setTextStyle(ElaTextType::Subtitle);

            ElaText *num = new ElaText("库存" + QString::number(product->getProductNum()) + "件", productArea);
            if (product->getProductNum() <= 5) num->setStyleSheet("color: red;");
            num->setTextStyle(ElaTextType::Body);

            ElaPushButton *add = new ElaPushButton("加入购物车", productArea);
            add->setFixedSize(100, 40);
            add->setLightDefaultColor(QColor(252, 90, 31));
            add->setLightHoverColor(QColor(255, 107, 48));
            add->setLightPressColor(QColor(232, 50, 11));
            add->setLightTextColor(Qt::white);
            QHBoxLayout *addLayout = new QHBoxLayout();
            addLayout->addWidget(num);
            addLayout->addStretch();
            addLayout->addWidget(add);
            // TODO: 加入购物车

            QVBoxLayout *textLayout = new QVBoxLayout();
            textLayout->addWidget(name);
            textLayout->addSpacing(5);
            textLayout->addWidget(about);
            textLayout->addSpacing(5);
            textLayout->addWidget(price);
            textLayout->addLayout(addLayout);
            textLayout->addSpacing(5);
            textLayout->addStretch();

            productLayout->addStretch();
            productLayout->addWidget(image);
            productLayout->addStretch();
            productLayout->addLayout(textLayout);
            productLayout->addStretch();
            mainLayout->addWidget(productArea);
            mainLayout->addSpacing(10);
        }
    }
    mainLayout->addStretch();
}

void SearchPage::onSearchBtnClicked()
{
    QList<Client *> clientList = {client};
    QList<QString> strList = {searchEdit->text()};

    QJsonObject message;
    ObjectToJson::addStrings(message, strList);
    ObjectToJson::addClientList(message, clientList);
    ObjectToJson::addSignal(message, QString::number(SEARCHPRODUCT));
    QByteArray array = ObjectToJson::changeJson(message);
    emit sigSendToServer(array);
}

