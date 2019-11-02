#include <connector.h>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <driver.h>
#include <exception.h>
#include <resultset.h>
#include <statement.h>
#include <cppconn/prepared_statement.h>
#include <stdlib.h>
#include <iostream>
#include <QVariant>
#include <QQmlProperty>
#include <QString>

using namespace std;

sql::Driver *driver;
sql::Connection *con;
sql::Statement *stmt;
sql::ResultSet *res;
sql::PreparedStatement *pstmt;

Connector::Connector(QObject *parent) :
    QObject(parent)
{

}
bool Connector::isConnected(void)
{
    bool didConnect = true;
    try {

    /* Create a connection */
    driver = get_driver_instance();
    /* Connect to the MySQL database */
    con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
    con->setSchema("Ski");

    didConnect = true; // boolean to test connection to the database;
    }
    catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	didConnect = false;
    }

    return didConnect;
}

/*handles the input from the lastname and num days inputs and adds them to the database using the first empty slot via
getNull()*/
void Connector::handleInput(const QVariant &lastName,const QVariant &numDays) {
    /* Create a table in the database */
    QString st = lastName.toString();
    pstmt = con->prepareStatement("UPDATE user SET lastname = (?) , numDays = (?) WHERE slot = (?)");
    std::string slot = this->getNull();

    pstmt->setString(1, st.toStdString()); //add the lastname to the prepare statement
    pstmt->setInt(2,numDays.toInt()); // add the number of days to the prepare statement
    pstmt->setString(3,slot); // the slot id of the first open row in the db
    pstmt->execute();
    QVariant slt = QString::fromStdString(slot);
    emit sendAdd(lastName,slt);
    delete pstmt;
    return;
}

/*Handle input from the lastname category and search for that last name in the database*/
void Connector::searchName(const QVariant &usr){
    pstmt = con->prepareStatement("SELECT * FROM user WHERE lastname = (?)");
    QString str = usr.toString();
    pstmt->setString(1,str.toStdString());
    res = pstmt->executeQuery();
    std::string getSlot;
    if(res->next() != 0){
	getSlot = res->getString("slot");
    }
    QVariant st = QString::fromStdString(getSlot);

    emit sendSearch(usr, st);
    delete pstmt;
    delete res;
    return;
}

/*Search the database for the first empty slot to be assigned to a customer*/
std::string Connector::getNull(){
    pstmt1 = con->prepareStatement("SELECT * FROM user WHERE lastname IS NULL");
    res = pstmt1->executeQuery();
    std::string slot;
    if(res->next() != 0){
	slot = res->getString("slot");
    }
    delete pstmt1;
    delete res;
    return  slot;


}

