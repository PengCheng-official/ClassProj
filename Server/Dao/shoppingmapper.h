#ifndef SHOPPINGMAPPER_H
#define SHOPPINGMAPPER_H


#include "mapper.h"

class ShoppingMapper : public Mapper
{
public:
    ShoppingMapper(QSqlDatabase &database);

public:
    Shopping *getShopping(const QSqlQuery &query);

    QList<Shopping *> select(const int cid);
    // 查询用户cid的购物车

    int select(const Shopping *shopping);
    // 查询用户cid购物车中pid商品的数量

    void insert(const Shopping *shopping);
    void insert(const QList<Shopping *> shopList);

    void update(const Shopping *shopping);
    // shopping中存新购物车数据 cid和pid为已存在的不变量

    void delet(const Shopping *shopping);
    void delet(const QList<Shopping *> shoppings);
    // 删除cid和pid的数据
};

#endif // SHOPPINGMAPPER_H
