#ifndef PRODUCTPAGE_H
#define PRODUCTPAGE_H


#include "basepage.h"
#include <QSqlDatabase>

class Product;
class QVBoxLayout;
class ElaLineEdit;
class ElaComboBox;
class ElaPushButton;
class QLineEdit;
class ElaPlainTextEdit;
class ProductPage : public BasePage
{
    Q_OBJECT
public:
    explicit ProductPage(QWidget* parent = nullptr);
    ~ProductPage();

    void refreshPage(Product *pProduct = nullptr);

private:
    void createActivityLayout(ElaText *activityText);

    void initPage(Product *pProduct = nullptr);

private:
    Product *product;
    ElaLineEdit *nameEdit;
    ElaLineEdit *priceEdit;
    ElaLineEdit *numEdit;
    ElaComboBox *strategyBox;
    ElaPushButton *confirmBtn;
    ElaPushButton *imageBtn;
    QString imagePath{""};
    ElaPlainTextEdit *aboutEdit;
    QLineEdit *_edit1;
    QLineEdit *_edit2;
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

private slots:
    void onCurrentIndexChanged(int cur);
    void onConFirmBtnClicked();
    void onDeleteBtnClicked();

signals:
    void sigCreateFail(int signal);

};

#endif // PRODUCTPAGE_H
