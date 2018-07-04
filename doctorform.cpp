#include "doctorform.h"
#include "ui_doctorform.h"
#include <QMessageBox>

doctorform::doctorform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::doctorform)
{
    ui->setupUi(this);

    ui->sex->addItem("男");
    ui->sex->addItem("女");

    ui->department->addItem("内科");
    ui->department->addItem("外科");

    ui->titile->addItem("医生");
    ui->titile->addItem("医师");


    qRegisterMetaType<QVariant>("QVariant");
}

doctorform::~doctorform()
{
    delete ui;
}

void doctorform::save_doctor(QVariant namex)
{
    DoctorGet save=namex.value<DoctorGet>();
    ui->doctor_id->setText(namex.value<DoctorGet>().doctor_id);
    ui->name->setText(namex.value<DoctorGet>().name);
    ui->sex->setItemText(0,namex.value<DoctorGet>().sex);
    ui->department->setItemText(0,namex.value<DoctorGet>().department);
    ui->titile->setItemText(0,namex.value<DoctorGet>().title);
    ui->identity->setText(namex.value<DoctorGet>().identity);
    ui->hospital->setText(namex.value<DoctorGet>().hospital);
    ui->imagepath->setText(namex.value<DoctorGet>().imagepath);
    ui->phone->setText(namex.value<DoctorGet>().phone);
//    ui->password->setText(namex.value<DoctorGet>().password);

    this->show();
}

void doctorform::on_submit_clicked()
{
    ShowTableForm *w=new ShowTableForm;
    QObject::connect(this,SIGNAL(turnback()),w,SLOT(doctorback()));

    Doctor sub;
    sub.doctor_id=ui->doctor_id->text();
    sub.name=ui->name->text();
    sub.sex=ui->sex->currentText();//combibox 返回数据
    sub.department=ui->department->currentText();
    sub.title=ui->titile->currentText();
    sub.identity=ui->identity->text();
    sub.hospital=ui->hospital->text();
    sub.imagepath=ui->imagepath->text();
    sub.phone=ui->phone->text();
    sub.password="123456";
/*
    if(sub.doctor_id==ui->doctor_id->text())
    {
        QMessageBox::warning(this,tr("warning!"),tr("请重新输入ID"),QMessageBox::Yes);
    }
*/
    DoctorDatabase subm;
    subm.insert(sub);

    w->showdoctortable();
    this->hide();
    emit turnback();
}
