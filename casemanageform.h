#ifndef CASEMANAGEFORM_H
#define CASEMANAGEFORM_H

#include <QWidget>
#include "patientdatabase.h"

struct PatientGet
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
Q_DECLARE_METATYPE(PatientGet);


namespace Ui {
class CaseManageForm;
}

class CaseManageForm : public QWidget
{
    Q_OBJECT

public:
    explicit CaseManageForm(QWidget *parent = 0);
    ~CaseManageForm();

public:
    Patient readFromUI();
    void writeToUI(const Patient &patient);
    void activeEdit(bool state);

private slots:
    void on_save_clicked();

    void on_search_clicked();

    void on_modify_clicked();

    void on_turn_clicked();

    void on_submit_clicked();

    void on_turndoctor_clicked();

    void save_patient(QVariant);

signals:

    void turnback();

private:
    Ui::CaseManageForm *m_ui;

public:
    PatientDatabase* m_patientDatabase;
};

#endif // CASEMANAGEFORM_H
