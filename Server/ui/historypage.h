#ifndef HISTORYPAGE_H
#define HISTORYPAGE_H


#include "ElaScrollPage.h"
#include <QSqlDatabase>

class Product;
class Order;
class QVBoxLayout;
class HistoryPage : public ElaScrollPage
{
    Q_OBJECT
public:
    explicit HistoryPage(QWidget* parent = nullptr);
    ~HistoryPage();

    void refreshPage(QList<Order *> orders, QList<Product *> products);
    // 传入的 product 需要特殊含义：price 订单中的价格，num 订单中的数量

private:
    void initPage();

    void clearPage(int left);

    void connectToDB();

private:
    QSqlDatabase db;
    QWidget *centralWidget;
    QVBoxLayout *centerLayout;

};

#endif // HISTORYPAGE_H
