
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>
#include <QtQuick/QQuickView>
#include "DataReceiver.h"
#include "ViewModel.h"
#include "file.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
//    const QUrl url(u"qrc:/Gameserver/Main.qml"_qs);
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
//        &app, []() { QCoreApplication::exit(-1); },
//        Qt::QueuedConnection);

    QTcpServer *server = new QTcpServer();
    DataReceiver *recieved = new DataReceiver(server);

    QThread threadsocket;
    recieved->moveToThread(&threadsocket);
    server->moveToThread(&threadsocket);
    threadsocket.start();

    QMetaObject::invokeMethod(recieved, "listen");

    QThread threadfile;
    File* file = new File(recieved);
    file->moveToThread(&threadfile);
    threadfile.start();

    DataHandeler* data = new DataHandeler(recieved,file);



    ViewModel *v = new ViewModel(recieved,data,file);


    engine.rootContext()->setContextProperty("mainviewmodel", v);
    qmlRegisterUncreatableType<ViewModel>("Viewmodels", 1 , 0 , "Viewmodel" , "error .... form qml register of viewmodels");



    engine.load(u"qrc:/Gameserver/Main.qml"_qs);

    return app.exec();
}
