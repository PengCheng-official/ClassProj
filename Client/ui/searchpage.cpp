#include "searchpage.h"

SearchPage::SearchPage(Client *cClient, QWidget* parent)
    : BasePage(cClient, parent)
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

    centerLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLayout->addStretch();
    searchLayout->addWidget(searchEdit);
    searchLayout->addSpacing(10);
    searchLayout->addWidget(searchBtn);
    searchLayout->addStretch();
    centerLayout->addLayout(searchLayout);
    centerLayout->addSpacing(20);
    centerLayout->addStretch();
}

SearchPage::~SearchPage()
{
}

void SearchPage::refreshPage(QList<Product *> productList)
{
    clearPage(2);

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
        centerLayout->addWidget(productArea);
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

            ElaText *price = new ElaText(productArea);
            if (!product->getStrategy()) price->setText("￥" + QString::number(product->getProductPrice()));
            else
            {
                double nprice = product->getProductPrice(); int num = 1;
                product->applyStrategy(nprice, num);
                qDebug() << nprice << num << product->getStrategy();
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
            //TODO: 促销价格
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
            // 加入购物车
            connect(add, &QPushButton::clicked, [=](){
                double p = product->getProductPrice(); int n = 1;
                product->applyStrategy(p, n);
                Shopping *shopping = new Shopping(client->getClientId(), product->getProductId(), n, p);
                QList<Shopping *> shopList = {shopping};
                qDebug() << "[searchPage] add shopping:" << product->getProductName();

                QJsonObject message;
                ObjectToJson::addSignal(message, QString::number(ADDSHOPPING));
                ObjectToJson::addShoppingList(message, shopList);
                QByteArray array = ObjectToJson::changeJson(message);
                emit sigSendToServer(array);
            });

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
            centerLayout->addWidget(productArea);
            centerLayout->addSpacing(10);
        }
    }
    centerLayout->addStretch();
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

