#ifndef ORDERPAGE_H
#define ORDERPAGE_H


#include "ElaWidget.h"
#include "basepage.h"
#include <QTime>
#include "ElaContentDialog.h"
#include <QThread>

class OrderPage : public ElaWidget
{
    Q_OBJECT
public:
    explicit OrderPage(Client *cClient, QList<QPair<Product *, int> > sSelectList, QWidget* parent = nullptr);
    ~OrderPage();

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
    QList<OrderList *> orderList;
    QList<QPair<Product *, int> > selectList;
    ElaText *totText;
    ElaText *deltaText;
    double totPrice;
    double deltaPrice;
    ElaContentDialog *payDialog;

signals:
    void sigSendToServer(QByteArray array);
};

#endif // ORDERPAGE_H
