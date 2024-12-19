#include "productpage.h"

#include "objecttojson.h"
#include "../dao/productmapper.h"
#include "../objects/product.h"
#include "statement.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QFileDialog>
#include "ElaText.h"
#include "ElaWindow.h"
#include "ElaLineEdit.h"
#include "ElaToggleButton.h"
#include "ElaPushButton.h"
#include "ElaScrollPageArea.h"
#include "ElaComboBox.h"
#include "ElaPlainTextEdit.h"
#include "ElaTheme.h"

ProductPage::ProductPage(QWidget* parent)
    : BasePage(parent)
{
    connectToDB("ProductPage");
    setWindowTitle("增改商品信息");
    centralWidget = new QWidget(this);
    centralWidget->setWindowTitle("增改商品信息");
    addCentralWidget(centralWidget, true, true, 0);

    //主Layout 初始化
    centerLayout = new QVBoxLayout(centralWidget);
    //复用居中的 水平Layout
    auto midHLayout2 = [](QWidget *widget1, QWidget *widget2) -> QHBoxLayout* {
        QHBoxLayout *layout = new QHBoxLayout;
        layout->addStretch();
        layout->addWidget(widget1);
        layout->addSpacing(10);
        layout->addWidget(widget2);
        layout->addStretch();
        return layout;
    };

    //商品名称 初始化
    ElaText *nameText = new ElaText("名称:", 18, this);
    nameEdit = new ElaLineEdit(this);
    nameEdit->setFixedSize(270, 40);
    nameEdit->setStyleSheet("font-size: 16px; font-weight: bold; color: black; ");

    //图片 初始化
    ElaText *imageText = new ElaText("图片:", 18, this);
    imageBtn = new ElaPushButton("选择图片", this);
    imageBtn->setFixedSize(100, 40);
    QHBoxLayout *imageLayout = new QHBoxLayout();
    imageLayout->addStretch();
    imageLayout->addWidget(imageText);
    imageLayout->addSpacing(11);
    imageLayout->addWidget(imageBtn);
    imageLayout->addSpacing(175);
    imageLayout->addStretch();
    connect(imageBtn, &ElaPushButton::clicked, [=](){
        imagePath = QFileDialog::getOpenFileName(
                    this,
                    tr("Select Image"),
                    "C:\\Users\\PC\\Desktop\\ClassPro\\MyPro\\Server\\include\\Resource",
                    tr("Image Files (*.png *.jpg *.bmp)"
                       ));
        qDebug() << "[personPage] select image: " << imagePath;
    });

    //价格 初始化
    ElaText *priceText = new ElaText("价格:", 18, this);
    priceEdit = new ElaLineEdit(this);
    priceEdit->setFixedSize(270, 40);
    priceEdit->setStyleSheet("font-size: 16px; color: black;");

    //库存 初始化
    ElaText *numText = new ElaText("库存:", 18, this);
    numEdit = new ElaLineEdit(this);
    numEdit->setFixedSize(270, 36);
    numEdit->setStyleSheet("font-size: 16px; color: black; ");

    //策略 初始化
    ElaText *strategyText = new ElaText("促销:", 18, this);
    strategyBox = new ElaComboBox(this);
    QStringList strategyList = {
        "无",
        "直接折扣",
        "满减活动",
        "买赠活动",
        "限时促销"
    };
    strategyBox->addItems(strategyList);
    strategyBox->setFixedWidth(140);
    strategyBox->setStyleSheet("font-size: 14px;");
    connect(strategyBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &ProductPage::onCurrentIndexChanged);
    QHBoxLayout *strategyLayout = new QHBoxLayout();
    strategyLayout->addStretch();
    strategyLayout->addWidget(strategyText);
    strategyLayout->addSpacing(11);
    strategyLayout->addWidget(strategyBox);
    strategyLayout->addSpacing(135);
    strategyLayout->addStretch();

    // 活动 初始化
    ElaText *activityText = new ElaText("活动:", 18, this);
    _edit1 = new QLineEdit(this);
    _edit2 = new QLineEdit(this);
    _edit1->setFixedSize(40, 36);
    _edit2->setFixedSize(40, 36);
    _edit1->setAlignment(Qt::AlignCenter);
    _edit2->setAlignment(Qt::AlignCenter);
    activityLayouts[0] = new QHBoxLayout();
    activityLayouts[1] = new QHBoxLayout();
    activityLayouts[2] = new QHBoxLayout();
    activityLayouts[3] = new QHBoxLayout();
    activityLayouts[4] = new QHBoxLayout();
    createActivityLayout(activityText);

    //简介 初始化 ElaPlainTextEdit
    ElaText *aboutText = new ElaText("简介:", 18, this);
    aboutEdit = new ElaPlainTextEdit(this);
    aboutEdit->setStyleSheet("font-size: 16px;");
    aboutEdit->setFixedWidth(270);
    //    aboutEdit->setPlainText(product->getProductAbout());

    //确定按钮 初始化
    confirmBtn = new ElaPushButton("确认新增", this);
    confirmBtn->setFixedSize(100, 40);
    confirmBtn->setLightDefaultColor(redDefault);
    confirmBtn->setLightHoverColor(redHover);
    confirmBtn->setLightPressColor(redPress);
    confirmBtn->setLightTextColor(Qt::white);
    confirmBtn->setStyleSheet("font-size: 16px;");

    //删除按钮 初始化
    deleteBtn = new ElaPushButton("删除", this);
    deleteBtn->setFixedSize(75, 40);
    deleteBtn->setLightDefaultColor(QColor(255, 90, 31));
    deleteBtn->setLightHoverColor(QColor(255, 107, 48));
    deleteBtn->setLightPressColor(QColor(255, 50, 11));
    deleteBtn->setLightTextColor(Qt::white);
    deleteBtn->setStyleSheet("font-size: 16px;");

    //连接确定的点击槽函数
    connect(confirmBtn, &QPushButton::clicked, this, &ProductPage::onConFirmBtnClicked);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addSpacing(140);
    btnLayout->addWidget(deleteBtn);
    btnLayout->addSpacing(20);
    btnLayout->addWidget(confirmBtn);
    btnLayout->addStretch();

    //主Layout添加
    centerLayout->addSpacing(25);
    centerLayout->addLayout(midHLayout2(nameText, nameEdit));
    centerLayout->addSpacing(25);
    centerLayout->addLayout(imageLayout);
    centerLayout->addSpacing(25);
    centerLayout->addLayout(midHLayout2(priceText, priceEdit));
    centerLayout->addSpacing(25);
    centerLayout->addLayout(midHLayout2(numText, numEdit));
    centerLayout->addSpacing(25);
    centerLayout->addLayout(strategyLayout);
    centerLayout->addSpacing(25);
    centerLayout->addLayout(activityLayouts[0]);
    centerLayout->addSpacing(25);
    centerLayout->addLayout(midHLayout2(aboutText, aboutEdit));
    centerLayout->addSpacing(25);
    centerLayout->addLayout(btnLayout);
    centerLayout->addStretch();

    initPage();
}

