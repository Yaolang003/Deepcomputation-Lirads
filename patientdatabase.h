#ifndef PATIENTDATABASE_H
#define PATIENTDATABASE_H

#include "liradsdatabase.h"

#include <QString>
#include <QVector>
#include <mysql/mysql.h>
#include <QtSql/QSqlDatabase>
#include <QWidget>


struct Patient
{
    QString patient_id;//就诊号
    QString name;//姓名
    QString sex;//性别
    QString identity;//身份证号(添加外键)
    QString age;//年龄
    QString birth;//出生日期
    QString phone;//联系电话
    QString address;//联系地址
    QString imagepath;//照片地址
    QString family_member_one;//家属1姓名
    QString family_member_one_phone;//家属1联系电话
    QString family_member_two;//家属2姓名
    QString family_member_two_phone;//家属2联系电话
    QString password;//用户密码
};

struct Doctor
{
    QString doctor_id;//医生工号
    QString name;//医生姓名
    QString sex;//性别
    QString department;//科室
    QString title;//职称
    QString identity;//身份证号
    QString hospital;//就职医院
    QString imagepath;//照片
    QString phone;//联系电话
    QString password;//医生登陆密码
};

struct CaseImage
{
    QString caseimage_id;//就诊号
    QString date;//影像日期
    QString imagepath;//影像地址
    QString ai_imagepath;//标注返回影像地址
    QString results;//人工诊断结果
    QString ai_results;//AI诊断结果
    QString audit_status;//审核状态
    QString audit_date;//审核日期
    QString report;//诊断报告
    QString diagnostic_state;//人工诊断状态
    QString ai_diagnostic_state;//AI诊断状态
    QString doctor_id;//指向医生库的外键
    QString patient_id;//指向患者库的外键
};


class PatientDatabase : public LiradsDatabase
{
public:
     PatientDatabase();
     ~PatientDatabase();
public:
    void createTable();
    bool insert(const Patient& patient);
    bool remove(const Patient& patient);
    bool query(Patient& patient);
    void show();
//    boost::shared_ptr<QSqlQueryModel> getModel();

private:

    QString m_patient_table;
};


class DoctorDatabase : public LiradsDatabase
{
public:
    DoctorDatabase();
    ~DoctorDatabase();
public:
    void createTable();
    bool insert(const Doctor& doctor);
    bool remove(const Doctor& doctor);
    bool query(Doctor& doctor);
    void show();
//    boost::shared_ptr<QSqlQueryModel> getModel();

private:
    QString m_doctor_table;
};


class CaseImageDatabase : public LiradsDatabase
{
public:
    CaseImageDatabase();
    ~CaseImageDatabase();
public:
    void createTable();
    bool insert(const CaseImage& caseImage);
    bool remove(const CaseImage& caseImage);
    bool query(CaseImage& caseImage);
    void show();
//    boost::shared_ptr<QSqlQueryModel> getModel();

private:
    QString m_caseimage_table;
};;

#endif // PATIENTDATABASE_H

