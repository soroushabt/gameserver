
#ifndef DATARECEIVER_H
#define DATARECEIVER_H
#include <iostream>
#include <QTcpServer>
#include <QTcpSocket>
#include<QObject>


class DataReceiver : public QObject
{
    Q_OBJECT
    QTcpServer *m_server;
    QTcpSocket *m_socket;
    Q_PROPERTY(QString currentStatus READ currentStatus WRITE setCurrentStatus NOTIFY currentStatusChanged)
public:
    DataReceiver(QTcpServer *server);
    QString currentStatus() const;
    void setCurrentStatus(const QString &newCurrentStatus);

public slots:
    void DataReceivedHandler();
    void handleNewConnection();
    void listen();

signals:
    void currentStatusChanged();

private:
    QString m_currentStatus;
};

#endif // DATARECEIVER_H
