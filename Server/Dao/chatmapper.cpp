#include "chatmapper.h"

ChatMapper::ChatMapper(QSqlDatabase &database)
    : Mapper(database)
{
}

Chat *ChatMapper::getChat(QSqlQuery &query)
{
    Chat* chat = new Chat();
    chat->setClientId(query.value(0).toInt());
    chat->setChatText(query.value(1).toString());
    chat->setChatIsserver(query.value(2).toInt());
    chat->setChatTime(query.value(3).toString());
    return chat;
}

QList<Chat *> ChatMapper::select(int id)
{
    qDebug() << "[database] chat select...";
    QSqlQuery query(db);
    query.prepare("SELECT * FROM chat WHERE chat_id = :id");
    query.bindValue(":id", id);
    query.exec();

    QList<Chat *> ret;
    while(query.next()) {
        ret.push_back(getChat(query));
    }
    query.finish();
    return ret;
}

void ChatMapper::insert(Chat *chat)
{
    qDebug() << "[database] chat insert ...";
    QSqlQuery query(db);
    query.prepare("INSERT chat ( `client_id`, `chat_text`, `chat_isserver`, `chat_time` ) \
                  VALUES ( :id, :text, :isserver, :time)");
    query.bindValue(":id", chat->getClientId());
    query.bindValue(":text", chat->getChatText());
    query.bindValue(":isserver", chat->getChatIsserver());
    query.bindValue(":time", chat->getChatTime());
    query.exec();
    query.finish();
}
