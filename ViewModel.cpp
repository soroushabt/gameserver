
#include "ViewModel.h"

ViewModel::ViewModel(DataReceiver* reciver , DataHandeler *data ,File* file)
    :m_dataReciever(reciver)
    ,m_datahandler(data)
    ,m_file(file)
    ,m_namefamliy({""})
    ,m_clearing(false)
{
    QObject::connect(m_dataReciever,&DataReceiver::currentStatusChanged , this ,&ViewModel::currentstautsChanged);
    QObject::connect(m_datahandler,&DataHandeler::cleardataChanged,this,&ViewModel::clearingChanged);
    QObject::connect(m_datahandler,&DataHandeler::isparsed , this ,&ViewModel::mypointChanged);
    QObject::connect(m_datahandler,&DataHandeler::namfamChanged,this,&ViewModel::namefamliyChanged);

}

void ViewModel::listen()
{
    QMetaObject::invokeMethod(m_dataReciever, "listen");
}

QString ViewModel::currentstauts() const
{
    return m_dataReciever->currentStatus();
}



QVector<double> ViewModel::mypoint() const
{
    return m_datahandler->mypoint();
}

void ViewModel::setMypoint(const QVector<double> &newMypoint)
{
    if (m_mypoint == newMypoint)
        return;
    m_mypoint = newMypoint;
    emit mypointChanged();
}



QStringList ViewModel::namefamliy() const
{
    return m_datahandler->namfam();
}




bool ViewModel::clearing() const
{
    return m_datahandler->cleardata();
}

void ViewModel::setClearing(bool newClearing)
{
    if (m_clearing == newClearing)
        return;
    m_clearing = newClearing;
    emit clearingChanged();
}