ProductPage::~ProductPage()
{
}

void ProductPage::initPage(Product *pProduct)
{
    if (pProduct == nullptr)
    {
        IsNew = true;
        product = nullptr;
        nameEdit->setPlaceholderText("  输入商品名称");
        priceEdit->setPlaceholderText("  输入商品价格");
        numEdit->setPlaceholderText("  输入商品库存量");
        strategyBox->setCurrentIndex(0);
        aboutEdit->setPlaceholderText("  输入商品简介");
        confirmBtn->setText("确认新增");
        deleteBtn->hide();
    }
    else
    {
        IsNew = false;
        product = pProduct;
        nameEdit->setPlaceholderText("  " + product->getProductName());
        priceEdit->setPlaceholderText("  " + QString::number(formatNum(product->getProductPrice())));
        numEdit->setPlaceholderText("  " + QString::number(product->getProductNum()));
        strategyBox->setCurrentIndex(product->getStrategy());
        onCurrentIndexChanged(product->getStrategy());
        _edit1->setPlaceholderText(QString::number(product->getStrategy1()));
        _edit2->setPlaceholderText(QString::number(product->getStrategy2()));
        aboutEdit->setPlainText(product->getProductAbout());
        confirmBtn->setText("确认修改");
        deleteBtn->show();
    }
}

