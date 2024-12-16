#include "objecttojson.h"

ObjectToJson::ObjectToJson()
{

}

QJsonObject ObjectToJson::addClients(QJsonObject &object, QList<Client *> clients)
{
    QJsonObject* objectList;
    QJsonArray array;
    int size = clients.size();
    objectList = new QJsonObject[size];
    for (int i = 0; i < size; i++) {
        objectList[i].insert("ClientId", clients[i]->getClientId());
        objectList[i].insert("ClientName", clients[i]->getClientName());
        objectList[i].insert("ClientSalt", clients[i]->getClientSalt());
        objectList[i].insert("ClientPhone", clients[i]->getClientPhone());
        objectList[i].insert("ClientEmail", clients[i]->getClientEmail());
        objectList[i].insert("ClientAddr", clients[i]->getClientAddr());
        objectList[i].insert("ClientPwd", clients[i]->getClientPwd());
        objectList[i].insert("ClientGender", clients[i]->getClientGender());
        objectList[i].insert("ClientImage", clients[i]->getClientImage());

        array.append(objectList[i]);
    }
    object.insert("Clients", QJsonValue(array));
    return object;
}

QJsonObject ObjectToJson::addChats(QJsonObject &object, QList<Chat *> chats)
{
    QJsonObject* objectList;
    QJsonArray array;
    int size = chats.size();
    objectList = new QJsonObject[size];
    for (int i=0;i<size;i++) {
        objectList[i].insert("ClientId", chats[i]->getClientId());
        objectList[i].insert("ChatText", chats[i]->getChatText());
        objectList[i].insert("ChatIsserver", chats[i]->getChatIsserver());
        objectList[i].insert("ChatTime", chats[i]->getChatTime());
        array.append(objectList[i]);
    }
    object.insert("Chats", QJsonValue(array));
    return object;
}

QJsonObject ObjectToJson::addProducts(QJsonObject &object, QList<Product *> products)
{
    QJsonObject* objectList;
    QJsonArray array;
    int size = products.size();
    objectList = new QJsonObject[size];
    for (int i=0;i<size;i++) {
        objectList[i].insert("ProductId", products[i]->getProductId());
        objectList[i].insert("ProductName", products[i]->getProductName());
        objectList[i].insert("ProductPrice", products[i]->getProductPrice());
        objectList[i].insert("ProductNum", products[i]->getProductNum());
        objectList[i].insert("ProductSales", products[i]->getProductSales());
        objectList[i].insert("ProductAbout", products[i]->getProductAbout());
        objectList[i].insert("ProductStrategy", products[i]->getStrategy());
        objectList[i].insert("ProductNum1", products[i]->getStrategy1());
        objectList[i].insert("ProductNum2", products[i]->getStrategy2());
        objectList[i].insert("ProductImage", products[i]->getProductImage());
        array.append(objectList[i]);
    }
    object.insert("Products", QJsonValue(array));
    return object;
}

QJsonObject ObjectToJson::addShoppings(QJsonObject &object, QList<Shopping *> shoppings)
{
    QJsonObject* objectList;
    QJsonArray array;
    int size = shoppings.size();
    objectList = new QJsonObject[size];
    for (int i=0;i<size;i++) {
        objectList[i].insert("ShoppingId", shoppings[i]->getShoppingId());
        objectList[i].insert("ClientId", shoppings[i]->getClientId());
        objectList[i].insert("ProductId", shoppings[i]->getProductId());
        objectList[i].insert("ShoppingNum", shoppings[i]->getShoppingNum());
        objectList[i].insert("ShoppingPrice", shoppings[i]->getShoppingPrice());
        array.append(objectList[i]);
    }
    object.insert("Shoppings", QJsonValue(array));
    return object;
}

QJsonObject ObjectToJson::addOrders(QJsonObject &object, QList<Order *> orders)
{
    QJsonObject* objectList;
    QJsonArray array;
    int size = orders.size();
    objectList = new QJsonObject[size];
    for (int i=0;i<size;i++) {
        objectList[i].insert("OrderId", orders[i]->getOrderId());
        objectList[i].insert("ClientId", orders[i]->getClientId());
        objectList[i].insert("TotalPrice", orders[i]->getTotalPrice());
        objectList[i].insert("OrderStatus", orders[i]->getOrderStatus());
        objectList[i].insert("CreateTime", orders[i]->getCreateTime());
        objectList[i].insert("FinishTime", orders[i]->getFinishTime());
        array.append(objectList[i]);
    }
    object.insert("Orders", QJsonValue(array));
    return object;
}

