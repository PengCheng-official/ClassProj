#ifndef CLIENT_H
#define CLIENT_H


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
    QString clientSalt;

public:
    Client();
    Client(
            QString clientName,
            int clientId,
            QString clientPhone,
            QString clientEmail,
            QString clientPwd,
            QString clientSalt,
            int clientBought,
            QString clientAddr,
            QString clientGender
            );
    void setClientId(int clientId);
    void setClientName(QString clientName);
    void setClientPwd(QString clientPwd);
    void setClientSalt(QString clientSalt);
    void setClientAddr(QString clientAddr);
    void setClientPhone(QString clientPhone);
    void setClientEmail(QString clientEmail);
    void setClientBought(int clientBought);
    void setClientGender(QString clientGender);

    int getClientBought() const;
    QString getClientPwd() const;
    QString getClientSalt() const;
    QString getClientEmail() const;
    QString getClientPhone() const;
    int getClientId() const;
    QString getClientName() const;
    QString getClientGender() const;
    QString getClientAddr() const;
};

#endif // CLIENT_H
