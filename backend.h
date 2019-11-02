#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <stdlib.h>
#include <iostream>
#include "connector.h"
#include <QQmlApplicationEngine>



class BackEnd : public Connector
{
    Q_OBJECT

public:
    explicit BackEnd();

    QString userName();
    void setUserName(const QString &userName);
    void addUser(std::string usr);
    void getUser(QQmlApplicationEngine &engine);

signals:
    void userNameChanged();

private:
    QString m_userName;
};



#endif // BACKEND_H
