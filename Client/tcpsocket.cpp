#include "tcpsocket.h"

TcpSocket::TcpSocket()
{
//    tcpSocket = new QTcpSocket(this);
//    QScopedPointer<QTcpSocket> socket(tcpSocket);
//    connectToServer();
//    readySendToServer();

}

//void TcpSocket::connectToServer()
//{
//    QString server_IP = "127.0.0.1";
//    int port = 23333;
//    socket->connectToHost(server_IP, port);
//    connect(socket.data(), &QTcpSocket::readyRead, this, SLOT(on_readyRead()));
//    connect(socket.data(), &QTcpSocket::stateChanged, this, SLOT(on_stateChanged(QAbstractSocket::SocketState socketState)));
//    connect(socket.data(), &QTcpSocket::connected, [=](){
//        qDebug() << "[socket] new Connected: ";
//        qDebug() << "Addr:" << socket->peerAddress();
//        qDebug() << "Port:" << socket->peerPort();
//    });
//    connect(socket.data(), &QTcpSocket::disconnected, [=](){
//        qDebug() << "[socket] disconnected";
//        socket->deleteLater();
//    });
//    connect(socket.data(), QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), [=](){
//        qDebug() << "[socket] error:" << socket->errorString();
//    });
//}

//void TcpSocket::readySendToServer()
//{
//    QObject::connect(logIn, &LogIn::sendToLogIn, [=](QByteArray array){
//        socket->write(array);
//    });
//}

//void TcpSocket::on_stateChanged(QAbstractSocket::SocketState socketState)
//{
//    qDebug() << "[socket] state changed: " << socketState;
//    if (socketState == QAbstractSocket::UnconnectedState)
//    {

//    }
//}

//void TcpSocket::on_readyRead()
//{
//    qDebug() << "[socket] receive message: ";
//    while(socket->bytesAvailable() > 0)
//    {
//        QByteArray datagram;
//        datagram = socket->readAll();
//        dealMessage(datagram);
//    }
//}


//void TcpSocket::dealMessage(QByteArray message)
//{
//    QString signal = ObjectToJson::parseSignal(message);
//    qDebug() << "signal: " << signal;
//    if (signal == QString::number(LOGIN))
//    {
//        // 登录成功
//        QList<Client*> clientList = ObjectToJson::parseClient(message);
//        Client* client = clientList[0];
//        emit logInSuccess(client);
//    }
//    else if (signal == QString::number(LOGINF))
//    {
//        emit logInFail();
//    }
//}
