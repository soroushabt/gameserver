
#include "DataReceiver.h"

DataReceiver::DataReceiver(QTcpServer *server)
    : m_server(server)
{
    setCurrentStatus("yellow");
    qRegisterMetaType<DataReceiver*>("DataReceiver*");
    QObject::connect(server, &QTcpServer::newConnection, this, &DataReceiver::handleNewConnection);
}

void DataReceiver::DataReceivedHandler()
{
//    setCurrentStatus("Data Received");
//    while (m_socket->bytesAvailable() > 0)
//    {
//        auto readsize = m_socket->read(m_buffer, 1000);
//        QString str;
//        for (int i = 0; i < readsize; ++i) {
//            str.append(m_buffer[i]);
//        }
//        setReceivedData(str);
//    }
}

void DataReceiver::handleNewConnection()
{
    if(m_server->hasPendingConnections())
    {
        m_socket = m_server->nextPendingConnection();
        m_server->close();
        setCurrentStatus("green");
        connect(m_socket, &QTcpSocket::readyRead, this, &DataReceiver::DataReceivedHandler);
        connect(m_socket, &QTcpSocket::disconnected, this, &DataReceiver::listen);
    }
}

void DataReceiver::listen()
{
    while(true)
    {
    if(m_server->isListening())
        break;
    m_server->listen(QHostAddress::Any, 2000);
    }
}


QString DataReceiver::currentStatus() const
{
    return m_currentStatus;
}

void DataReceiver::setCurrentStatus(const QString &newCurrentStatus)
{
    if (m_currentStatus == newCurrentStatus)
        return;
    m_currentStatus = newCurrentStatus;
    emit currentStatusChanged();
}
