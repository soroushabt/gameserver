
#ifndef VIEWMODEL_H
#define VIEWMODEL_H


#include <QObject>
#include <QVector>
#include "DataReceiver.h"


class ViewModel : public QObject
{
    Q_OBJECT
    DataReceiver *m_dataReciever;
    Q_PROPERTY(QString currentstauts READ currentstauts NOTIFY currentstautsChanged)
    Q_PROPERTY(QVector<double> mypoint READ mypoint WRITE setMypoint NOTIFY mypointChanged)

public:
    ViewModel(DataReceiver *dataReciever);
    Q_INVOKABLE void listen();
    QString currentstauts() const;
    QVector<double> mypoint() ;
    void setMypoint(const QVector<double> &newMypoint);
signals:
    void currentstautsChanged();
    void mypointChanged();
private:
    QString m_currentstauts;
    QVector<double> m_mypoint;
    int m_startindex=0;
    int lasty=0;
    int sumy=0;
};

#endif // VIEWMODEL_H
