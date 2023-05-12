
#include "ViewModel.h"

ViewModel::ViewModel(DataReceiver *dataReciever)
    :m_dataReciever(dataReciever)
{
    QObject::connect(m_dataReciever,&DataReceiver::currentStatusChanged , this ,&ViewModel::currentstautsChanged);
    QObject::connect(m_dataReciever,&DataReceiver::dataReceivedChanged , this ,&ViewModel::mypointChanged);

}


void ViewModel::listen()
{
    QMetaObject::invokeMethod(m_dataReciever, "listen");
}

QString ViewModel::currentstauts() const
{
    return m_dataReciever->currentStatus();
}


QVector<double> ViewModel::mypoint()
{
    QString data = m_dataReciever->dataReceived();
    while (m_startindex < data.size())
    {
        // Find the index of the next '$' character
        int endIndex = data.indexOf('$', m_startindex);
        if (endIndex == -1)
        {
            // No more data points, exit the loop
            break;
        }
        // Extract the substring containing the current data point
        QString pointData = data.mid(m_startindex, endIndex - m_startindex);
        // Split the substring into x and y values
        QStringList values = pointData.split(',');
        if (values.size() == 2)
        {
            // Convert the x and y values to doubles and add them to the QVector
            double x = values[0].toDouble();
            double y = values[1].toDouble() - lasty;
            sumy += y;
            lasty = values[1].toDouble();
            if(m_startindex==0)
                sumy=0;
            m_mypoint.append(x);
            m_mypoint.append(sumy);
        }
        // Move the start index to the next data point
        m_startindex = endIndex + 1;
    }
//    std::cerr << m_mypoint.size() << "--";
    return m_mypoint;
}

void ViewModel::setMypoint(const QVector<double> &newMypoint)
{
    if (m_mypoint == newMypoint)
        return;
    m_mypoint = newMypoint;
    emit mypointChanged();
}

