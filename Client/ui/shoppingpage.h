#ifndef SHOPPINGPAGE_H
#define SHOPPINGPAGE_H


#include "basepage.h"
#include "ElaCheckBox.h"
#include "ElaSpinBox.h"

class ShoppingPage : public BasePage
{
    Q_OBJECT
public:
    explicit ShoppingPage(Client *cClient, QWidget* parent = nullptr);
    ~ShoppingPage();

    void refreshPage(QList<Product *> productList, QList<Shopping *> shoppingList);
};

#endif // SHOPPINGPAGE_H
