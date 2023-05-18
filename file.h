
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
    int m_userid;
    DataReceiver* m_data;
    DataHandeler* m_datapars;
    int m_counter;
    std::ofstream m_outputfile;

public:
    File(DataReceiver *data);
    ~File();
    void writeonfile();
    bool clearfil() const;
    void setClearfil(bool newClearfil);

signals:
    void clearfilChanged();

private:
    bool m_clearfil;
};

#endif // FILE_H
