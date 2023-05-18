
#include "file.h"
#include <functional>

File::File(DataReceiver* data)
    :m_data(data)
    ,m_counter(0)
    ,m_userid(0)
    ,m_clearfil(false)

{
    //    m_outputfile = "test";
    connect(m_data , &DataReceiver::dataReceivedChanged , this , &File::writeonfile);
}

File::~File()
{
}

void File::writeonfile()
{
    if(m_outputfile.is_open())
    {
//        qDebug() << "buffer" << m_data->buffer();
        if(!m_data->buffer().isEmpty())
        {
            m_outputfile << m_data->dataReceived().toStdString().substr(m_outputfile.tellp());
            m_outputfile.flush();
            if(m_data->dataReceived().toStdString().back()=='*')
            {
                std::cerr << "test";
                m_outputfile.close();
                m_userid++;
                setClearfil(true);
            }

        }
    }
    else
    {
        m_outputfile.open("user"+std::to_string(m_userid)+".txt");
    }

}



bool File::clearfil() const
{
    return m_clearfil;
}

void File::setClearfil(bool newClearfil)
{
    if (m_clearfil == newClearfil)
        return;
    m_clearfil = newClearfil;
    emit clearfilChanged();
}
