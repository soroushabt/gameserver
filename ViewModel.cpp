
#include "ViewModel.h"

ViewModel::ViewModel(DataReceiver *dataReciever)
    :m_dataReciever(dataReciever)
{

}


QString ViewModel::currentStatus() const
{
    return m_currentStatus;
}

QString ViewModel::receivedData() const
{
    return m_receivedData;
}

void ViewModel::listen()
{
    QMetaObject::invokeMethod(m_dataReciever, "listen");
}
