
#include "datahandeler.h"

DataHandeler::DataHandeler(DataReceiver *data)
    :m_dataReciever(data)
{
    connect(m_dataReciever,&DataReceiver::dataReceivedChanged,this,&DataHandeler::parsing);
}


QVector<double> DataHandeler::mypoint() const
{
    return m_mypoint;
}

void DataHandeler::parsing()
{
    QString data = m_dataReciever->dataReceived();
    int counterdelimiter=0;
    while (m_startindex < data.size())
    {
        if(data.startsWith("@"))
        {
            int startnameindex=1;
            int endnameIndex = data.indexOf('@', startnameindex);
            QString namefamily = data.mid(startnameindex, endnameIndex - startnameindex);
            setNamfam(namefamily.split(','));
            data.remove(0,namefamily.size());
        }


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
    emit isparsed();
}


QStringList DataHandeler::namfam() const
{
    return m_namfam;
}

void DataHandeler::setNamfam(const QStringList &newNamfam)
{
    if (m_namfam == newNamfam)
        return;
    m_namfam = newNamfam;
    emit namfamChanged();
}
