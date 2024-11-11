#ifndef OBJECT_H
#define OBJECT_H

// 数据类

#include <QString>
#include <QDateTime>

class Client
{
private:
    QString clientName;
    int clientId;
    QString clientPhone;
    QString clientEmail;
    QString clientPwd;
    int clientBought;
    QString clientAddr;
    QString clientGender;

public:
    Client();
    Client(
            QString clientName,
            int clientId,
            QString clientPhone,
            QString clientEmail,
            QString clientPwd,
            int clientBought,
            QString clientAddr,
            QString clientGender
            );
    void setClientId(int clientId);
    void setClientName(QString clientName);
    void setClientPwd(QString clientPwd);
    void setClientAddr(QString clientAddr);
    void setClientPhone(QString clientPhone);
    void setClientEmail(QString clientEmail);
    void setClientBought(int clientBought);
    void setClientGender(QString clientGender);

    int getClientBought() const;
    QString getClientPwd() const;
    QString getClientEmail() const;
    QString getClientPhone() const;
    int getClientId() const;
    QString getClientName() const;
    QString getClientGender() const;
    QString getClientAddr() const;
};

#endif // OBJECT_H
