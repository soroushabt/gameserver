
#include "file.h"
#include <functional>

File::File(DataReceiver* data)
    :m_thread(std::bind(&File::writeonfile,this))
    ,m_data(data)
    ,m_counter(0)
{
    //    m_outputfile = "test";
    connect(m_data , &DataReceiver::dataReceivedChanged , this , &File::writeonfile);
}

File::~File()
{
    m_thread.join();
}

void File::writeonfile()
{
    if(!m_data->buffer().isEmpty())
    {
//        std::this_thread::sleep_for(std::chrono::microseconds(1000));
//        std::cerr << "Iamthere" << std::endl;
//        m_namefile = m_datapars->namfam().join(" ");
        m_outputfile.open(m_namefile.toStdString()+".txt");
        if (m_outputfile.is_open()) {
//            std::cerr << "Iamhere" << std::endl;
            // Convert the QString to a std::string
            std::string data = m_data->dataReceived().toStdString();

            // Write the string to the file
            m_outputfile << data;

            // Close the file
            m_outputfile.close();
        }
    }
}

