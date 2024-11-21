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
    void setClientName(const QString &clientName);
    void setClientPwd(const QString &clientPwd);
    void setClientSalt(const QString &clientSalt);
    void setClientAddr(const QString &clientAddr);
    void setClientPhone(const QString &clientPhone);
    void setClientEmail(const QString &clientEmail);
    void setClientBought(int clientBought);
    void setClientGender(const QString &clientGender);

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
