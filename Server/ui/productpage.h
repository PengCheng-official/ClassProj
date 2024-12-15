#ifndef PRODUCTPAGE_H
#define PRODUCTPAGE_H


#include <ElaScrollPage.h>
#include <ElaScrollPageArea.h>
#include "objects/objects.h"
#include "objecttojson.h"
#include "ElaMenu.h"
#include "ElaText.h"
#include "ElaWindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QVBoxLayout>
#include "ElaLineEdit.h"
#include "ElaToggleButton.h"
#include "ElaPushButton.h"
#include <QFileDialog>
#include "ElaComboBox.h"
#include "ElaPlainTextEdit.h"
#include "ElaTheme.h"
#include "dao/productmapper.h"
#include "statement.h"

class ProductPage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit ProductPage(QWidget* parent = nullptr);
    ~ProductPage();

    void refreshPage(Product *pProduct = nullptr);

private:
    void createActivityLayout(ElaText *activityText);
    void connectToDB();
    void initPage(Product *pProduct = nullptr);

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
    ElaText *_text8;
    QList<QHBoxLayout *> activityLayouts{nullptr, nullptr, nullptr, nullptr, nullptr};
    bool IsNew;
    ElaPushButton *deleteBtn;
    QSqlDatabase db;

private slots:
    void onCurrentIndexChanged(int cur);
    void onConFirmBtnClicked();
    void onDeleteBtnClicked();

signals:
    void sigCreateFail(int signal);

};

#endif // PRODUCTPAGE_H
