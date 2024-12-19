#include "searchpage.h"

#include <QSqlError>

#include "../dao/productmapper.h"
#include "../objects/product.h"
#include "objecttojson.h"
#include "statement.h"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QVBoxLayout>
#include "ElaScrollPageArea.h"
#include "ElaText.h"
#include "ElaWindow.h"
#include "ElaLineEdit.h"
#include "ElaPushButton.h"
#include "ElaTheme.h"

SearchPage::SearchPage(QWidget* parent)
    : BasePage(parent)
{
    setWindowTitle("搜索商品");
    connectToDB("SearchPage");

    searchEdit = new ElaLineEdit(this);
    searchEdit->setFixedSize(500, 45);
    searchEdit->setPlaceholderText("  搜索商品名称");
    searchEdit->setStyleSheet("font-size: 16px;");
    connect(searchEdit, &QLineEdit::returnPressed, this, &SearchPage::onSearchBtnClicked);

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

void SearchPage::updatePage(QList<Product *> productList)
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
            if (product->getProductId() == 0) continue;
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

            ElaText *price = new ElaText("￥" + QString::number(formatNum(product->getProductPrice())), productArea);
            price->setStyleSheet("color: rgb(252, 106, 35); font-weight: bold;");
            price->setTextStyle(ElaTextType::Subtitle);

            ElaText *num = new ElaText("库存" + QString::number(product->getProductNum()) + "件", productArea);
            if (product->getProductNum() <= 5) num->setStyleSheet("color: red;");
            num->setTextStyle(ElaTextType::Body);

            ElaPushButton *add = new ElaPushButton("修改商品", productArea);
            add->setFixedSize(100, 40);
            add->setLightDefaultColor(ElaThemeColor(ElaThemeType::Light, PrimaryNormal));
            add->setLightHoverColor(ElaThemeColor(ElaThemeType::Light, PrimaryHover));
            add->setLightPressColor(ElaThemeColor(ElaThemeType::Light, PrimaryPress));
            add->setLightTextColor(Qt::white);
            QHBoxLayout *addLayout = new QHBoxLayout();
            addLayout->addWidget(num);
            addLayout->addStretch();
            addLayout->addWidget(add);
            // TODO: 修改商品
            connect(add, &QPushButton::clicked, [=](){
               emit sigTurnToProduct(product);
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
    ProductMapper *productMapper = new ProductMapper(db);
    updatePage(productMapper->selectLike(searchEdit->text()));
}

