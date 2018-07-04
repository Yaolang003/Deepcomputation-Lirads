#ifndef CASEIMAGEFORM_H
#define CASEIMAGEFORM_H

#include <QWidget>
#include "patientdatabase.h"
#include "showtableform.h"
struct CaseImageGet
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
Q_DECLARE_METATYPE(CaseImageGet);

namespace Ui {
class caseimageform;
}

class caseimageform : public QWidget
{
    Q_OBJECT
public:
    explicit caseimageform(QWidget *parent = 0);
    ~caseimageform();
private slots:

    void save_caseimage(QVariant);

    void on_submit_clicked();

    void on_uploadimage_clicked();

    void on_savefile_clicked();

signals:

    void turnback();


private:
    Ui::caseimageform *ui;
};

#endif // CASEIMAGEFORM_H