QJsonObject ObjectToJson::addOrderLists(QJsonObject &object, QList<OrderList *> orderLists)
{
    QJsonObject* objectList;
    QJsonArray array;
    int size = orderLists.size();
    objectList = new QJsonObject[size];
    for (int i=0;i<size;i++) {
        objectList[i].insert("OrderListId", orderLists[i]->getOrderListId());
        objectList[i].insert("OrderId", orderLists[i]->getOrderId());
        objectList[i].insert("ProductId", orderLists[i]->getProductId());
        objectList[i].insert("ProductNum", orderLists[i]->getProductNum());
        objectList[i].insert("ProductPrice", orderLists[i]->getProductPrice());
        array.append(objectList[i]);
    }
    object.insert("OrderLists", QJsonValue(array));
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

QList<Client *> ObjectToJson::parseClients(QByteArray byteArray)
{
    QJsonParseError jsonError;
    QList<Client *> clientList;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        if (doucment.isObject())
        {
            QJsonObject object = doucment.object();
            if (object.contains("Clients"))
            {
                QJsonValue value = object.value("Clients");
                if (value.isArray())
                {
                    QJsonArray array = value.toArray();
                    int size = array.size();
                    for (int i = 0; i < size; i++)
                    {
                        if (array[i].isObject()){
                            QJsonObject jsonObject = array[i].toObject();
                            Client * client = new Client;
                            if(jsonObject.contains("ClientName")){
                                QJsonValue object = jsonObject.value("ClientName");
                                client->setClientName(object.toString());
                            }
                            if(jsonObject.contains("ClientId")){
                                QJsonValue object = jsonObject.value("ClientId");
                                client->setClientId(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("ClientPhone")){
                                QJsonValue object = jsonObject.value("ClientPhone");
                                client->setClientPhone(object.toString());
                            }
                            if(jsonObject.contains("ClientEmail")){
                                QJsonValue object = jsonObject.value("ClientEmail");
                                client->setClientEmail(object.toString());
                            }
                            if(jsonObject.contains("ClientAddr")){
                                QJsonValue object = jsonObject.value("ClientAddr");
                                client->setClientAddr(object.toString());
                            }
                            if(jsonObject.contains("ClientPwd")){
                                QJsonValue object = jsonObject.value("ClientPwd");
                                client->setClientPwd(object.toString());
                            }
                            if(jsonObject.contains("ClientSalt")){
                                QJsonValue object = jsonObject.value("ClientSalt");
                                client->setClientSalt(object.toString());
                            }
                            if(jsonObject.contains("ClientGender")){
                                QJsonValue object = jsonObject.value("ClientGender");
                                client->setClientGender(object.toString());
                            }
                            if(jsonObject.contains("ClientImage")){
                                QJsonValue object = jsonObject.value("ClientImage");
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

QList<Chat *> ObjectToJson::parseChats(QByteArray byteArray)
{
    QJsonParseError jsonError;
    QList<Chat *> chatList;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        if (doucment.isObject())
        {
            QJsonObject object = doucment.object();
            if (object.contains("Chats")){
                QJsonValue value = object.value("Chats");
                if (value.isArray())
                {
                    QJsonArray array = value.toArray();
                    int size = array.size();
                    for (int i = 0; i < size; i++)
                    {
                        if(array[i].isObject()){
                            QJsonObject jsonObject = array[i].toObject();
                            Chat * chat = new Chat;
                            if(jsonObject.contains("ClientId")){
                                QJsonValue object = jsonObject.value("ClientId");
                                chat->setClientId(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("ChatText")){
                                QJsonValue object = jsonObject.value("ChatText");
                                chat->setChatText(object.toString());
                            }
                            if(jsonObject.contains("ChatIsserver")){
                                QJsonValue object = jsonObject.value("ChatIsserver");
                                chat->setChatIsserver(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("ChatTime")){
                                QJsonValue object = jsonObject.value("ChatTime");
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

QList<Product *> ObjectToJson::parseProducts(QByteArray byteArray)
{
    QJsonParseError jsonError;
    QList<Product *> productList;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        if (doucment.isObject())
        {
            QJsonObject object = doucment.object();
            if (object.contains("Products")){
                QJsonValue value = object.value("Products");
                if (value.isArray())
                {
                    QJsonArray array = value.toArray();
                    int size = array.size();
                    for (int i = 0; i < size; i++)
                    {
                        if(array[i].isObject()){
                            QJsonObject jsonObject = array[i].toObject();
                            Product * product = new Product;
                            if(jsonObject.contains("ProductId")){
                                QJsonValue object = jsonObject.value("ProductId");
                                product->setProductId(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("ProductName")){
                                QJsonValue object = jsonObject.value("ProductName");
                                product->setProductName(object.toString());
                            }
                            if(jsonObject.contains("ProductPrice")){
                                QJsonValue object = jsonObject.value("ProductPrice");
                                product->setProductPrice(object.toVariant().toDouble());
                            }
                            if(jsonObject.contains("ProductNum")){
                                QJsonValue object = jsonObject.value("ProductNum");
                                product->setProductNum(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("ProductSales")){
                                QJsonValue object = jsonObject.value("ProductSales");
                                product->setProductSales(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("ProductAbout")){
                                QJsonValue object = jsonObject.value("ProductAbout");
                                product->setProductAbout(object.toString());
                            }
                            if(jsonObject.contains("ProductStrategy")){
                                QJsonValue object = jsonObject.value("ProductStrategy");
                                QJsonValue object1 = jsonObject.value("ProductNum1");
                                QJsonValue object2 = jsonObject.value("ProductNum1");
                                product->setStrategy(object.toVariant().toInt(), object1.toVariant().toDouble(), object2.toVariant().toDouble());
                            }
                            if(jsonObject.contains("ProductImage")){
                                QJsonValue object = jsonObject.value("ProductImage");
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

QList<Shopping *> ObjectToJson::parseShoppings(QByteArray byteArray)
{
    QJsonParseError jsonError;
    QList<Shopping *> shoppingList;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        if (doucment.isObject())
        {
            QJsonObject object = doucment.object();
            if (object.contains("Shoppings")){
                QJsonValue value = object.value("Shoppings");
                if (value.isArray())
                {
                    QJsonArray array = value.toArray();
                    int size = array.size();
                    for (int i = 0; i < size; i++)
                    {
                        if(array[i].isObject()){
                            QJsonObject jsonObject = array[i].toObject();
                            Shopping * shopping = new Shopping;
                            if(jsonObject.contains("ShoppingId")){
                                QJsonValue object = jsonObject.value("ShoppingId");
                                shopping->setShoppingId(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("ClientId")){
                                QJsonValue object = jsonObject.value("ClientId");
                                shopping->setClientId(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("ProductId")){
                                QJsonValue object = jsonObject.value("ProductId");
                                shopping->setProductId(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("ShoppingNum")){
                                QJsonValue object = jsonObject.value("ShoppingNum");
                                shopping->setShoppingNum(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("ShoppingPrice")){
                                QJsonValue object = jsonObject.value("ShoppingPrice");
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

QList<Order *> ObjectToJson::parseOrders(QByteArray byteArray)
{
    QJsonParseError jsonError;
    QList<Order *> orderList;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        if (doucment.isObject())
        {
            QJsonObject object = doucment.object();
            if (object.contains("Orders")){
                QJsonValue value = object.value("Orders");
                if (value.isArray())
                {
                    QJsonArray array = value.toArray();
                    int size = array.size();
                    for (int i = 0; i < size; i++)
                    {
                        if(array[i].isObject()){
                            QJsonObject jsonObject = array[i].toObject();
                            Order * order = new Order;
                            if(jsonObject.contains("OrderId")){
                                QJsonValue object = jsonObject.value("OrderId");
                                order->setOrderId(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("ClientId")){
                                QJsonValue object = jsonObject.value("ClientId");
                                order->setClientId(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("TotalPrice")){
                                QJsonValue object = jsonObject.value("TotalPrice");
                                order->setTotalPrice(object.toVariant().toDouble());
                            }
                            if(jsonObject.contains("OrderStatus")){
                                QJsonValue object = jsonObject.value("OrderStatus");
                                order->setOrderStatus(object.toString());
                            }
                            if(jsonObject.contains("CreateTime")){
                                QJsonValue object = jsonObject.value("CreateTime");
                                order->setCreateTime(object.toString());
                            }
                            if(jsonObject.contains("FinishTime")){
                                QJsonValue object = jsonObject.value("FinishTime");
                                order->setFinishTime(object.toString());
                            }
                            orderList.append(order);
                        }
                    }
                }
            }
        }
    }
    return orderList;
}

QList<OrderList *> ObjectToJson::parseOrderLists(QByteArray byteArray)
{
    QJsonParseError jsonError;
    QList<OrderList *> orderLists;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
    {
        if (doucment.isObject())
        {
            QJsonObject object = doucment.object();
            if (object.contains("OrderLists")){
                QJsonValue value = object.value("OrderLists");
                if (value.isArray())
                {
                    QJsonArray array = value.toArray();
                    int size = array.size();
                    for (int i = 0; i < size; i++)
                    {
                        if(array[i].isObject()){
                            QJsonObject jsonObject = array[i].toObject();
                            OrderList * orderList = new OrderList;
                            if(jsonObject.contains("OrderListId")){
                                QJsonValue object = jsonObject.value("OrderListId");
                                orderList->setOrderListId(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("OrderId")){
                                QJsonValue object = jsonObject.value("OrderId");
                                orderList->setOrderId(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("ProductId")){
                                QJsonValue object = jsonObject.value("ProductId");
                                orderList->setProductId(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("ProductNum")){
                                QJsonValue object = jsonObject.value("ProductNum");
                                orderList->setProductNum(object.toVariant().toInt());
                            }
                            if(jsonObject.contains("ProductPrice")){
                                QJsonValue object = jsonObject.value("ProductPrice");
                                orderList->setProductPrice(object.toVariant().toDouble());
                            }
                            orderLists.append(orderList);
                        }
                    }
                }
            }
        }
    }
    return orderLists;
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
    byteArray.append("\r\n");   //分隔符
    return byteArray;
}


