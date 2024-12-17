#ifndef CHATMAPPER_H
#define CHATMAPPER_H


#include "mapper.h"

class Chat;
class ChatMapper : public Mapper
{
public:
    ChatMapper(QSqlDatabase &database);

public:
    Chat *getChat(QSqlQuery &query) const;
    //DAO层，数据转对象

    QList<Chat *> select(const int cid) const;
    //通过用户cid，查找聊天记录

    void insert(const Chat* chat) const;
    //插入聊天记录

    void insert(const QList<Chat *> chatList) const;
    //插入多条聊天记录
};

#endif // CHATMAPPER_H
