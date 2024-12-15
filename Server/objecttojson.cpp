﻿#include "objecttojson.h"

ObjectToJson::ObjectToJson()
{

}

QJsonObject ObjectToJson::addClientList(QJsonObject &object, QList<Client *> clientList)
{
    QJsonObject* objectList;
    QJsonArray array;
    int size = clientList.size();
    objectList = new QJsonObject[size];
    for (int i = 0; i < size; i++) {
        objectList[i].insert("clientId", clientList[i]->getClientId());
        objectList[i].insert("clientName", clientList[i]->getClientName());
        objectList[i].insert("clientSalt", clientList[i]->getClientSalt());
        objectList[i].insert("clientPhone", clientList[i]->getClientPhone());
        objectList[i].insert("clientEmail", clientList[i]->getClientEmail());
        objectList[i].insert("clientAddr", clientList[i]->getClientAddr());
        objectList[i].insert("clientPwd", clientList[i]->getClientPwd());
        objectList[i].insert("clientGender", clientList[i]->getClientGender());
        objectList[i].insert("clientImage", clientList[i]->getClientImage());

        array.append(objectList[i]);
    }
    object.insert("ClientList", QJsonValue(array));
    return object;
}

QJsonObject ObjectToJson::addChatList(QJsonObject &object, QList<Chat *> chatList)
{
    QJsonObject* objectList;
    QJsonArray array;
    int size = chatList.size();
    objectList = new QJsonObject[size];
    for (int i=0;i<size;i++) {
        objectList[i].insert("clientId", chatList[i]->getClientId());
        objectList[i].insert("chatText", chatList[i]->getChatText());
        objectList[i].insert("chatIsserver", chatList[i]->getChatIsserver());
        objectList[i].insert("chatTime", chatList[i]->getChatTime());
        array.append(objectList[i]);
    }
    object.insert("ChatList", QJsonValue(array));
    return object;
}

QJsonObject ObjectToJson::addProductList(QJsonObject &object, QList<Product *> productList)
{
    QJsonObject* objectList;
    QJsonArray array;
    int size = productList.size();
    objectList = new QJsonObject[size];
    for (int i=0;i<size;i++) {
        objectList[i].insert("productId", productList[i]->getProductId());
        objectList[i].insert("productName", productList[i]->getProductName());
        objectList[i].insert("productPrice", productList[i]->getProductPrice());
        objectList[i].insert("productNum", productList[i]->getProductNum());
        objectList[i].insert("productSales", productList[i]->getProductSales());
        objectList[i].insert("productAbout", productList[i]->getProductAbout());
        objectList[i].insert("productStrategy", productList[i]->getStrategy());
        objectList[i].insert("productNum1", productList[i]->getStrategy1());
        objectList[i].insert("productNum2", productList[i]->getStrategy2());
        objectList[i].insert("productImage", productList[i]->getProductImage());
        array.append(objectList[i]);
    }
    object.insert("ProductList", QJsonValue(array));
    return object;
}

QJsonObject ObjectToJson::addShoppingList(QJsonObject &object, QList<Shopping *> shoppingList)
{
    QJsonObject* objectList;
    QJsonArray array;
    int size = shoppingList.size();
    objectList = new QJsonObject[size];
    for (int i=0;i<size;i++) {
        objectList[i].insert("shoppingId", shoppingList[i]->getShoppingId());
        objectList[i].insert("clientId", shoppingList[i]->getClientId());
        objectList[i].insert("productId", shoppingList[i]->getProductId());
        objectList[i].insert("shoppingNum", shoppingList[i]->getShoppingNum());
        objectList[i].insert("shoppingPrice", shoppingList[i]->getShoppingPrice());
        array.append(objectList[i]);
    }
    object.insert("ShoppingList", QJsonValue(array));
    return object;
}

