#include "patientdatabase.h"
#include <iostream>
#include <QTableView>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>
#include <QDebug>
#include <QtSql/QSqlError>
#include "showtableform.h"
/*
 *以下进行患者数据库的建表,插入数据,修改数据,信息认证,展示数据
 */
PatientDatabase::PatientDatabase()
{
   m_patient_table = "Patient";
}
PatientDatabase::~PatientDatabase()
{

}
void PatientDatabase::createTable()
{
    QString sql_table_statement = "create table "  + m_patient_table + "  ( " +
            "patient_id int primary key not null, " +
            "name varchar(30), " +
            "sex varchar(2), " +
            "identity varchar(18), " +
            "age int, " +
            "birth varchar(10), " +
            "phone varchar(11), " +
            "address varchar(128), " +
            "imagePath varchar(128), "+
            "family_member_one varchar(30), " +
            "family_member_one_phone varchar(11), " +
            "family_member_two varchar(30),"+
            "family_member_two_phone varchar(11),"+
            "password varchar(30)"+
            " )"+"ENGINE=InnoDB DEFAULT CHARSET=UTF8";

    std::cout << sql_table_statement.toStdString() << std::endl;

    QSqlQuery sql_table;
    sql_table.exec(sql_table_statement);
    qDebug()<<sql_table.lastError();
}


bool PatientDatabase::insert(const Patient &patient)
{
    QString sql_insert_statement =  "insert into " + m_patient_table + " values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    QSqlQuery sql_insert;
    sql_insert.prepare(sql_insert_statement);
    sql_insert.addBindValue(patient.patient_id);
    sql_insert.addBindValue(patient.name);
    sql_insert.addBindValue(patient.sex);
    sql_insert.addBindValue(patient.identity);
    sql_insert.addBindValue(patient.age);
    sql_insert.addBindValue(patient.birth);
    sql_insert.addBindValue(patient.phone);
    sql_insert.addBindValue(patient.address);
    sql_insert.addBindValue(patient.imagepath);
    sql_insert.addBindValue(patient.family_member_one);
    sql_insert.addBindValue(patient.family_member_one_phone);
    sql_insert.addBindValue(patient.family_member_two);
    sql_insert.addBindValue(patient.family_member_two_phone);
    sql_insert.addBindValue(patient.password);

    if(!sql_insert.exec())
    {

        qDebug() << sql_insert.lastError();
        return false;
    }
    else
    {
        qDebug() << "inserted sucssefully!";
        return true;
    }
}

bool PatientDatabase::remove(const Patient &patient)
{

}
bool PatientDatabase::query(Patient &patient){
    Patient query_patientInfo;
    QString sql_query_statement =  "select * from " + m_patient_table;
    QSqlQuery sql_query;
    sql_query.prepare(sql_query_statement);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        return false;
    }
    else{
        while(sql_query.next())
        {
            query_patientInfo.patient_id = sql_query.value("patient_id").toString();
            if( !patient.patient_id.isEmpty() && query_patientInfo.patient_id != patient.patient_id ){
                continue;
            }
            query_patientInfo.name = sql_query.value("name").toString();
            if( !patient.name.isEmpty() && query_patientInfo.name != patient.name ){
                continue;
            }
            query_patientInfo.sex = sql_query.value("sex").toString();
            if( !patient.sex.isEmpty() && query_patientInfo.sex != patient.sex ){
                continue;
            }
            query_patientInfo.identity = sql_query.value("identity").toString();
            if( !patient.identity.isEmpty() && query_patientInfo.identity != patient.identity ){
                continue;
            }
            query_patientInfo.age = sql_query.value("age").toString();
            if( !patient.age.isEmpty() && query_patientInfo.age != patient.age ){
                continue;
            }
            query_patientInfo.birth = sql_query.value("birth").toString();
            if( !patient.birth.isEmpty() && query_patientInfo.birth != patient.birth ){
                continue;
            }
            query_patientInfo.phone = sql_query.value("phone").toString();
            if( !patient.phone.isEmpty() && query_patientInfo.phone != patient.phone ){
                continue;
            }
            query_patientInfo.address = sql_query.value("address").toString();
            query_patientInfo.family_member_one = sql_query.value("family_member_one").toString();
            query_patientInfo.family_member_one_phone = sql_query.value("family_member_one_phone").toString();
            query_patientInfo.family_member_two = sql_query.value("family_member_two").toString();
            query_patientInfo.family_member_two_phone = sql_query.value("family_member_two_phone").toString();
            patient = query_patientInfo;

            return true;
        }
    }
    return false;
}
void PatientDatabase::show()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(QString("select * from ") + m_patient_table);
    qDebug()<<model;
    model->setHeaderData(0, Qt::Horizontal, "就诊号");
    model->setHeaderData(1, Qt::Horizontal, "姓名");
    model->setHeaderData(2, Qt::Horizontal, "性别");
    model->setHeaderData(3, Qt::Horizontal, "身份证");
    model->setHeaderData(4, Qt::Horizontal, "年龄");
    model->setHeaderData(5, Qt::Horizontal, "出生日期");
    model->setHeaderData(6, Qt::Horizontal, "手机");
    model->setHeaderData(7, Qt::Horizontal, "地址");
    model->setHeaderData(8, Qt::Horizontal, "照片");
    model->setHeaderData(9, Qt::Horizontal, "家庭成员之一");
    model->setHeaderData(10, Qt::Horizontal, "家庭成员一的电话");
    model->setHeaderData(11, Qt::Horizontal, "家庭成员之二");
    model->setHeaderData(12, Qt::Horizontal, "家庭成员二的电话");
    model->setHeaderData(13, Qt::Horizontal, "密码");

    ShowTableForm *ui=new ShowTableForm;
    qDebug()<<"调用函数";
