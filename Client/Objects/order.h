#ifndef ORDER_H
#define ORDER_H


#include <QString>

class Order
{
private:
    int clientId;
    double totalPrice;
    QString orderStatus;
    // ENUM{'未支付', '已支付', '已完成', '已取消', '已退款'}
    QString createTime;
    QString finishTime;

public:
    Order();
    Order(int cId, double totPrice, QString oStatus, QString cTime, QString fTime);

    int getClientId() const;
    double getTotalPrice() const;
    QString getCreateTime() const;
    QString getFinishTime() const;

    void setClientId(int value);
    void setTotalPrice(double value);
    void setCreateTime(const QString &value);
    void setFinishTime(const QString &value);
};

#endif // ORDER_H
