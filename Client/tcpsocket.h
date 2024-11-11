#ifndef TCPSOCKET_H
#define TCPSOCKET_H

// 统一处理 socket
#include <QObject>
#include <QTcpSocket>
#include <QCoreApplication>
#include <QDebug>
#include <QHostAddress>
#include "statement.h"
#include "login.h"
#include "signal.h"
#include "chatroom.h"

class LogIn;
class SignIn;
class ChatRoom;

class TcpSocket : public QTcpSocket
{
public:
    TcpSocket();

private:
};

#endif // TCPSOCKET_H
