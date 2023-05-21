
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

public:
    ViewModel(DataReceiver *reciver, DataHandeler *data ,File* file);
    Q_INVOKABLE void listen();
    Q_INVOKABLE void readfile(QString url);
    QString currentstauts() const;
    QVector<double> mypoint() const;
    void setMypoint(const QVector<double> &newMypoint);
    QStringList namefamliy() const;
    QString fileurl() const;
    void setFileurl(const QString &newFileurl);

signals:
    void currentstautsChanged();
    void mypointChanged();
    void namefamliyChanged();
    void clearing();
public slots:
    void clearingslot();
private:
    QString m_currentstauts;
    DataReceiver *m_dataReciever;
    DataHandeler *m_datahandler;
    File *m_file;
    QVector<double> m_mypoint;
    QStringList m_namefamliy;
};

#endif // VIEWMODEL_H
