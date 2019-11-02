#include "backend.cpp"
#include <connector.cpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <stdlib.h>
#include <iostream>
#include <QQmlComponent>
#include <QQmlProperty>
#include <QMetaObject>
#include <QVariant>
#include <QDebug>
#include <QQuickView>
#include <QThread>



using namespace std;

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine; //testing application window vs quickview
    engine.load(QUrl(QStringLiteral("/Users/kevingottfried/Documents/Customer_Manager/main.qml")));

    BackEnd backEnd;
    Connector connection;
    connection.isConnected();

    QObject *item = engine.rootObjects()[0];
    QObject *submit= item->findChild<QObject *>("submit");
    QObject *search = item->findChild<QObject *>("search");
    QObject::connect(submit, SIGNAL(submitTextField(QVariant, QVariant)), &connection, SLOT(handleInput(QVariant, QVariant)));
    QObject::connect(search, SIGNAL(searchDb(QVariant)), &connection, SLOT(searchName(QVariant)));
    QObject::connect(&connection, SIGNAL(sendSearch(QVariant,QVariant)), item, SLOT(searchRes(QVariant, QVariant)));
    QObject::connect(&connection, SIGNAL(sendAdd(QVariant,QVariant)), item, SLOT(displayAdd(QVariant, QVariant)));

    return app.exec();
}
