#ifndef CHATMAPPER_H
#define CHATMAPPER_H

#include "mapper.h"

class ChatMapper : public Mapper
{
public:
    ChatMapper(QSqlDatabase &database);

public:
    Chat *getChat(QSqlQuery &query);

    QList<Chat *> select(int id);

    void insert(Chat* chat);

};

#endif // CHATMAPPER_H