void ProductPage::onCurrentIndexChanged(int cur)
{
    // 11
    centerLayout->removeItem(centerLayout->itemAt(11));
    centerLayout->insertLayout(11, activityLayouts[cur]);

    switch (cur) {
    case 0:
        _edit1->hide();
        _edit2->hide();
        _text1->show();
        _text2->hide();
        _text3->hide();
        _text4->hide();
        _text5->hide();
        _text6->hide();
        _text7->hide();
        _text8->hide();
        break;
    case 1:
        _edit1->show();
        _edit2->hide();
        _text1->hide();
        _text2->show();
        _text3->hide();
        _text4->hide();
        _text5->hide();
        _text6->hide();
        _text7->hide();
        _text8->hide();
        break;
    case 2:
        _edit1->show();
        _edit2->show();
        _text1->hide();
        _text2->hide();
        _text3->show();
        _text4->show();
        _text5->hide();
        _text6->hide();
        _text7->hide();
        _text8->hide();
        break;
    case 3:
        _edit1->show();
        _edit2->show();
        _text1->hide();
        _text2->hide();
        _text3->show();
        _text4->hide();
        _text5->show();
        _text6->hide();
        _text7->hide();
        _text8->hide();
        break;
    case 4:
        _edit1->show();
        _edit2->show();
        _text1->hide();
        _text2->hide();
        _text3->hide();
        _text4->hide();
        _text5->hide();
        _text6->show();
        _text7->show();
        _text8->show();
        break;
    default:
        _edit1->hide();
        _edit2->hide();
        _text1->hide();
        _text2->hide();
        _text3->hide();
        _text4->hide();
        _text5->hide();
        _text6->hide();
        _text7->hide();
        _text8->hide();
        break;
    }
}

