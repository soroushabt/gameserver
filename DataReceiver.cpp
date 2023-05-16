
#include "DataReceiver.h"

DataReceiver::DataReceiver(QTcpServer *server)
    : m_server(server)
{
    setCurrentStatus("yellow");
    QObject::connect(server, &QTcpServer::newConnection, this, &DataReceiver::handleNewConnection);
}

void DataReceiver::DataReceivedHandler()
{
//    std::cerr << "data is ready" << std::endl ;

    // Initialize startindex outside of the loop
    int startindex = 0;

    while (m_socket->bytesAvailable() > 0)
    {
        m_buffer.append(m_socket->readAll());

        if (!m_buffer.isEmpty())
        {
            startindex=m_dataReceived.size();
        }
        setDataReceived(QString::fromLatin1(m_buffer.data() + startindex, m_buffer.size() - startindex));

//        qDebug() << "buffer" << m_buffer;
    }

//    qDebug() << "data" << m_dataReceived; /*<< "sizedata: " << m_dataReceived.size();*/
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

QByteArray DataReceiver::buffer() const
{
    return m_buffer;
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

QString DataReceiver::dataReceived() const
{
    return m_dataReceived;
}

void DataReceiver::setDataReceived(const QString &newDataReceived)
{
    if (m_dataReceived == newDataReceived)
        return;
    m_dataReceived.append(newDataReceived);
    emit dataReceivedChanged();
}
