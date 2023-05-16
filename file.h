
#ifndef FILE_H
#define FILE_H

#include "DataReceiver.h"
#include "datahandeler.h"
#include <QObject>
#include <thread>
#include <fstream>
#include <functional>

class File : public QObject
{
    Q_OBJECT
    QString m_namefile;
    std::thread m_thread;
    DataReceiver* m_data;
    DataHandeler* m_datapars;
    int m_counter;
    std::ofstream m_outputfile;

public:
    File(DataReceiver *data);
    ~File();
    void writeonfile();
};

#endif // FILE_H
