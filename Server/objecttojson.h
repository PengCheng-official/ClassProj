#ifndef OBJECTTOJSON_H
#define OBJECTTOJSON_H

//解析json类和转换json类
#include <QObject>

class QJsonObject;
class Client;
class Product;
class Chat;
class Shopping;
class Order;
class OrderList;

class ObjectToJson
{
public:
    ObjectToJson();
    static QJsonObject addSignal(QJsonObject &object,QString signal);
    static QJsonObject addStrings(QJsonObject &object, QList<QString> strings);
    static QJsonObject addNums(QJsonObject &object, QList<int> numbers);
    static QJsonObject addClients(QJsonObject &object, QList<Client *> clients);
    static QJsonObject addChats(QJsonObject &object, QList<Chat *> chats);
    static QJsonObject addProducts(QJsonObject &object, QList<Product *> products);
    static QJsonObject addShoppings(QJsonObject &object, QList<Shopping *> shoppings);
    static QJsonObject addOrders(QJsonObject &object, QList<Order *> orderList);
    static QJsonObject addOrderLists(QJsonObject &object, QList<OrderList *> orderLists);
//    static QJsonObject integrateProductList(QJsonObject &object,QList<Product*>ProductList);
//    static QJsonObject integrateProductTypeList(QJsonObject &object,QList<ProductType*>ProductTypeList);
//    static QJsonObject integrateOrderList(QJsonObject &object,QList<Order*>OrderList);
//    static QJsonObject integrateObjects(QJsonObject &object,int number,QString string);

    static QString parseSignal(QByteArray byteArray);
    static QList<QString> parseStrings(QByteArray byteArray);
    static QList<int> parseNums(QByteArray byteArray);
    static QList<Client *> parseClients(QByteArray byteArray);
    static QList<Chat *> parseChats(QByteArray byteArray);
    static QList<Product *> parseProducts(QByteArray byteArray);
    static QList<Shopping *> parseShoppings(QByteArray byteArray);
    static QList<Order *> parseOrders(QByteArray byteArray);
    static QList<OrderList *> parseOrderLists(QByteArray byteArray);
//    static QList<Product*> parseProduct(QByteArray object);
//    static QList<ProductType*> parseProductType(QByteArray object);
//    static QList<Order*> parseOrder(QByteArray object);
//    static void parseObjects(QByteArray object);

    static QByteArray changeJson(QJsonObject& object);
};

#endif // OBJECTTOJSON_H
