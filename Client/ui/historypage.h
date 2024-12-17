#ifndef HISTORYPAGE_H
#define HISTORYPAGE_H


#include "basepage.h"

class Order;
class OrderList;
class HistoryPage : public BasePage
{
    Q_OBJECT
public:
    explicit HistoryPage(Client *cClient, QWidget* parent = nullptr);
    ~HistoryPage();

    void refreshPage(QList<Order *> orders, QList<Product *> products);
    // 传入的 product 需要特殊含义：price 订单中的价格，num 订单中的数量

private:
    void initPage();
};

#endif // HISTORYPAGE_H
