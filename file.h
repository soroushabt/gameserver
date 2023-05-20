
#ifndef FILE_H
#define FILE_H

#include "DataReceiver.h"
#include "datahandeler.h"
#include <QObject>
#include <fstream>
#include <functional>


class File : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool clearfil READ clearfil WRITE setClearfil NOTIFY clearfilChanged)
    Q_PROPERTY(QString datafile READ datafile WRITE setDatafile NOTIFY datafileChanged)
    int m_userid;
    DataReceiver* m_data;
    DataHandeler* m_datapars;
    int m_counter;
    std::ofstream m_outputfile;
    std::ifstream m_inputfile;

public:
    File(DataReceiver *data);
    ~File();
    void writeonfile();
    bool clearfil() const;
    Q_INVOKABLE void readonfile(QString url);
    void setClearfil(bool newClearfil);

    QString datafile() const;
    void setDatafile(const QString &newDatafile);

signals:
    void clearfilChanged();

    void datafileChanged();

private:
    bool m_clearfil;
    int m_sizefile;
    QString m_datafile;
};

#endif // FILE_H