//QJsonObject ObjectToJson::integrateOrderList(QJsonObject &object, QList<Order *> OrderList)
//{
////    QJsonObject object;
//    QJsonObject* objectList;
//    QJsonArray array;
//    int size = OrderList.size();
//    objectList = new QJsonObject[size];
//        for (int i=0;i<size;i++) {
//            objectList[i].insert("orderId",OrderList[i]->getOrderId());
//            objectList[i].insert("orderProductName",OrderList[i]->getOrderProductName());
//            objectList[i].insert("orderProductNum",OrderList[i]->getOrderProductNum());
//            objectList[i].insert("orderProductStyle",OrderList[i]->getOrderProductStyle());
//            objectList[i].insert("orderProductId",OrderList[i]->getOrderProductId());
//            objectList[i].insert("orderCost",OrderList[i]->getOrderCost());
//            objectList[i].insert("orderTime",OrderList[i]->getOrderTime().toString());
//            objectList[i].insert("orderClient",OrderList[i]->getOrderClient());
//            objectList[i].insert("orderClientId",OrderList[i]->getOrderClientId());
//            objectList[i].insert("orderCheck",OrderList[i]->getOrderCheck());
//            objectList[i].insert("orderHide",OrderList[i]->getOrderHide());
//            array.append(objectList[i]);
//        }
////    object.insert("signal",signal);
//    object.insert("OrderList",QJsonValue(array));
//    return object;
//}

//QJsonObject ObjectToJson::integrateObjects(QJsonObject &object, int number, QString string)
//{
//    //    QJsonObject object;
//    //    object.insert("signal",signal);
//    object.insert("number",number);
//    object.insert("string",string);
//    return object;
//}

QJsonObject ObjectToJson::addStrings(QJsonObject &object, QList<QString> strings)
{
    for (int i = 0; i < strings.size(); i++) {
        object.insert(QString("string%1").arg(i), strings[i]);
    }
    return object;
}

QJsonObject ObjectToJson::addNums(QJsonObject &object, QList<int> numbers)
{
    for (int i = 0; i < numbers.size(); i++) {
        object.insert(QString("number%1").arg(i), numbers[i]);
    }
    return object;
}

QJsonObject ObjectToJson::addSignal(QJsonObject &object, QString signal)
{
    object.insert("signal",signal);
    return object;
}

QString ObjectToJson::parseSignal(QByteArray byteArray)
{
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)){
        if(doucment.isObject()){
            QJsonObject object = doucment.object();
            if(object.contains("signal")){
                QJsonValue value =object.value("signal");
                return value.toString();
            }
        }
    }
    return "";
}

QList<Client *> ObjectToJson::parseClient(QByteArray byteArray)
{
    QJsonParseError jsonError;
    QList<Client *> clientList;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        if (doucment.isObject())
        {
            QJsonObject object = doucment.object();
            if (object.contains("ClientList"))
            {
                QJsonValue value = object.value("ClientList");
                if (value.isArray())
                {
                    QJsonArray array = value.toArray();
                    int size = array.size();
                    for (int i = 0; i < size; i++)
                    {
                        if (array[i].isObject()){
                            QJsonObject jsonObject = array[i].toObject();
                            Client * client = new Client;
                            if(jsonObject.contains("clientName")){
                                QJsonValue object = jsonObject.value("clientName");
                                client->setClientName(object.toString());
                            }
                            if(jsonObject.contains("clientId")){
                                QJsonValue object = jsonObject.value("clientId");
                                client->setClientId(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("clientPhone")){
                                QJsonValue object = jsonObject.value("clientPhone");
                                client->setClientPhone(object.toString());
                            }
                            if(jsonObject.contains("clientEmail")){
                                QJsonValue object = jsonObject.value("clientEmail");
                                client->setClientEmail(object.toString());
                            }
                            if(jsonObject.contains("clientAddr")){
                                QJsonValue object = jsonObject.value("clientAddr");
                                client->setClientAddr(object.toString());
                            }
                            if(jsonObject.contains("clientPwd")){
                                QJsonValue object = jsonObject.value("clientPwd");
                                client->setClientPwd(object.toString());
                            }
                            if(jsonObject.contains("clientSalt")){
                                QJsonValue object = jsonObject.value("clientSalt");
                                client->setClientSalt(object.toString());
                            }
                            if(jsonObject.contains("clientGender")){
                                QJsonValue object = jsonObject.value("clientGender");
                                client->setClientGender(object.toString());
                            }
                            if(jsonObject.contains("clientImage")){
                                QJsonValue object = jsonObject.value("clientImage");
                                client->setClientImage(object.toString());
                            }
                            clientList.append(client);
                        }
                    }
                }
            }
        }
    }
    return clientList;
}

