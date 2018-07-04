#include "liradsdatabase.h"

#include <iostream>
#include <QTableView>

LiradsCase::LiradsCase(){
    m_id   = 0;
    m_name = "";
}

LiradsDatabase::LiradsDatabase()
{
    m_db_name = "lirads";
    m_table_name = "lirads";

    m_cn_names.push_back("诊断号"); m_en_names.push_back("id");    m_types.push_back("int primary key");
    m_cn_names.push_back("姓名");   m_en_names.push_back("name");     m_types.push_back("vchar");
}

/*

std::string getName(int id, bool cn){
    std::string names[2][20];
    int i = 0;
    names[0][i] = "id int(10) primary key";        names[1][i] = "诊断号";          i++;
    names[0][i] = " ";               names[1][i] = "";            i++;
    names[0][i] = "sex  varchar(2)";               names[1][i] = "性别";            i++;
    names[0][i] = "age  varchar(3)";               names[1][i] = "年龄";            i++;
    names[0][i] = "date varchar(6)";               names[1][i] = "就诊日期";        i++;
    names[0][i] = "time varchar(6)";               names[1][i] = "就诊时间";        i++;
    names[0][i] = "phone varchar(11)";             names[1][i] = "手机号";          i++;
    names[0][i] = "adress varchar(50)";            names[1][i] = "地址";            i++;
    names[0][i] = "identity varchar(18)";       names[1][i] = "身份证";          i++;

    int typ = cn;
    return names[id][typ];
}
*/

void LiradsDatabase::connection(){
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setHostName("localhost");
    m_db.setDatabaseName(m_db_name);
    m_db.setUserName("root");
    m_db.setPassword("yhz");

    if(!m_db.open()){
        qDebug() << "数据库操作失败";
        return;
    }
}

void LiradsDatabase::createTable(){
//    QString m_sql_statement = "create table " + m_db_name + "." + m_table_name + "  ( ";
    QString m_sql_statement = "create table "  + m_table_name + "  ( ";
    int i = 0;
    for(i=0; i<m_en_names.size()-1; ++i)
        m_sql_statement += m_en_names[i] + " " + m_types[i] + ", ";
    m_sql_statement += m_en_names[i] + " " + m_types[i] + " )";

    std::cout << m_sql_statement.toStdString() << std::endl;

    QSqlQuery query;

    query.exec(m_sql_statement);
    LiradsCase lirads_case;    lirads_case.m_id = 1;    lirads_case.m_name = "习洗洗";
    insert(lirads_case);

//    query.exec("insert into student values (0,'yafei0')");
//    query.exec("insert into student values (1,'yafei1')");
//    query.exec("insert into student values (2,'yafei2')");
}

void LiradsDatabase::show(){

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(QString("select * from ") + m_table_name);
    model->setHeaderData(0, Qt::Horizontal, "id");
    model->setHeaderData(1, Qt::Horizontal, "name");
    QTableView *view = new QTableView;
    view->setModel(model);
    view->show();
}

void LiradsDatabase::insert(const LiradsCase &lirads_case){
    QString m_sql_statement = "insert into " + m_table_name + " values ( "
            + QString::number(lirads_case.m_id) + ", "
            + "'" + lirads_case.m_name + "' "
            + ")";

    QSqlQuery query;
    std::cout << m_sql_statement.toStdString() << std::endl;
    query.exec(m_sql_statement);
}




boost::shared_ptr<QSqlQueryModel> LiradsDatabase::getModel(){
    boost::shared_ptr<QSqlQueryModel> model = boost::shared_ptr<QSqlQueryModel>(new QSqlQueryModel);
    model->setQuery(QString("select * from ") + m_table_name);
    model->setHeaderData(0, Qt::Horizontal, "id");
    model->setHeaderData(1, Qt::Horizontal, "name");
    return model;
}
