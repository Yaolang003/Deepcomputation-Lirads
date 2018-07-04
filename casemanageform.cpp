#include "casemanageform.h"
#include "ui_casemanageform.h"
#include <QDesktopWidget>
#include <QStringList>
#include "caseimageform.h"
#include "doctorform.h"
#include <QMessageBox>

CaseManageForm::CaseManageForm(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::CaseManageForm)
{
    m_ui->setupUi(this);
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    int g_nActScreenW = screenRect.width();
    int g_nActScreenH = screenRect.height();
    this->setWindowTitle("");
    this->resize(960, 800);
    this->move(g_nActScreenW/2-1200/2, g_nActScreenH/2-740/2);


    QStringList conditionItem;
    conditionItem.push_back(" ");
    conditionItem.push_back("就诊号");
    conditionItem.push_back("姓名");
    conditionItem.push_back("身份证号");

    m_ui->condition1->addItems(conditionItem);
    m_ui->condition2->addItems(conditionItem);
    m_ui->condition3->addItems(conditionItem);

    m_ui->sex->addItem("男");
    m_ui->sex->addItem("女");

    activeEdit(false);

    qRegisterMetaType<QVariant>("QVariant");
}

CaseManageForm::~CaseManageForm()
{
    delete m_ui;
}


void CaseManageForm::activeEdit(bool state){
    state = !state;
    //患者
    m_ui->patient_id->setDisabled(state);
    m_ui->name->setDisabled(state);
    m_ui->sex->setDisabled(state);
    m_ui->identity->setDisabled(state);
    m_ui->age->setDisabled(state);
    m_ui->birth->setDisabled(state);
    m_ui->phone->setDisabled(state);
    m_ui->address->setDisabled(state);
//  m_ui->image->setDisabled(state);
    m_ui->family_member_one->setDisabled(state);
    m_ui->family_member_one_phone->setDisabled(state);
    m_ui->family_member_two->setDisabled(state);
    m_ui->family_member_two_phone->setDisabled(state);

    //医生
    /*
    m_ui->doctor_id->setDisabled(state);
    m_ui->d_name->setDisabled(state);
    m_ui->d_sex->setDisabled(state);
    m_ui->d_department->setDisabled(state);
    m_ui->d_titile->setDisabled(state);
    m_ui->d_identity->setDisabled(state);
    m_ui->d_hospital->setDisabled(state);
//  m_ui->d_imagepath->setDisabled(state);
    m_ui->d_phone->setDisabled(state);
    */
}

Patient CaseManageForm::readFromUI(){

}

void CaseManageForm::writeToUI(const Patient& patientInfo)
{
    m_ui->patient_id->setText(patientInfo.patient_id);
    m_ui->name->setText(patientInfo.name);
    //m_ui->sex->Text(patientInfo.sex);
    m_ui->identity->setText(patientInfo.identity);
    m_ui->age->setText(patientInfo.age);
    //m_ui->birth->setText(patientInfo.birth);
    m_ui->phone->setText(patientInfo.phone);
    m_ui->address->setText(patientInfo.address);
    //m_ui->image->setText(patientInfo.image);
    //m_ui->report->setText(patientInfo.report);
}

void CaseManageForm::on_save_clicked()
{
    //...
}

void CaseManageForm::on_search_clicked()
{
 //   activeEdit(true);
    printf("testtest\n");
    Patient patientInfo;
    QString str = m_ui->condition1->currentText().trimmed();
    if(!str.isEmpty()){
        QString val = m_ui->condition1_value->text();
        if(str == "姓名"){
            patientInfo.name = val;
        }
        else if(str == "就诊号"){
            patientInfo.patient_id = val;
        }
        else if(str == "身份证号"){
            patientInfo.identity = val;
        }
    }

    str = m_ui->condition2->currentText().trimmed();
    if(!str.isEmpty()){
        QString val = m_ui->condition2_value->text();
        if(str == "姓名"){
            patientInfo.name = val;
        }
        else if(str == "就诊号"){
            patientInfo.patient_id = val;
        }
        else if(str == "身份证号"){
            patientInfo.identity = val;
        }
    }

    str = m_ui->condition3->currentText().trimmed();
    if(!str.isEmpty()){
        QString val = m_ui->condition3_value->text();
        if(str == "姓名"){
            patientInfo.name = val;
        }
        else if(str == "就诊号"){
            patientInfo.patient_id = val;
        }
        else if(str == "身份证号"){
            patientInfo.identity = val;
        }
    }

    if(m_patientDatabase->query(patientInfo)){
        m_ui->patient_id->setText(patientInfo.patient_id);
    }
    writeToUI(patientInfo);
}

