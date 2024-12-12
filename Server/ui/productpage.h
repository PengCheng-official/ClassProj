#ifndef PRODUCTPAGE_H
#define PRODUCTPAGE_H


#include <ElaScrollPage.h>
#include <ElaScrollPageArea.h>
#include "objects/objects.h"
#include "objecttojson.h"
#include "ElaMenu.h"
#include "ElaText.h"
#include "ElaWindow.h"
#include <QHBoxLayout>
#include <QHeaderView>
#include <QVBoxLayout>
#include "ElaLineEdit.h"
#include "ElaToggleButton.h"
#include "ElaPushButton.h"
#include <QFileDialog>
#include "ElaComboBox.h"
#include "ElaPlainTextEdit.h"

class ProductPage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit ProductPage(QWidget* parent = nullptr);
    ~ProductPage();

    void initPage(Product *product = nullptr);

private:
    void createActivityLayout(ElaText *activityText);

private:
    Product *product;
    QWidget *centralWidget;
    QVBoxLayout *centerLayout;
    ElaLineEdit *nameEdit;
    ElaLineEdit *priceEdit;
    ElaLineEdit *numEdit;
    ElaComboBox *strategyBox;
    ElaPushButton *confirmBtn;
    ElaPushButton *imageBtn;
    QString imagePath{""};
    ElaPlainTextEdit *aboutEdit;
    ElaLineEdit *_edit1;
    ElaLineEdit *_edit2;
    ElaText *_text1;
    ElaText *_text2;
    ElaText *_text3;
    ElaText *_text4;
    ElaText *_text5;
    ElaText *_text6;
    ElaText *_text7;
    QList<QHBoxLayout *> activityLayouts{nullptr, nullptr, nullptr, nullptr, nullptr};

private slots:
    void onCurrentIndexChanged(int cur);

signals:
    void onConFirmBtnClicked();
};

#endif // PRODUCTPAGE_H