void ProductPage::onConFirmBtnClicked()
{
    auto IsNum = [=](const QString &str) {
        bool ok;
        double d = str.toDouble(&ok);
        ok = d >= 0;
        return ok;
    };
    auto IsInt = [=](const QString &str) {
        bool ok;
        int d = str.toInt(&ok);
        ok = d >= 0;
        return ok;
    };
    if (IsNew)
    {
        Product *nProduct = new Product();
        if (nameEdit->text() != "") {
            nProduct->setProductName(nameEdit->text());
        }
        else {
            emit sigCreateFail(0);  //没设置名称
            return;
        }
        if (imagePath != "") {
            nProduct->setProductImage(imagePath);
        }
        if (priceEdit->text() != "") {
            if (priceEdit->text().toDouble())
                nProduct->setProductPrice(priceEdit->text().toDouble());
            else {
                emit sigCreateFail(11); //价格输入不是浮点数
                return;
            }
        }
        else {
            emit sigCreateFail(10);  //没设置价格
            return;
        }
        if (numEdit->text() != "") {
            if (numEdit->text().toInt())
                nProduct->setProductNum(numEdit->text().toInt());
            else {
                emit sigCreateFail(21); //库存输入不是整数
                return;
            }
        }
        else {
            emit sigCreateFail(20);  //没设置库存
            return;
        }
        if (aboutEdit->toPlainText() != "") {
            nProduct->setProductAbout(aboutEdit->toPlainText());
        }
        if ((_edit1->text() != "" && !IsNum(_edit2->text()))
                || (_edit2->text() != "" && !IsNum(_edit2->text()))) {
            emit sigCreateFail(31); //edit不是数字
            return;
        }
        switch(strategyBox->currentIndex())
        {
        case 0:
            nProduct->setStrategy(0, 0, 0);
            break;
        case 1:
            if (_edit1->text() == "" || _edit1->text().toDouble() > 10) {
                emit sigCreateFail(4); //折扣大于10
                return;
            }
            nProduct->setStrategy(1, _edit1->text().toDouble(), 0);
            break;
        case 2:
            if (_edit1->text() == "" || _edit2->text() == "") {
                emit sigCreateFail(4);
                return;
            }
            nProduct->setStrategy(2, _edit1->text().toDouble(), _edit2->text().toDouble());
            break;
        case 3:
            if (_edit1->text() == "" || _edit2->text() == "" || !IsInt(_edit1->text()) || !IsInt(_edit2->text())) {
                emit sigCreateFail(4); //满赠不是整数
                return;
            }
            nProduct->setStrategy(3, _edit1->text().toInt(), _edit2->text().toInt());
            break;
        case 4:
            if (_edit1->text() == "" || _edit2->text() == "") {
                emit sigCreateFail(4);
                return;
            }
            nProduct->setStrategy(4, _edit1->text().toDouble(), _edit2->text().toDouble());
            break;
        default:
            emit sigCreateFail(4); //满赠不是整数
            return;
        }
        ProductMapper *productMapper = new ProductMapper(db);
        productMapper->insert(nProduct);
        refreshPage();
        emit sigCreateFail(200); //成功
    }
    else
    {
        Product *nProduct = new Product(*product);
        ProductMapper *productMapper = new ProductMapper(db);
        if (nameEdit->text() != "") {
            nProduct->setProductName(nameEdit->text());
        }
        if (imagePath != "") {
            nProduct->setProductImage(imagePath);
        }
        if (priceEdit->text() != "") {
            if (IsNum(priceEdit->text()))
                nProduct->setProductPrice(priceEdit->text().toDouble());
            else {
                emit sigCreateFail(11); //价格输入不是浮点数
                return;
            }
        }
        if (numEdit->text() != "") {
            if (IsInt(numEdit->text()))
                nProduct->setProductNum(numEdit->text().toInt());
            else {
                emit sigCreateFail(21); //价格输入不是整数
                return;
            }
        }
        if (aboutEdit->toPlainText() != "") {
            if (aboutEdit->toPlainText().length() > 30) {
                emit sigCreateFail(5);
                return;
            }
            nProduct->setProductAbout(aboutEdit->toPlainText());
        }
        if ((_edit1->text() != "" && !IsNum(_edit1->text()))
                || (_edit2->text() != "" && !IsNum(_edit2->text()))) {
            emit sigCreateFail(31); //edit不是数字
            return;
        }
        switch(strategyBox->currentIndex())
        {
        case 0:
            nProduct->setStrategy(0, 0, 0);
            break;
        case 1:
            if (_edit1->text() == "" || _edit1->text().toDouble() > 10) {
                emit sigCreateFail(4); //折扣大于10
                return;
            }
            nProduct->setStrategy(1, _edit1->text().toDouble(), 0);
            break;
        case 2:
            if (_edit1->text() == "" || _edit2->text() == "") {
                emit sigCreateFail(4);
                return;
            }
            nProduct->setStrategy(2, _edit1->text().toDouble(), _edit2->text().toDouble());
            break;
        case 3:
            if (_edit1->text() == "" || _edit2->text() == "" || !IsInt(_edit1->text()) || !IsInt(_edit2->text())) {
                emit sigCreateFail(4); //满赠不是整数
                return;
            }
            nProduct->setStrategy(3, _edit1->text().toInt(), _edit2->text().toInt());
            break;
        case 4:
            if (_edit1->text() == "" || _edit2->text() == "" || !IsInt(_edit1->text())) {
                emit sigCreateFail(4);
                return;
            }
            nProduct->setStrategy(4, _edit1->text().toInt(), _edit2->text().toDouble());
            break;
        default:
            emit sigCreateFail(4); //满赠不是整数
            return;
        }
        productMapper->update(nProduct);
        refreshPage(nProduct);
        emit sigCreateFail(200); //成功
    }
}