//  ui->showtable();
}

/*
 * 以下进行医生数据库创建,插入数据,修改数据,读取表格
 */
DoctorDatabase::DoctorDatabase()
{
    m_doctor_table = "Doctor";
}

DoctorDatabase::~DoctorDatabase()
{

}

void DoctorDatabase::createTable()
{
    QString sql_table_statement = "create table "  + m_doctor_table + "  ( " +
            "doctor_id int primary key not null, " +
            "name varchar(30), " +
            "sex varchar(2), " +
            "department varchar(30), " +
            "title varchar(30), " +
            "identity varchar(18), " +
            "hospital varchar(30),"+
            "imagepath varchar(128), "+
            "phone varchar(11), " +
            "password varchar(20) " +
            " )"+"ENGINE=InnoDB DEFAULT CHARSET=UTF8";

    std::cout << sql_table_statement.toStdString() << std::endl;

    QSqlQuery sql_table;
    sql_table.exec(sql_table_statement);
}

bool DoctorDatabase::insert(const Doctor &doctor)
{
    QString sql_insert_statement =  "insert into " + m_doctor_table + " values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    QSqlQuery sql_insert;
    sql_insert.prepare(sql_insert_statement);
    sql_insert.addBindValue(doctor.doctor_id);
    sql_insert.addBindValue(doctor.name);
    sql_insert.addBindValue(doctor.sex);
    sql_insert.addBindValue(doctor.department);
    sql_insert.addBindValue(doctor.title);
    sql_insert.addBindValue(doctor.identity);
    sql_insert.addBindValue(doctor.hospital);
    sql_insert.addBindValue(doctor.imagepath);
    sql_insert.addBindValue(doctor.phone);
    sql_insert.addBindValue(doctor.password);

    if(!sql_insert.exec())
    {

        qDebug() << sql_insert.lastError();
        return false;
    }
    else
    {
        qDebug() << "inserted sucssefully!";
        return true;
    }
}

bool DoctorDatabase::remove(const Doctor &doctor)
{

}

void DoctorDatabase::show()
{
    QSqlQueryModel *doctormodel = new QSqlQueryModel;
    doctormodel->setQuery(QString("select * from ") + m_doctor_table );
    doctormodel->setHeaderData(0, Qt::Horizontal, "工号");
    doctormodel->setHeaderData(1, Qt::Horizontal, "姓名");
    doctormodel->setHeaderData(2, Qt::Horizontal, "性别");
    doctormodel->setHeaderData(3, Qt::Horizontal, "科室");
    doctormodel->setHeaderData(4, Qt::Horizontal, "职称");
    doctormodel->setHeaderData(5, Qt::Horizontal, "身份证号");
    doctormodel->setHeaderData(6, Qt::Horizontal, "就职医院");
    doctormodel->setHeaderData(7, Qt::Horizontal, "照片");
    doctormodel->setHeaderData(8, Qt::Horizontal, "联系电话");
    doctormodel->setHeaderData(9, Qt::Horizontal, "密码");

    QTableView *doctorview = new QTableView;
    doctorview->setModel(doctormodel);
    doctorview->resize(1200, 400);
    doctorview->show();
}

