
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
    Q_PROPERTY(bool cleardata READ cleardata WRITE setCleardata NOTIFY cleardataChanged)

signals:
    void isparsed();
    void namfamChanged();

    void cleardataChanged();

public slots:
    void parsing();
public:
    DataHandeler(DataReceiver* data, File* file);
    QVector<double> mypoint() const;
    QStringList names() const;
    QStringList namfam() const;
    void setNamfam(const QStringList &newNamfam);

    void clearing();
    bool cleardata() const;
    void setCleardata(bool newCleardata);

private:
    QStringList m_namfam;
    DataReceiver *m_dataReciever;
    File *m_file;
    QVector<double> m_mypoint;
    int m_startindex=0;
    int lasty=0;
    int sumy=0;
    bool m_cleardata;
};

#endif // DATAHANDELER_H
