#ifndef SHOPPINGPAGE_H
#define SHOPPINGPAGE_H


#include "basepage.h"

class Shopping;
class ElaPushButton;
class ElaSpinBox;
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
    void sigRefreshPage();
    void sigSendMessageBar(bool success, QString Title, QString subTitle = "");
};

#endif // SHOPPINGPAGE_H
