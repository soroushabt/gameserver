
#ifndef VIEWMODEL_H
#define VIEWMODEL_H


#include <QObject>
#include <QVector>
#include "DataReceiver.h"
#include "datahandeler.h"
#include "file.h"


class ViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentstauts READ currentstauts NOTIFY currentstautsChanged)
    Q_PROPERTY(QVector<double> mypoint READ mypoint WRITE setMypoint NOTIFY mypointChanged)
    Q_PROPERTY(QStringList namefamliy READ namefamliy NOTIFY namefamliyChanged)
    Q_PROPERTY(bool clearing READ clearing WRITE setClearing NOTIFY clearingChanged)

public:
    ViewModel(DataReceiver *reciver, DataHandeler *data ,File* file);
    Q_INVOKABLE void listen();
    QString currentstauts() const;
    QVector<double> mypoint() const;
    void setMypoint(const QVector<double> &newMypoint);
    QStringList namefamliy() const;



    bool clearing() const;
    void setClearing(bool newClearing);

signals:
    void currentstautsChanged();
    void mypointChanged();
    void namefamliyChanged();


    void clearingChanged();

private:
    QString m_currentstauts;
    DataReceiver *m_dataReciever;
    DataHandeler *m_datahandler;
    File *m_file;
    QVector<double> m_mypoint;
    QStringList m_namefamliy;
    bool m_clearing;
};

#endif // VIEWMODEL_H
