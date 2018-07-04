#ifndef LIRADSDATABASE_H
#define LIRADSDATABASE_H

#include <QSqlDatabase>
#include <QString>
#include <QVector>
#include <mysql/mysql.h>
#include <QtSql>
#include <boost/shared_ptr.hpp>

struct LiradsCase
{
    LiradsCase();
    int m_id;
    QString m_name;
};

class LiradsDatabase
{
public:
    LiradsDatabase();


public:
    void connection();
    void createTable();
    void insert(const LiradsCase& lirads_case);
    void remove(const LiradsCase& lirads_case);
    void show();
    LiradsCase randGenLiradsCase();
    boost::shared_ptr<QSqlQueryModel> getModel();

private:
    QSqlDatabase m_db;
    QString m_db_name;
    QString m_table_name;

   // QSqlQuery query;

    QVector<QString> m_cn_names;
    QVector<QString> m_en_names;
    QVector<QString> m_types;
 //   QString          m_sql_statement;
};

#endif // LIRADSDATABASE_H
