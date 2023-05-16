
#include "ViewModel.h"

ViewModel::ViewModel(DataReceiver* reciver , DataHandeler *data)
    :m_dataReciever(reciver)
    ,m_datahandler(data)
{
    QObject::connect(m_dataReciever,&DataReceiver::currentStatusChanged , this ,&ViewModel::currentstautsChanged);
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


