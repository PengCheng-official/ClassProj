#ifndef SEARCH_H
#define SEARCH_H

#include <QString>
#include <QTime>
#include <QDateTime>

class Search
{
private:
    int clientId;
    int productId;
    QString searchTime;   //toString("yyyy-MM-dd hh:mm:ss")
    int searchCount;

public:
    Search();
    Search(int cId, int pId, QString sTime, int sCount);

    int getClientId() const;
    int getProductId() const;
    QString getSearchTime() const;
    int getSearchCount() const;

    void setClientId(int value);
    void setProductId(int value);
    void setSearchTime(const QString &value);
    void setSearchCount(int value);
};

#endif // SEARCH_H
