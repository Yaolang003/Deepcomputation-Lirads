#ifndef DOCTORFORM_H
#define DOCTORFORM_H

#include <QWidget>
#include "patientdatabase.h"
#include "showtableform.h"

struct DoctorGet
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
Q_DECLARE_METATYPE(DoctorGet);

namespace Ui {
class doctorform;
}

class doctorform : public QWidget
{
    Q_OBJECT

public:
    explicit doctorform(QWidget *parent = 0);
    ~doctorform();
private slots:

    void save_doctor(QVariant);

    void on_submit_clicked();

signals:

    void turnback();
private:
    Ui::doctorform *ui;
};

#endif // DOCTORFORM_H