void ProductPage::onDeleteBtnClicked()
{
    ProductMapper *productMapper = new ProductMapper(db);
    productMapper->delet(product->getProductId());
    refreshPage();
}

void ProductPage::createActivityLayout(ElaText *activityText)
{
    activityLayouts[0]->addStretch();
    activityLayouts[0]->addWidget(activityText);
    activityLayouts[0]->addSpacing(11);
    _text1 = new ElaText("不参加活动", 17, this);
    _text1->setFixedSize(100, 36);
    activityLayouts[0]->addWidget(_text1);
    activityLayouts[0]->addSpacing(170);
    activityLayouts[0]->addStretch();

    activityLayouts[1]->addStretch();
    activityLayouts[1]->addWidget(activityText);
    activityLayouts[1]->addSpacing(11);
    _text2 = new ElaText("折", 17, this);
    _text2->setFixedSize(30, 36);
    activityLayouts[1]->addWidget(_edit1);
    activityLayouts[1]->addWidget(_text2);
    activityLayouts[1]->addSpacing(195);
    activityLayouts[1]->addStretch();

    activityLayouts[2]->addStretch();
    activityLayouts[2]->addWidget(activityText);
    activityLayouts[2]->addSpacing(11);
    _text3 = new ElaText("满", 17, this);
    _text4 = new ElaText("减", 17, this);
    _text3->setFixedSize(30, 36);
    _text4->setFixedSize(30, 36);
    activityLayouts[2]->addWidget(_text3);
    activityLayouts[2]->addWidget(_edit1);
    activityLayouts[2]->addWidget(_text4);
    activityLayouts[2]->addWidget(_edit2);
    activityLayouts[2]->addSpacing(110);
    activityLayouts[2]->addStretch();

    activityLayouts[3]->addStretch();
    activityLayouts[3]->addWidget(activityText);
    activityLayouts[3]->addSpacing(11);
    _text5 = new ElaText("赠", 17, this);
    _text5->setFixedSize(30, 36);
    activityLayouts[3]->addWidget(_text3);
    activityLayouts[3]->addWidget(_edit1);
    activityLayouts[3]->addWidget(_text5);
    activityLayouts[3]->addWidget(_edit2);
    activityLayouts[3]->addSpacing(110);
    activityLayouts[3]->addStretch();

    activityLayouts[4]->addStretch();
    activityLayouts[4]->addWidget(activityText);
    activityLayouts[4]->addSpacing(11);
    _text6 = new ElaText("限量", 17, this);
    _text7 = new ElaText("件", 17, this);
    _text8 = new ElaText("元", 17, this);
    _text6->setFixedSize(40, 36);
    _text7->setFixedSize(30, 36);
    _text8->setFixedSize(30, 36);
    _edit1->setFixedSize(40, 36);
    _edit1->setClearButtonEnabled(false);
    _edit2->setFixedSize(40, 36);
    _edit2->setClearButtonEnabled(false);
    activityLayouts[4]->addWidget(_text6);
    activityLayouts[4]->addWidget(_edit1);
    activityLayouts[4]->addWidget(_text7);
    activityLayouts[4]->addWidget(_edit2);
    activityLayouts[4]->addWidget(_text8);
    activityLayouts[4]->addSpacing(65);
    activityLayouts[4]->addStretch();

    _edit1->hide();
    _edit2->hide();
    _text1->show();
    _text2->hide();
    _text3->hide();
    _text4->hide();
    _text5->hide();
    _text6->hide();
    _text7->hide();
    _text7->hide();
    _text8->hide();
}

void ProductPage::refreshPage(Product *pProduct)
{
    _edit1->setText("");
    _edit2->setText("");
    imagePath = "";
    nameEdit->setText("");
    priceEdit->setText("");
    numEdit->setText("");

    initPage(pProduct);
}
