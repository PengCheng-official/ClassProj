#ifndef SHOPPINGPAGE_H
#define SHOPPINGPAGE_H


#include "basepage.h"
#include "ElaCheckBox.h"
#include "ElaSpinBox.h"
#include <QPair>
#include <QMap>

class ShoppingPage : public BasePage
{
    Q_OBJECT
public:
    explicit ShoppingPage(Client *cClient, QWidget* parent = nullptr);
    ~ShoppingPage();

    void refreshPage(QList<Product *> productList, QList<Shopping *> shoppingList);

private:
    void confirmChanged();

private:
    ElaPushButton *confirmBtn;
    ElaText *totText;
    ElaText *deltaText;
    double totPrice;
    double deltaPrice;
    QMap<ElaSpinBox *, int> spinMap;
    QList<QPair<Product *, int> > selectList;
};

#endif // SHOPPINGPAGE_H
