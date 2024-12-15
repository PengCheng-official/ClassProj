#ifndef ORDERPAGE_H
#define ORDERPAGE_H


#include "basepage.h"
#include <QTime>

class OrderPage : public BasePage
{
    Q_OBJECT
public:
    explicit OrderPage(Client *cClient, QList<QPair<Product *, int> > selectList, QWidget* parent = nullptr);
    ~OrderPage();

private slots:
    void onConfirmBtnClicked();

private:
    ElaPushButton *confirmBtn;
    Order* order;
    QList<OrderList *> orderList;
    ElaText *totText;
    ElaText *deltaText;
    double totPrice;
    double deltaPrice;
};

#endif // ORDERPAGE_H
