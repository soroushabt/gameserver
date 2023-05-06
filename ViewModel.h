
#ifndef VIEWMODEL_H
#define VIEWMODEL_H


#include <QObject>
#include "DataReceiver.h"


class ViewModel : public QObject
{
    Q_OBJECT
    DataReceiver *m_dataReciever;
    Q_PROPERTY(QString currentStatus READ currentStatus NOTIFY currentStatusChanged)
    Q_PROPERTY(QString receivedData READ receivedData NOTIFY receivedDataChanged)
public:
    ViewModel(DataReceiver *dataReciever);
    Q_INVOKABLE void listen();

    QString currentStatus() const;
    QString receivedData() const;

signals:

    void currentStatusChanged();
    void receivedDataChanged();

private:
    QString m_currentStatus;
    QString m_receivedData;
};

#endif // VIEWMODEL_H
