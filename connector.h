#ifndef CONNECTOR_H
#define CONNECTOR_H
#include <QObject>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <driver.h>
#include <exception.h>
#include <resultset.h>
#include <statement.h>
#include <cppconn/prepared_statement.h>
#include <stdlib.h>
#include <iostream>

class Connector : public QObject
{
    Q_OBJECT
    public slots:
	void handleInput(const QVariant &msg,const QVariant &numDays);
	void searchName(const QVariant &usr);
    signals:
	void sendSearch(const QVariant &name, const QVariant &st);
	void sendAdd(const QVariant &name, const QVariant &st);
    public:
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    sql::PreparedStatement *pstmt;
    sql::PreparedStatement *pstmt1;
    Connector(QObject *parent = nullptr);
    bool isConnected();
    std::string getNull();

};

#endif // CONNECTOR_H
