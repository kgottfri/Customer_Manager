#include "backend.h"
#include "connector.h"
#include <stdlib.h>
#include <iostream>
#include <QQmlComponent>
#include <QDebug>
#include <QQuickItem>

BackEnd::BackEnd()
{
}

QString BackEnd::userName()
{
    return m_userName;
}

void BackEnd::setUserName(const QString &userName)
{
    if (userName == m_userName)
        return;

    m_userName = userName;
    emit userNameChanged();
}

void BackEnd::addUser(std::string usr){
    /* Create a table in the database */
    pstmt = con->prepareStatement("INSERT INTO user(username) VALUES (?)");
    pstmt->setString(1, usr);
    pstmt->execute();

    delete pstmt;
    return;
}
