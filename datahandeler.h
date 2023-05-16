
#ifndef DATAHANDELER_H
#define DATAHANDELER_H

#include <QObject>
#include <QVector>
#include "DataReceiver.h"


class DataHandeler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList namfam READ namfam WRITE setNamfam NOTIFY namfamChanged)
    DataReceiver *m_dataReciever;
    QVector<double> m_mypoint;
    int m_startindex=0;
    int lasty=0;
    int sumy=0;
signals:
    void isparsed();
    void namfamChanged();

public slots:
    void parsing();
public:
    DataHandeler(DataReceiver* data);
    QVector<double> mypoint() const;

    QStringList names() const;
    QStringList namfam() const;
    void setNamfam(const QStringList &newNamfam);
private:
    QStringList m_namfam;
};

#endif // DATAHANDELER_H
