#ifndef SHOWTABLEFORM_H
#define SHOWTABLEFORM_H

#include <QWidget>
#include "patientdatabase.h"
#include "liradsdatabase.h"
#include "caseimageform.h"
#include "doctorform.h"
#include "casemanageform.h"


namespace Ui {
class ShowTableForm;
}

class ShowTableForm : public QWidget
{
    Q_OBJECT

public:
    explicit ShowTableForm(QWidget *parent = 0);
    ~ShowTableForm();

    void showpatienttable();

    void showdoctortable();

    void showcaseimagetable();

private slots:
    void on_patient_clicked();

    void on_doctor_clicked();

    void on_caseimage_clicked();

    void on_quicksearch_clicked();

    void on_delete_2_clicked();

    void on_remove_clicked();

    void doctorback();

    void caseimageback();

    void patientback();

signals:
    void data_patient(QVariant);

    void data_doctor(QVariant);

    void data_caseimage(QVariant);

private:
    Ui::ShowTableForm *ui;

    PatientDatabase*   m_patientDatabase;
    DoctorDatabase*   m_doctorDatabase;
    CaseImageDatabase*  m_caseDatabase;
    LiradsDatabase*   m_liradsDatabase;

    QSqlDatabase db;
};

#endif // SHOWTABLEFORM_H
