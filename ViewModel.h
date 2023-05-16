
#ifndef VIEWMODEL_H
#define VIEWMODEL_H


#include <QObject>
#include <QVector>
#include "DataReceiver.h"
#include "datahandeler.h"


class ViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentstauts READ currentstauts NOTIFY currentstautsChanged)
    Q_PROPERTY(QVector<double> mypoint READ mypoint WRITE setMypoint NOTIFY mypointChanged)
    Q_PROPERTY(QStringList namefamliy READ namefamliy NOTIFY namefamliyChanged)

public:
    ViewModel(DataReceiver *reciver, DataHandeler *data);
    Q_INVOKABLE void listen();
    QString currentstauts() const;
    QVector<double> mypoint() const;
    void setMypoint(const QVector<double> &newMypoint);
    QStringList namefamliy() const;


signals:
    void currentstautsChanged();
    void mypointChanged();
    void namefamliyChanged();

private:
    QString m_currentstauts;
    DataReceiver *m_dataReciever;
    DataHandeler *m_datahandler;
    QVector<double> m_mypoint;
    QStringList m_namefamliy;
};

#endif // VIEWMODEL_H
