
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
    Q_PROPERTY(int clearing READ clearing WRITE setClearing NOTIFY clearingChanged)

public:
    ViewModel(DataReceiver *reciver, DataHandeler *data ,File* file);
    Q_INVOKABLE void listen();
    Q_INVOKABLE void readfile(QString url);
    QString currentstauts() const;
    QVector<double> mypoint() const;
    void setMypoint(const QVector<double> &newMypoint);
    QStringList namefamliy() const;


    int clearing() const;
    void setClearing(int newClearing);

    QString fileurl() const;
    void setFileurl(const QString &newFileurl);

signals:
    void currentstautsChanged();
    void mypointChanged();
    void namefamliyChanged();
    int clearingChanged();

public slots:
    void clear();


private:
    QString m_currentstauts;
    DataReceiver *m_dataReciever;
    DataHandeler *m_datahandler;
    File *m_file;
    QVector<double> m_mypoint;
    QStringList m_namefamliy;
    int m_clearing;
    int m_numuser;
};

#endif // VIEWMODEL_H
