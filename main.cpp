
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThread>
#include <QtQuick/QQuickView>
#include "DataReceiver.h"
#include "ViewModel.h"

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

    QThread thread;
    recieved->moveToThread(&thread);
    server->moveToThread(&thread);
    thread.start();

    QMetaObject::invokeMethod(recieved, "listen");
    ViewModel viewModel(recieved);
    engine.rootContext()->setContextObject(&viewModel);



    engine.load(u"qrc:/Gameserver/Main.qml"_qs);

    return app.exec();
}