QList<Chat *> ObjectToJson::parseChat(QByteArray byteArray)
{
    QJsonParseError jsonError;
    QList<Chat *> chatList;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        if (doucment.isObject())
        {
            QJsonObject object = doucment.object();
            if (object.contains("ChatList")){
                QJsonValue value = object.value("ChatList");
                if (value.isArray())
                {
                    QJsonArray array = value.toArray();
                    int size = array.size();
                    for (int i = 0; i < size; i++)
                    {
                        if(array[i].isObject()){
                            QJsonObject jsonObject = array[i].toObject();
                            Chat * chat = new Chat;
                            if(jsonObject.contains("clientId")){
                                QJsonValue object = jsonObject.value("clientId");
                                chat->setClientId(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("chatText")){
                                QJsonValue object = jsonObject.value("chatText");
                                chat->setChatText(object.toString());
                            }
                            if(jsonObject.contains("chatIsserver")){
                                QJsonValue object = jsonObject.value("chatIsserver");
                                chat->setChatIsserver(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("chatTime")){
                                QJsonValue object = jsonObject.value("chatTime");
                                chat->setChatTime(object.toString());
                            }
                            chatList.append(chat);
                        }
                    }
                }
            }
        }
    }
    return chatList;
}

QList<Product *> ObjectToJson::parseProduct(QByteArray byteArray)
{
    QJsonParseError jsonError;
    QList<Product *> productList;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        if (doucment.isObject())
        {
            QJsonObject object = doucment.object();
            if (object.contains("ProductList")){
                QJsonValue value = object.value("ProductList");
                if (value.isArray())
                {
                    QJsonArray array = value.toArray();
                    int size = array.size();
                    for (int i = 0; i < size; i++)
                    {
                        if(array[i].isObject()){
                            QJsonObject jsonObject = array[i].toObject();
                            Product * product = new Product;
                            if(jsonObject.contains("productId")){
                                QJsonValue object = jsonObject.value("productId");
                                product->setProductId(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("productName")){
                                QJsonValue object = jsonObject.value("productName");
                                product->setProductName(object.toString());
                            }
                            if(jsonObject.contains("productPrice")){
                                QJsonValue object = jsonObject.value("productPrice");
                                product->setProductPrice(object.toVariant().toDouble());
                            }
                            if(jsonObject.contains("productNum")){
                                QJsonValue object = jsonObject.value("productNum");
                                product->setProductNum(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("productSales")){
                                QJsonValue object = jsonObject.value("productSales");
                                product->setProductSales(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("productAbout")){
                                QJsonValue object = jsonObject.value("productAbout");
                                product->setProductAbout(object.toString());
                            }
                            if(jsonObject.contains("productStrategy")){
                                QJsonValue object = jsonObject.value("productStrategy");
                                QJsonValue object1 = jsonObject.value("productNum1");
                                QJsonValue object2 = jsonObject.value("productNum1");
                                product->setStrategy(object.toVariant().toInt(), object1.toVariant().toDouble(), object2.toVariant().toDouble());
                            }
                            if(jsonObject.contains("productImage")){
                                QJsonValue object = jsonObject.value("productImage");
                                product->setProductImage(object.toString());
                            }
                            productList.append(product);
                        }
                    }
                }
            }
        }
    }
    return productList;
}

QList<Shopping *> ObjectToJson::parseShopping(QByteArray byteArray)
{
    QJsonParseError jsonError;
    QList<Shopping *> shoppingList;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        if (doucment.isObject())
        {
            QJsonObject object = doucment.object();
            if (object.contains("ShoppingList")){
                QJsonValue value = object.value("ShoppingList");
                if (value.isArray())
                {
                    QJsonArray array = value.toArray();
                    int size = array.size();
                    for (int i = 0; i < size; i++)
                    {
                        if(array[i].isObject()){
                            QJsonObject jsonObject = array[i].toObject();
                            Shopping * shopping = new Shopping;
                            if(jsonObject.contains("shoppingId")){
                                QJsonValue object = jsonObject.value("shoppingId");
                                shopping->setShoppingId(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("clientId")){
                                QJsonValue object = jsonObject.value("clientId");
                                shopping->setClientId(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("productId")){
                                QJsonValue object = jsonObject.value("productId");
                                shopping->setProductId(object.toVariant().toDouble());
                            }
                            if(jsonObject.contains("shoppingNum")){
                                QJsonValue object = jsonObject.value("shoppingNum");
                                shopping->setShoppingNum(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("shoppingPrice")){
                                QJsonValue object = jsonObject.value("shoppingPrice");
                                shopping->setShoppingPrice(object.toVariant().toDouble());
                            }
                            shoppingList.append(shopping);
                        }
                    }
                }
            }
        }
    }
    return shoppingList;
}

//QList<Order *> ObjectToJson::parseOrder(QByteArray byteArray)
//{
//    QJsonParseError jsonError;
//    QList<Order*> orderList;
//    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
//    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)){
//           if (doucment.isObject()){
//                QJsonObject object = doucment.object();
//                if(object.contains("OrderList")){
//                    QJsonValue value = object.value("OrderList");
//                    if(value.isArray()){
//                        QJsonArray array = value.toArray();
//                        int size = array.size();
//                        for(int i=0;i<size;i++){
//                            if(array[i].isObject()){
//                                QJsonObject orderObject = array[i].toObject();
//                                Order * order = new Order;
//                                if(orderObject.contains("orderProductName")){
//                                    QJsonValue object = orderObject.value("orderProductName");
//                                    order->setOrderProductName(object.toString());
//                                }
//                                if(orderObject.contains("orderId")){
//                                    QJsonValue object = orderObject.value("orderId");
//                                    order->setOrderId(object.toVariant().toInt());
//                                }
//                                if(orderObject.contains("orderProductId")){
//                                    QJsonValue object = orderObject.value("orderProductId");
//                                    order->setOrderProductId(object.toVariant().toInt());
//                                }
//                                if(orderObject.contains("orderProductNum")){
//                                    QJsonValue object = orderObject.value("orderProductNum");
//                                    order->setOrderProductNum(object.toVariant().toInt());
//                                }
//                                if(orderObject.contains("orderProductStyle")){
//                                    QJsonValue object = orderObject.value("orderProductStyle");
//                                    order->setOrderProductStyle(object.toString());
//                                }
//                                if(orderObject.contains("orderTime")){
//                                    QJsonValue object = orderObject.value("orderTime");
//                                    order->setOrderTime(QDateTime::currentDateTime());
//                                }
//                                if(orderObject.contains("orderCost")){
//                                    QJsonValue object = orderObject.value("orderCost");
//                                    order->setOrderCost(object.toString());
//                                }
//                                if(orderObject.contains("orderClient")){
//                                    QJsonValue object = orderObject.value("orderClient");
//                                    order->setOrderClient(object.toString());
//                                }
//                                if(orderObject.contains("orderClientId")){
//                                    QJsonValue object = orderObject.value("orderClientId");
//                                    order->setOrderClientId(object.toVariant().toInt());
//                                }
//                                if(orderObject.contains("orderCheck")){
//                                    QJsonValue object = orderObject.value("orderCheck");
//                                    order->setOrderCheck(object.toVariant().toInt());
//                                }
//                                if(orderObject.contains("orderHide")){
//                                    QJsonValue object = orderObject.value("orderHide");
//                                    order->setOrderHide(object.toVariant().toInt());
//                                }
//                                orderList.append(order);
//                            }
//                        }
//                    }
//                }
//           }
//    }return orderList;
//}



QList<int> ObjectToJson::parseNums(QByteArray byteArray)
{
    QList<int> ret;

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)){
        if (doucment.isObject()){
            QJsonObject object = doucment.object();
            for (int i = 0; ; i++)
            {
                QString name = QString("number%1").arg(i);
                if (object.contains(name)) {
                    QJsonValue value = object.value(name);
                    ret.append(value.toVariant().toInt());
                }
                else break;
            }
        }
    }
    return ret;
}

//void ObjectToJson::parseObjects(QByteArray byteArray)
//{
//    QJsonParseError jsonError;
//    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
//    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)){
//        if (doucment.isObject()){
//            QJsonObject object = doucment.object();
//            if(object.contains("number")){
//                QJsonValue value = object.value("number");
//                number = value.toVariant().toInt();
//            }
//            if(object.contains("string")){
//                QJsonValue value = object.value("string");
//                string = value.toString();
//            }
//        }
//    }
//}

QList<QString> ObjectToJson::parseStrings(QByteArray byteArray)
{
    QList<QString> ret;

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)){
        if (doucment.isObject()){
            QJsonObject object = doucment.object();
            for (int i = 0; ; i++)
            {
                QString name = QString("string%1").arg(i);
                if (object.contains(name)) {
                    QJsonValue value = object.value(name);
                    ret.append(value.toString());
                }
                else break;
            }
        }
    }
    return ret;
}

QByteArray ObjectToJson::changeJson(QJsonObject &object)
{
    QJsonDocument document;
    document.setObject(object);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    return byteArray;
}


