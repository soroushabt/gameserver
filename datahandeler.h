
#ifndef DATAHANDELER_H
#define DATAHANDELER_H

#include <QObject>
#include <QVector>
#include "DataReceiver.h"

class File;

class DataHandeler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList namfam READ namfam WRITE setNamfam NOTIFY namfamChanged)

signals:
    void isparsed();
    void namfamChanged();

    void cleardataChanged();

public slots:
    void parsing();
    void clearing();
    void readfile();
public:
    DataHandeler(DataReceiver* data, File* file);
    QVector<double> mypoint() const;
    QStringList names() const;
    QStringList namfam() const;
    void setNamfam(const QStringList &newNamfam);


    void setData(const QString &newData);

private:
    QStringList m_namfam;
    QString data;
    DataReceiver *m_dataReciever;
    File *m_file;
    QVector<double> m_mypoint;
    int m_startindex=0;
    long lasty=0;
    long sumy=0;
    bool m_clearpars;
};

#endif // DATAHANDELER_H