/*
 * 以下进行病例影像库的创建
 */
CaseImageDatabase::CaseImageDatabase()
{
    m_caseimage_table = "CaseImage";
}

CaseImageDatabase::~CaseImageDatabase()
{

}

void CaseImageDatabase::createTable()
{
    QString sql_table_statement = "create table "  + m_caseimage_table + "  ( " +
            "caseimage_id int primary key not null, " +
            "date varchar(20), " +
            "imagepath varchar(128), " +
            "ai_imagepath varchar(30), " +
            "results varchar(64), " +
            "ai_results varchar(64), " +
            "audit_status varchar(30),"+
            "audit_date varchar(128), "+
            "report varchar(128), " +
            "diagnostic_state varchar(20), " +
            "ai_diagnostic_state varchar(20), "+
            "doctor_id int(20),"+
            "patient_id int(20),"+
            "foreign key(doctor_id) references Doctor(doctor_id),"+
            "foreign key(patient_id) references Patient(patient_id)"
            " )"+"ENGINE=InnoDB DEFAULT CHARSET=UTF8";

    std::cout << sql_table_statement.toStdString() << std::endl;

    QSqlQuery sql_table;
    sql_table.exec(sql_table_statement);
    qDebug()<<sql_table.lastError();
}

bool CaseImageDatabase::insert(const CaseImage &caseimage)
{
    QString sql_insert_statement =  "insert into " + m_caseimage_table + " values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    QSqlQuery sql_insert;
    sql_insert.prepare(sql_insert_statement);
    sql_insert.addBindValue(caseimage.caseimage_id);
    sql_insert.addBindValue(caseimage.date);
    sql_insert.addBindValue(caseimage.imagepath);
    sql_insert.addBindValue(caseimage.ai_imagepath);
    sql_insert.addBindValue(caseimage.results);
    sql_insert.addBindValue(caseimage.ai_results);
    sql_insert.addBindValue(caseimage.audit_status);
    sql_insert.addBindValue(caseimage.audit_date);
    sql_insert.addBindValue(caseimage.report);
    sql_insert.addBindValue(caseimage.diagnostic_state);
    sql_insert.addBindValue(caseimage.ai_diagnostic_state);
    sql_insert.addBindValue(caseimage.doctor_id);
    sql_insert.addBindValue(caseimage.patient_id);
    if(!sql_insert.exec())
    {

        qDebug() << sql_insert.lastError();
        return false;
    }
    else
    {
        qDebug() << "inserted sucssefully!";
        return true;
    }
}

bool CaseImageDatabase::remove(const CaseImage &caseimage)
{

}

void CaseImageDatabase::show()
{
    QSqlQueryModel *caseimagemodel = new QSqlQueryModel;
    caseimagemodel->setQuery(QString("select * from ") + m_caseimage_table );
    caseimagemodel->setHeaderData(0, Qt::Horizontal, "就诊号");
    caseimagemodel->setHeaderData(1, Qt::Horizontal, "影像日期");
    caseimagemodel->setHeaderData(2, Qt::Horizontal, "影像地址");
    caseimagemodel->setHeaderData(3, Qt::Horizontal, "标注返回影像地址");
    caseimagemodel->setHeaderData(4, Qt::Horizontal, "人工诊断结果");
    caseimagemodel->setHeaderData(5, Qt::Horizontal, "AI诊断结果");
    caseimagemodel->setHeaderData(6, Qt::Horizontal, "审核状态");
    caseimagemodel->setHeaderData(7, Qt::Horizontal, "审核日期");
    caseimagemodel->setHeaderData(8, Qt::Horizontal, "诊断报告");
    caseimagemodel->setHeaderData(9, Qt::Horizontal, "人工诊断状态");
    caseimagemodel->setHeaderData(10, Qt::Horizontal, "AI诊断状态");

    QTableView *caseimageview = new QTableView;
    caseimageview->setModel(caseimagemodel);
    caseimageview->resize(1200, 400);
    caseimageview->show();


}




/*
boost::shared_ptr<QSqlQueryModel> PatientDatabase::getModel()
{
    boost::shared_ptr<QSqlQueryModel> model = boost::shared_ptr<QSqlQueryModel>(new QSqlQueryModel);
 //   model->setQuery(QString("select * from ") + m_table_name);
 //   model->setHeaderData(0, Qt::Horizontal, "id");
 //   model->setHeaderData(1, Qt::Horizontal, "name");
    return model;
}
*/
