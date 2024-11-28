#ifndef OBJECTTOJSON_H
#define OBJECTTOJSON_H
#include "objects/client.h"
#include "objects/chat.h"
#include "objects/order.h"
#include "objects/orderlist.h"
#include "objects/product.h"
#include "objects/search.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QString>
#include <QList>
#include <QByteArray>
#include <QJsonValue>
#include <QVariant>

//解析json类和转换json类

class ObjectToJson
{
public:
    ObjectToJson();
    static QJsonObject addSignal(QJsonObject &object,QString signal);
    static QJsonObject addStrings(QJsonObject &object, QList<QString> strings);
    static QJsonObject addNums(QJsonObject &object, QList<int> numbers);
    static QJsonObject addClientList(QJsonObject &object, QList<Client *> clientList);
    static QJsonObject addChatList(QJsonObject &object, QList<Chat *> chatList);
//    static QJsonObject integrateProductList(QJsonObject &object,QList<Product*>ProductList);
//    static QJsonObject integrateProductTypeList(QJsonObject &object,QList<ProductType*>ProductTypeList);
//    static QJsonObject integrateOrderList(QJsonObject &object,QList<Order*>OrderList);
//    static QJsonObject integrateObjects(QJsonObject &object,int number,QString string);

    static QString parseSignal(QByteArray object);
    static QList<QString> parseStrings(QByteArray object);
    static QList<int> parseNums(QByteArray object);
    static QList<Client *> parseClient(QByteArray object);
    static QList<Chat *> parseChat(QByteArray object);
//    static QList<Product*> parseProduct(QByteArray object);
//    static QList<ProductType*> parseProductType(QByteArray object);
//    static QList<Order*> parseOrder(QByteArray object);
//    static void parseObjects(QByteArray object);

    static QByteArray changeJson(QJsonObject& object);
};

#endif // OBJECTTOJSON_H
