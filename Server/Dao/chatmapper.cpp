#include "chatmapper.h"

#include <QSqlQuery>
#include <QTime>
#include <QReadWriteLock>
#include "../objects/chat.h"

ChatMapper::ChatMapper(QSqlDatabase &database)
    : Mapper(database)
{
}

Chat *ChatMapper::getChat(QSqlQuery &query) const
{
    Chat* chat = new Chat();
    chat->setChatId(query.value(0).toInt());
    chat->setClientId(query.value(1).toInt());
    chat->setChatText(query.value(2).toString());
    chat->setChatIsserver(query.value(3).toInt());
    chat->setChatTime(query.value(4).toDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    return chat;
}

QList<Chat *> ChatMapper::select(const int cid) const
{
    QReadLocker locker(&dbLock);

    qDebug() << "[database] chat select... " << cid;
    QSqlQuery query(db);
    query.prepare("SELECT * FROM chat WHERE client_id = :id");
    query.bindValue(":id", cid);
    query.exec();

    QList<Chat *> ret;
    while(query.next()) {
        ret.push_back(getChat(query));
    }
    query.clear();
    return ret;
}

void ChatMapper::insert(const Chat *chat) const
{
    QWriteLocker locker(&dbLock);

    qDebug() << "[database] chat insert chat ... " << chat->getClientId();
    QSqlQuery query(db);
    query.prepare("INSERT chat ( `client_id`, `chat_text`, `chat_isserver`, `chat_time` ) \
                  VALUES ( :id, :text, :isserver, :time)");
    query.bindValue(":id", chat->getClientId());
    query.bindValue(":text", chat->getChatText());
    query.bindValue(":isserver", chat->getChatIsserver());
    query.bindValue(":time", chat->getChatTime());
    query.exec();
    query.clear();
}

void ChatMapper::insert(const QList<Chat *> chatList) const
{
    qDebug() << "[database] chat insert chatList ...";
    for (auto chat : chatList)
    {
        insert(chat);
    }
}
