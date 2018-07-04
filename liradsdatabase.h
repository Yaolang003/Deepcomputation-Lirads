#ifndef LIRADSDATABASE_H
#define LIRADSDATABASE_H

#include <QSqlDatabase>
#include <QString>
#include <QVector>
#include <mysql/mysql.h>
#include <QtSql>
#include <boost/shared_ptr.hpp>



class LiradsDatabase
{
public:
    LiradsDatabase();
    ~LiradsDatabase();

public:
    void setSqlDriver(const QString& sqlDriver);
    void setConnectionName(const QString& connectionName);
    void setHostName(const QString& hostName);
    void setUserName(const QString& userName);
    void setPassword(const QString& password);
    void setDatabaseName(const QString& dbName);

    QString getConnectionName() const;
    QString getSqlDriver() const;
    QString getHostName() const;
    QString getUserName() const;
    QString getPassword() const;
    QString getDatabaseName() const;
    bool    isOpen() const;

    void open();
    void close();
//    virtual void createTable() = 0;
//    virtual void show()        = 0;
//    virtual boost::shared_ptr<QSqlQueryModel> getModel() = 0;

private:
    QString      m_connectionName;
    QString      m_sqlDriver;
    QString      m_hostName;
    QString      m_userName;
    QString      m_password;
    QString      m_dbName;
    QSqlDatabase m_db;
    bool         m_isOpen;

};

#endif // LIRADSDATABASE_H
