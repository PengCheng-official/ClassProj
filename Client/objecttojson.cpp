#include "objecttojson.h"

ObjectToJson::ObjectToJson()
{

}

QJsonObject ObjectToJson::addClientList(QJsonObject &object, QList<Client *> clientList)
{
    QJsonObject* objectList;
    QJsonArray array;
    int size = clientList.size();
    objectList = new QJsonObject[size];
    for (int i=0;i<size;i++) {
        objectList[i].insert("clientName", clientList[i]->getClientName());
        objectList[i].insert("clientId", clientList[i]->getClientId());
        objectList[i].insert("clientPhone", clientList[i]->getClientPhone());
        objectList[i].insert("clientEmail", clientList[i]->getClientEmail());
        objectList[i].insert("clientAddr", clientList[i]->getClientAddr());
        objectList[i].insert("clientPwd", clientList[i]->getClientPwd());
        objectList[i].insert("clientBought", clientList[i]->getClientBought());
        objectList[i].insert("clientGender", clientList[i]->getClientGender());
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

//QJsonObject ObjectToJson::integrateProductList(QJsonObject &object, QList<Product *> ProductList)
//{
////    QJsonObject object;
//    QJsonObject* objectList;
//    QJsonArray array;
//    int size = ProductList.size();
//    objectList = new QJsonObject[size];
//    for (int i=0;i<size;i++) {
//          objectList[i].insert("productId",ProductList[i]->getProductId());
//          objectList[i].insert("productName",ProductList[i]->getProductName());
//          objectList[i].insert("productPrice",ProductList[i]->getProductPrice());
//          objectList[i].insert("productNum",ProductList[i]->getProductNum());
//          objectList[i].insert("productBuyNum",ProductList[i]->getProductBuyNum());
//          objectList[i].insert("productImage",ProductList[i]->getProductImage());
//          objectList[i].insert("productDiscount",ProductList[i]->getProductDiscount());
//          array.append(objectList[i]);
//    }
////    object.insert("signal",signal);
//    object.insert("ProductList",QJsonValue(array));
//    return object;
//}

//QJsonObject ObjectToJson::integrateProductTypeList(QJsonObject &object, QList<ProductType *> ProductTypeList)
//{
////    QJsonObject object;
//    QJsonObject* objectList;
//    QJsonArray array;
//    int size = ProductTypeList.size();
//    objectList = new QJsonObject[size];
//        for (int i=0;i<size;i++) {
//            objectList[i].insert("typeName",ProductTypeList[i]->getTypeName());
//            objectList[i].insert("typeId",ProductTypeList[i]->getTypeId());
//            objectList[i].insert("typeProduct",ProductTypeList[i]->getTypeProduct());
//            objectList[i].insert("typeProductId",ProductTypeList[i]->getTypeProductId());
//            array.append(objectList[i]);
//        }
////    object.insert("signal",signal);
//    object.insert("ProductTypeList",QJsonValue(array));
//    return object;
//}

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

QJsonObject ObjectToJson::addString(QJsonObject &object, QString string)
{
    object.insert("string", string);
    return object;
}

QJsonObject ObjectToJson::addNum(QJsonObject &object, int number)
{
    object.insert("number",number);
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
                            QJsonObject clientObject = array[i].toObject();
                            Client * client = new Client;
                            if(clientObject.contains("clientName")){
                                QJsonValue object = clientObject.value("clientName");
                                client->setClientName(object.toString());
                            }
                            if(clientObject.contains("clientId")){
                                QJsonValue object = clientObject.value("clientId");
                                client->setClientId(object.toVariant().toInt());
                            }
                            if(clientObject.contains("clientPhone")){
                                QJsonValue object = clientObject.value("clientPhone");
                                client->setClientPhone(object.toString());
                            }
                            if(clientObject.contains("clientEmail")){
                                QJsonValue object = clientObject.value("clientEmail");
                                client->setClientEmail(object.toString());
                            }
                            if(clientObject.contains("clientAddr")){
                                QJsonValue object = clientObject.value("clientAddr");
                                client->setClientAddr(object.toString());
                            }
                            if(clientObject.contains("clientPwd")){
                                QJsonValue object = clientObject.value("clientPwd");
                                client->setClientPwd(object.toString());
                            }
                            if(clientObject.contains("clientBought")){
                                QJsonValue object = clientObject.value("clientBought");
                                client->setClientBought(object.toVariant().toInt());
                            }
                            if(clientObject.contains("clientGender")){
                                QJsonValue object = clientObject.value("clientGender");
                                client->setClientGender(object.toString());
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
                            QJsonObject clientObject = array[i].toObject();
                            Chat * chat = new Chat;
                            if(clientObject.contains("clientId")){
                                QJsonValue object = clientObject.value("clientId");
                                chat->setClientId(object.toVariant().toInt());
                            }
                            if(clientObject.contains("chatText")){
                                QJsonValue object = clientObject.value("chatText");
                                chat->setChatText(object.toString());
                            }
                            if(clientObject.contains("chatIsserver")){
                                QJsonValue object = clientObject.value("chatIsserver");
                                chat->setChatIsserver(object.toVariant().toInt());
                            }
                            if(clientObject.contains("chatTime")){
                                QJsonValue object = clientObject.value("chatTime");
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

//QList<Product *> ObjectToJson::parseProduct(QByteArray byteArray)
//{
//    QJsonParseError jsonError;
//    QList<Product*> productList;
//    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
//    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)){
//           if (doucment.isObject()){
//                QJsonObject object = doucment.object();
//                if(object.contains("ProductList")){
//                    QJsonValue value = object.value("ProductList");
//                    if(value.isArray()){
//                        QJsonArray array = value.toArray();
//                        int size = array.size();
//                        for(int i=0;i<size;i++){
//                            if(array[i].isObject()){
//                                QJsonObject productObject = array[i].toObject();
//                                Product * product = new Product;
//                                if(productObject.contains("productName")){
//                                    QJsonValue object = productObject.value("productName");
//                                    product->setProductName(object.toString());
//                                }
//                                if(productObject.contains("productId")){
//                                    QJsonValue object = productObject.value("productId");
//                                    product->setProductId(object.toVariant().toInt());
//                                }
//                                if(productObject.contains("productPrice")){
//                                    QJsonValue object = productObject.value("productPrice");
//                                    product->setProductPrice(object.toVariant().toInt());
//                                }
//                                if(productObject.contains("productNum")){
//                                    QJsonValue object = productObject.value("productNum");
//                                    product->setProductNum(object.toVariant().toInt());
//                                }
//                                if(productObject.contains("productBuyNum")){
//                                    QJsonValue object = productObject.value("productBuyNum");
//                                    product->setProductBuyNum(object.toVariant().toInt());
//                                }
//                                if(productObject.contains("productDiscount")){
//                                    QJsonValue object = productObject.value("productDiscount");
//                                    product->setProductDiscount(object.toVariant().toFloat());
//                                }
//                                if(productObject.contains("productImage")){
//                                    QJsonValue object = productObject.value("productImage");
//                                    product->setProductImage(object.toString());
//                                }
//                                productList.append(product);
//                            }
//                        }
//                    }
//                }
//           }
//    }
//    return productList;
//}

//QList<ProductType *> ObjectToJson::parseProductType(QByteArray byteArray)
//{
//    QJsonParseError jsonError;
//    QList<ProductType*> productTypeList;
//    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
//    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)){
//           if (doucment.isObject()){
//                QJsonObject object = doucment.object();
//                if(object.contains("ProductTypeList")){
//                    QJsonValue value = object.value("ProductTypeList");
//                    if(value.isArray()){
//                        QJsonArray array = value.toArray();
//                        int size = array.size();
//                        for(int i=0;i<size;i++){
//                            if(array[i].isObject()){
//                                QJsonObject productTypeObject = array[i].toObject();
//                                ProductType * productType = new ProductType;
//                                if(productTypeObject.contains("typeName")){
//                                    QJsonValue object = productTypeObject.value("typeName");
//                                    productType->setTypeName(object.toString());
//                                }
//                                if(productTypeObject.contains("typeId")){
//                                    QJsonValue object = productTypeObject.value("typeId");
//                                    productType->setTypeId(object.toVariant().toInt());
//                                }
//                                if(productTypeObject.contains("typeProduct")){
//                                    QJsonValue object = productTypeObject.value("typeProduct");
//                                    productType->setTypeProduct(object.toString());
//                                }
//                                if(productTypeObject.contains("typeProductId")){
//                                    QJsonValue object = productTypeObject.value("typeProductId");
//                                    productType->setTypeProductId(object.toVariant().toInt());
//                                }

//                                productTypeList.append(productType);
//                            }
//                        }
//                    }
//                }
//           }
//    }return productTypeList;
//}


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



int ObjectToJson::parseNum(QByteArray byteArray)
{
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)){
        if (doucment.isObject()){
            QJsonObject object = doucment.object();
            if(object.contains("number")){
                QJsonValue value = object.value("number");
                return value.toVariant().toInt();
            }
        }
    }
    return -1;
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

QString ObjectToJson::parseString(QByteArray byteArray)
{
    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)){
        if (doucment.isObject()){
            QJsonObject object = doucment.object();
            if(object.contains("string")){
                QJsonValue value = object.value("string");
                return value.toVariant().toString();
            }
        }
    }
    return "";
}

QByteArray ObjectToJson::changeJson(QJsonObject &object)
{
    QJsonDocument document;
    document.setObject(object);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    return byteArray;
}


