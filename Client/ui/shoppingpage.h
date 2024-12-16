#ifndef SHOPPINGPAGE_H
#define SHOPPINGPAGE_H


#include "basepage.h"
#include "ElaCheckBox.h"
#include "ElaSpinBox.h"
#include <QPair>
#include <QMap>
#include "orderpage.h"
#include "allmain.h"

class ShoppingPage : public BasePage
{
    Q_OBJECT
public:
    explicit ShoppingPage(Client *cClient, QWidget* parent = nullptr);
    ~ShoppingPage();

    void refreshPage(QList<Product *> productList, QList<Shopping *> shoppingList);

private:
    void confirmChanged();
    void initPage();

private:
    ElaPushButton *confirmBtn;
    ElaText *totText;
    ElaText *deltaText;
    double totPrice;
    double deltaPrice;
    int checkNum;
    QMap<ElaSpinBox *, int> spinMap;
    QList<QPair<Product *, int> > selectList;

signals:
    void sigShoppingTooMore();
    void sigShoppingTooLess();
    void sigSendMessageBar(bool success, QString Title);
};

#endif // SHOPPINGPAGE_H