void CaseManageForm::on_modify_clicked()
{
    activeEdit(true);
}

void CaseManageForm::on_turn_clicked()
{
    caseimageform *w=new caseimageform;
    w->show();
}

void CaseManageForm::on_turndoctor_clicked()
{
    doctorform *w=new doctorform;
    w->show();
}

void CaseManageForm::on_submit_clicked()
{
    ShowTableForm *w=new ShowTableForm;
    QObject::connect(this,SIGNAL(turnback()),w,SLOT(patientback()));

    Patient sub;
    sub.patient_id=m_ui->patient_id->text();
    sub.name=m_ui->name->text();
//    sub.sex=m_ui->sex->text();
    sub.sex=m_ui->sex->currentText();
    sub.identity=m_ui->identity->text();
    sub.age=m_ui->age->text();
    sub.birth=m_ui->birth->text();
    sub.phone=m_ui->phone->text();
    sub.address=m_ui->address->text();
    sub.imagepath=m_ui->imagepath->text();
    sub.family_member_one=m_ui->family_member_one->text();
    sub.family_member_one_phone=m_ui->family_member_one_phone->text();
    sub.family_member_two=m_ui->family_member_two->text();
    sub.family_member_two_phone=m_ui->family_member_two_phone->text();
    sub.password="123456";
/*
    if(sub.patient_id==m_ui->patient_id->text())
    {
        QMessageBox::warning(this,tr("warning!"),tr("请重新输入ID"),QMessageBox::Yes);
    }
*/
    PatientDatabase subm;
    subm.insert(sub);

    w->showpatienttable();
    this->hide();
    emit turnback();
}

void CaseManageForm::save_patient(QVariant namex)
{
    PatientGet save=namex.value<PatientGet>();
    save.patient_id=namex.value<PatientGet>().patient_id;
    save.name=namex.value<PatientGet>().name;
    save.sex=namex.value<PatientGet>().sex;
    save.identity=namex.value<PatientGet>().identity;
    save.age=namex.value<PatientGet>().age;
    save.birth=namex.value<PatientGet>().birth;
    save.phone=namex.value<PatientGet>().phone;
    save.address=namex.value<PatientGet>().address;
    save.imagepath=namex.value<PatientGet>().imagepath;
    save.family_member_one=namex.value<PatientGet>().family_member_one;
    save.family_member_one_phone=namex.value<PatientGet>().family_member_one_phone;
    save.family_member_two=namex.value<PatientGet>().family_member_two;
    save.family_member_two_phone=namex.value<PatientGet>().family_member_two_phone;
    save.password=namex.value<PatientGet>().password;

    m_ui->patient_id->setText(save.patient_id);
    m_ui->name->setText(save.name);
    m_ui->sex->setItemText(0,save.sex);
    m_ui->identity->setText(save.identity);
    m_ui->age->setText(save.age);
//    m_ui->birth->setText(save.birth);
    m_ui->phone->setText(save.phone);
    m_ui->address->setText(save.address);
    m_ui->imagepath->setText(save.imagepath);
    m_ui->family_member_one->setText(save.family_member_one);
    m_ui->family_member_one_phone->setText(save.family_member_one_phone);
    m_ui->family_member_two->setText(save.family_member_two);
    m_ui->family_member_two_phone->setText(save.family_member_two_phone);

    this->show();
}
