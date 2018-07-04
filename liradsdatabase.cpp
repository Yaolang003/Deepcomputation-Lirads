#include "liradsdatabase.h"

#include <iostream>
#include <QTableView>


LiradsDatabase::LiradsDatabase()
{
    m_sqlDriver      = "QMYSQL";
    m_connectionName = "db1";
    m_hostName       = "localhost";
    m_userName       = "root";
    m_password       = "deepcomp";
    m_dbName         = "lirads2";
    m_isOpen         = false;
}

LiradsDatabase::~LiradsDatabase(){

}
void LiradsDatabase::setSqlDriver(const QString& sqlDriver)
{
    m_sqlDriver = sqlDriver;
}
void LiradsDatabase::setConnectionName(const QString& connectionName)
{
    m_connectionName = connectionName;
}
void LiradsDatabase::setHostName(const QString& hostName)
{
    m_hostName = hostName;
}
void LiradsDatabase::setUserName(const QString& userName)
{
    m_userName = userName;
}
void LiradsDatabase::setPassword(const QString& password)
{
    m_password = password;
}
void LiradsDatabase::setDatabaseName(const QString& dbName)
{
    m_dbName = dbName;
}

QString LiradsDatabase::getConnectionName() const
{
    return m_connectionName;
}
QString LiradsDatabase::getSqlDriver() const
{
    return m_sqlDriver;
}
QString LiradsDatabase::getHostName() const
{
    return m_hostName;
}
QString LiradsDatabase::getUserName() const
{
    return m_userName;
}
QString LiradsDatabase::getPassword() const
{
    return m_password;
}
QString LiradsDatabase::getDatabaseName() const
{
    return m_dbName;
}

bool LiradsDatabase::isOpen() const
{
    return m_isOpen;
}

void LiradsDatabase::open(){
//  m_db = QSqlDatabase::addDatabase(m_sqlDriver, m_connectionName);
    m_db = QSqlDatabase::addDatabase(m_sqlDriver);
    m_db.setHostName(m_hostName);
    m_db.setDatabaseName(m_dbName);
    m_db.setUserName(m_userName);
    m_db.setPassword(m_password);

    if(!m_db.open()){
        qDebug() << "数据库操作失败";
        qDebug() << m_db.lastError();
        return;
    }
    m_isOpen = true;
}

void LiradsDatabase::close()
{
    m_db.close();
    m_isOpen = false;
}
/*
void LiradsDatabase::createTable()
{

}

void LiradsDatabase::show()
{

}
*/


