#ifndef SHOPPINGMAPPER_H
#define SHOPPINGMAPPER_H


#include "mapper.h"

class Shopping;
class ShoppingMapper : public Mapper
{
public:
    ShoppingMapper(QSqlDatabase &database);

public:
    Shopping *getShopping(const QSqlQuery &query) const;
    //DAO层，数据转对象

    QList<Shopping *> select(const int cid) const;
    //通过用户cid，查询购物车

    int select(const Shopping *shopping) const;
    //通过用户cid，查询购物车中 pid 商品的数量

    void insert(const Shopping *shopping) const;
    //插入shopping

    void insert(const QList<Shopping *> shopList) const;
    //插入多个shopping

    void update(const Shopping *shopping) const;
    //通过对应 cid 和 pid，更新shopping

    void delet(const Shopping *shopping) const;
    //删除对应 cid 和 pid 的数据

    void delet(const QList<Shopping *> shoppings) const;
    //删除多个shopping
};

#endif // SHOPPINGMAPPER_H
