
#ifndef DATARECEIVER_H
#define DATARECEIVER_H
#include <iostream>
#include <QTcpServer>
#include <QTcpSocket>
#include<QObject>
#include<QChar>


class DataReceiver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentStatus READ currentStatus WRITE setCurrentStatus NOTIFY currentStatusChanged)
    Q_PROPERTY(QString dataReceived READ dataReceived WRITE setDataReceived NOTIFY dataReceivedChanged)
public:
    DataReceiver(QTcpServer *server);
    QString currentStatus() const;
    void setCurrentStatus(const QString &newCurrentStatus);


    QString dataReceived() const;
    void setDataReceived(const QString &newDataReceived);

    QByteArray buffer() const;

public slots:
    void DataReceivedHandler();
    void handleNewConnection();
    void listen();

signals:
    void currentStatusChanged();
    void dataReceivedChanged();

private:
    QString m_currentStatus;
    QByteArray m_buffer;
    QTcpServer *m_server;
    QTcpSocket *m_socket;
    QString m_dataReceived;
};

#endif // DATARECEIVER_H


