#ifndef ORDERPAGE_H
#define ORDERPAGE_H


#include "ElaWidget.h"

class Client;
class Product;
class Order;
class OrderList;
class QVBoxLayout;
class ElaPushButton;
class ElaText;
class ElaContentDialog;
class OrderPage : public ElaWidget
{
    Q_OBJECT
public:
    explicit OrderPage(Client *cClient, QList<QPair<Product *, int> > sSelectList, QWidget* parent = nullptr);
    ~OrderPage();

public:
    void createOrder();

    void createOrderList(int oid);

private slots:
    void onConfirmBtnClicked();
    void onRightBtnClicked();
    void onMiddleBtnClicked();

private:
    Client *client;
    QVBoxLayout *centerLayout;
    ElaPushButton *confirmBtn;
    Order* order;
    QList<OrderList *> orderLists;
    QList<QPair<Product *, int> > selectList;
    ElaText *totText;
    ElaText *deltaText;
    double totPrice;
    double deltaPrice;
    ElaContentDialog *payDialog;

signals:
    void sigSendToServer(QByteArray array);
    void sigSendMessageBar(bool success, QString Title, QString subTitle = "");
    void sigRefreshPage();
};

#endif // ORDERPAGE_H
