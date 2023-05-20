
#include "datahandeler.h"
#include "file.h"

DataHandeler::DataHandeler(DataReceiver *data , File* file)
    :m_dataReciever(data)
    ,m_file(file)
    ,m_namfam({"",""})
    ,m_clearpars(false)
//    ,m_mypoint({15,50})
{
    m_mypoint.fill(0);
    connect(m_dataReciever,&DataReceiver::dataReceivedChanged,this,&DataHandeler::parsing);
    connect(m_file,&File::clearfilChanged,this,&DataHandeler::clearing);
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
            data.remove(0,namefamily.size()+2);
        }


        // Find the index of the next '$' character
        int endIndex = data.indexOf('$', m_startindex);
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

        if(data.toStdString().back()=='*')
        {
            m_clearpars = true;
            clearing();
        }
        if (endIndex == -1)
        {
            // No more data points, exit the loop
            break;
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

void DataHandeler::clearing()
{
    if(m_clearpars==true && m_file->clearfil()==true)
    {
        m_dataReciever->cleardata();
        m_startindex = 0;
        setNamfam({"",""});
        m_dataReciever->setBuffer({});
        m_mypoint.clear();
        emit cleardataChanged();
    }
}



