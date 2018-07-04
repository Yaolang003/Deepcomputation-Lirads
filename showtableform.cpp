#include "showtableform.h"
#include "ui_showtableform.h"

ShowTableForm::ShowTableForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowTableForm)
{
    ui->setupUi(this);
}

ShowTableForm::~ShowTableForm()
{
    delete ui;
}
void ShowTableForm :: on_patient_clicked()
{
    /*
    m_patientDatabase = new PatientDatabase;
    m_liradsDatabase=new LiradsDatabase;
    m_liradsDatabase->open();
    m_patientDatabase->createTable();
    Patient pat;
    pat.patient_id = "123325";
    pat.name = "孙悟空";
    pat.sex = "男";
    pat.identity = "123456789012345678";
    pat.age = "500";
    pat.birth = "20180808";
    pat.phone = "12345678901";
    pat.address = "湖南省湘潭市雨湖区水帘洞";
    pat.imagepath = "/liards/images/timg.jpeg";
    pat.family_member_one = "猪八戒";
    pat.family_member_one_phone = "12233641022";
    pat.family_member_two = "沙悟净";
    pat.family_member_two_phone = "12255633315";
    pat.password = "99864";

    PatientDatabase db;
    db.open();
    db.insert(pat);
    qDebug()<< "打开失败";
*/

    m_patientDatabase = new PatientDatabase;
    m_liradsDatabase=new LiradsDatabase;
    m_liradsDatabase->open();
//    m_patientDatabase->show();
    QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery(QString("select * from ") +"Patient");
        qDebug()<<model;
        qDebug()<<"成功";
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

        ui->tableView->resizeColumnsToContents(); // 自适应列宽
        ui->tableView->setSortingEnabled(true); // 可以按列来排序
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);// 表格单元格为只读
        ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu); // 可以自定义右键菜单
        qDebug()<<"调用成功";
        qDebug()<<model;
        ui->tableView->setModel(model);
/*
    QSqlQueryModel *model = new QSqlQueryModel;
    qDebug()<<model;
    model->setQuery(QString("select * from ") +"Patient");
    qDebug()<<model;
    qDebug()<<"成功";
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
    ui->showtable();

    ui->tableView->resizeColumnsToContents(); // 自适应列宽
    ui->tableView->setSortingEnabled(true); // 可以按列来排序
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);// 表格单元格为只读
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu); // 可以自定义右键菜单
    qDebug()<<model;
    ui->tableView->setModel(model);
*/
}

void ShowTableForm :: on_doctor_clicked()
{
    /*
    m_doctorDatabase = new DoctorDatabase;
    m_liradsDatabase=new LiradsDatabase;
    m_liradsDatabase->open();
    m_doctorDatabase->createTable();

    Doctor doc;
    doc.doctor_id = "000003";
    doc.name = "刘若英";
    doc.sex = "男";
    doc.department = "内科";
    doc.title = "医师";
    doc.identity = "335441199544622224";
    doc.hospital = "湘雅医院";
    doc.imagepath = "liards/images/doc.png";
    doc.phone = "11145532566";
    doc.password = "11234";

    DoctorDatabase ddb;
    ddb.open();
    ddb.createTable();
    ddb.insert(doc);
    */
    m_doctorDatabase = new DoctorDatabase;
    m_liradsDatabase=new LiradsDatabase;
    m_liradsDatabase->open();
    QSqlQueryModel *doctormodel = new QSqlQueryModel;
    doctormodel->setQuery(QString("select * from ") + "Doctor");
    qDebug()<<doctormodel;
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

    ui->tableView->resizeColumnsToContents(); // 自适应列宽
    ui->tableView->setSortingEnabled(true); // 可以按列来排序
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);// 表格单元格为只读
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu); // 可以自定义右键菜单
    qDebug()<<doctormodel;
    ui->tableView->setModel(doctormodel);

}

void ShowTableForm :: on_caseimage_clicked()
{
    /*
    m_caseDatabase = new CaseImageDatabase;
    m_liradsDatabase=new LiradsDatabase;
    m_liradsDatabase->open();
    m_caseDatabase->createTable();
    CaseImage cas;
    cas.caseimage_id = "062201";
    cas.date = "20180622";
    cas.imagepath = "liards/images/doc.png";
    cas.ai_imagepath = "liards/aiimages/doc.png";
    cas.results = "患者暂未发现病情";
    cas.ai_results = "患者暂未发现病情";
    cas.audit_status = "审核中";
    cas.audit_date = "20180623";
    cas.report = "经过人工和AI初步诊断显示，该患者暂未发现病情";
    cas.diagnostic_state = "人工诊断中";
    cas.ai_diagnostic_state = "AI未诊断";
    cas.doctor_id = "000003";
    cas.patient_id = "123325";

    CaseImageDatabase cdb;
    cdb.open();
    cdb.createTable();
    cdb.insert(cas);
    */
    m_liradsDatabase=new LiradsDatabase;
    m_liradsDatabase->open();

    QSqlQueryModel *caseimagemodel = new QSqlQueryModel;
    caseimagemodel->setQuery(QString("select * from ") + "CaseImage");
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

    ui->tableView->resizeColumnsToContents(); // 自适应列宽
    ui->tableView->setSortingEnabled(true); // 可以按列来排序
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);// 表格单元格为只读
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu); // 可以自定义右键菜单

    ui->tableView->setModel(caseimagemodel);

}

void ShowTableForm :: on_quicksearch_clicked()
{
    m_liradsDatabase=new LiradsDatabase;
    m_liradsDatabase->open();
    QSqlQueryModel *quicksearch = new QSqlQueryModel;
    quicksearch->setQuery(QString("select * from CaseImage e right join Patient d on e.patient_id=d.patient_id"));

    ui->tableView->setModel(quicksearch);
    qDebug()<<quicksearch->lastError();
}

void ShowTableForm :: on_delete_2_clicked()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QMYSQL");

  //  db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("lirads2");
    db.setUserName("root");
    db.setPassword("deepcomp");
    if(db.open())
    {
    QSqlQuery query;
    int curRow=ui->tableView->currentIndex().row();//选中行
    QAbstractItemModel *modessl=ui->tableView->model();
    QModelIndex indx1=modessl->index(curRow,0);
    QString    name1=modessl->data(indx1).toString();
    qDebug()<<name1;
    int  row=name1.toInt();


    return;
    if(row>99999)
    {
        query.exec("DELETE FROM Patient WHERE user_id="+name1);
        QSqlQueryModel *model1 = new QSqlQueryModel();
        model1->setQuery("select * from Patient");
        ui->tableView->setModel(model1);
        db.close();
    }
    else
    {
        if(row>9999)
        {
            query.exec("DELETE FROM  CaseImage WHERE user_id="+name1);
            QSqlQueryModel *model1 = new QSqlQueryModel();
            model1->setQuery("select * from CaseImage");
            ui->tableView->setModel(model1);
            db.close();
        }
        else
        {
            query.exec("DELETE FROM  Doctor WHERE user_id="+name1);
            QSqlQueryModel *model1 = new QSqlQueryModel();
            model1->setQuery("select * from Doctor");
            ui->tableView->setModel(model1);
            db.close();
        }
    }

    qDebug()<<"delete data success";
    }
    else
    {
    qDebug()<<"delete data faliure";
    }
}

void ShowTableForm :: on_remove_clicked()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QMYSQL");

  //  db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("lirads2");
    db.setUserName("root");
    db.setPassword("deepcomp");
    if(db.open())
    {
    QSqlQuery query;
    int curRow=ui->tableView->currentIndex().row();//选中行
    QAbstractItemModel *modessl=ui->tableView->model();
    QModelIndex indx1=modessl->index(curRow,0);
    QString    name1=modessl->data(indx1).toString();
    qDebug()<<name1.toInt();
    int  row=name1.toInt();
    if(row>99999)
    {
        //   w->show();
        CaseManageForm *w=new CaseManageForm;

        QObject::connect(this,SIGNAL(data_patient(QVariant)),w,SLOT(save_patient(QVariant)));
        QModelIndex indx1=modessl->index(curRow,0);
        qDebug()<<indx1;
        QString    name1=modessl->data(indx1).toString();
        QModelIndex indx2=modessl->index(curRow,1);
        QString    name2=modessl->data(indx2).toString();
        QModelIndex indx3=modessl->index(curRow,2);
        QString    name3=modessl->data(indx3).toString();
        QModelIndex indx4=modessl->index(curRow,3);
        QString    name4=modessl->data(indx4).toString();
        QModelIndex indx5=modessl->index(curRow,4);
        QString    name5=modessl->data(indx5).toString();
        QModelIndex indx6=modessl->index(curRow,5);
        QString    name6=modessl->data(indx6).toString();
        QModelIndex indx7=modessl->index(curRow,6);
        QString    name7=modessl->data(indx7).toString();
        QModelIndex indx8=modessl->index(curRow,7);
        QString    name8=modessl->data(indx8).toString();
        QModelIndex indx9=modessl->index(curRow,8);
        QString    name9=modessl->data(indx9).toString();
        QModelIndex indx10=modessl->index(curRow,9);
        QString    name10=modessl->data(indx10).toString();
        QModelIndex indx11=modessl->index(curRow,10);
        QString    name11=modessl->data(indx11).toString();
        QModelIndex indx12=modessl->index(curRow,11);
        QString    name12=modessl->data(indx12).toString();
        QModelIndex indx13=modessl->index(curRow,12);
        QString    name13=modessl->data(indx13).toString();
        QModelIndex indx14=modessl->index(curRow,13);
        QString    name14=modessl->data(indx14).toString();


        qDebug()<<indx2;
        qDebug()<<indx3;
        PatientGet save;
//        save.row=curRow;
        save.patient_id=name1;
        save.name=name2;
        save.sex=name3;
        save.identity=name4;
        save.age=name5;
        save.birth=name6;
        save.phone=name7;
        save.address=name8;
        save.imagepath=name9;
        save.family_member_one=name10;
        save.family_member_one_phone=name11;
        save.family_member_two=name12;
        save.family_member_two_phone=name13;
        save.password=name14;

        QVariant namex;
        namex.setValue(save);
        emit data_patient(namex);
        this->hide();
    }
    else
    {
        if(row>9999)
        {

            caseimageform *w=new caseimageform;
//         w->show();
            CaseImageGet save;

            QObject::connect(this,SIGNAL(data_caseimage(QVariant)),w,SLOT(save_caseimage(QVariant)));
            QModelIndex indx1=modessl->index(curRow,0);
            save.caseimage_id=modessl->data(indx1).toString();
            QModelIndex indx2=modessl->index(curRow,1);
            save.date=modessl->data(indx2).toString();
            QModelIndex indx3=modessl->index(curRow,2);
            save.imagepath=modessl->data(indx3).toString();
            QModelIndex indx4=modessl->index(curRow,3);
            save.ai_imagepath=modessl->data(indx4).toString();
            QModelIndex indx5=modessl->index(curRow,4);
            save.results=modessl->data(indx5).toString();
            QModelIndex indx6=modessl->index(curRow,5);
            save.ai_results=modessl->data(indx6).toString();
            QModelIndex indx7=modessl->index(curRow,6);
            save.audit_status=modessl->data(indx7).toString();
            QModelIndex indx8=modessl->index(curRow,7);
            save.audit_date=modessl->data(indx8).toString();
            QModelIndex indx9=modessl->index(curRow,8);
            save.report=modessl->data(indx9).toString();
            QModelIndex indx10=modessl->index(curRow,9);
            save.diagnostic_state=modessl->data(indx10).toString();
            QModelIndex indx11=modessl->index(curRow,10);
            save.ai_diagnostic_state=modessl->data(indx11).toString();
            QModelIndex indx12=modessl->index(curRow,11);
            save.doctor_id=modessl->data(indx12).toString();
            QModelIndex indx13=modessl->index(curRow,12);
            save.patient_id=modessl->data(indx13).toString();
/*
            CaseImageGet save;
            save.row=curRow;
            save.caseimage_id=name1;
            save.date=name2;
            save.imagepath=name3;
            save.ai_imagepath=name4;
            save.results=name5;
            save.ai_results=name6;
            save.audit_status=name7;
            save.audit_date=name8;
            save.report=name9;
            save.diagnostic_state=name10;
            save.ai_diagnostic_state=name11;
            save.doctor_id=name12;
            save.patient_id=name13;
*/
            QVariant namex;
            namex.setValue(save);
            emit data_caseimage(namex);
            this->hide();
        }
        else
        {
            doctorform *w=new doctorform;
            QObject::connect(this,SIGNAL(data_doctor(QVariant)),w,SLOT(save_doctor(QVariant)));
     //       w->show();
            DoctorGet save;
            QModelIndex indx1=modessl->index(curRow,0);
            save.doctor_id=modessl->data(indx1).toString();
            QModelIndex indx2=modessl->index(curRow,1);
            save.name=modessl->data(indx2).toString();
            QModelIndex indx3=modessl->index(curRow,2);
            save.sex=modessl->data(indx3).toString();
            QModelIndex indx4=modessl->index(curRow,3);
            save.department=modessl->data(indx4).toString();
            QModelIndex indx5=modessl->index(curRow,4);
            save.title=modessl->data(indx5).toString();
            QModelIndex indx6=modessl->index(curRow,5);
            save.identity=modessl->data(indx6).toString();
            QModelIndex indx7=modessl->index(curRow,6);
            save.hospital=modessl->data(indx7).toString();
            QModelIndex indx8=modessl->index(curRow,7);
            save.imagepath=modessl->data(indx8).toString();
            QModelIndex indx9=modessl->index(curRow,8);
            save.phone=modessl->data(indx9).toString();
            QModelIndex indx10=modessl->index(curRow,9);
            save.password=modessl->data(indx10).toString();

            QVariant namex;
            namex.setValue(save);
            emit data_doctor(namex);
            this->hide();
        }
    }
    }
}

void ShowTableForm::showpatienttable()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(QString("select * from ") +"Patient");
    qDebug()<<model;
    qDebug()<<"成功";
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

    ui->tableView->resizeColumnsToContents(); // 自适应列宽
    ui->tableView->setSortingEnabled(true); // 可以按列来排序
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);// 表格单元格为只读
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu); // 可以自定义右键菜单
    qDebug()<<"调用成功";
    qDebug()<<model;
    ui->tableView->setModel(model);
}

void ShowTableForm::showdoctortable()
{

    QSqlQueryModel *doctormodel = new QSqlQueryModel;
    doctormodel->setQuery(QString("select * from ") + "Doctor");
    qDebug()<<doctormodel;
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

    ui->tableView->resizeColumnsToContents(); // 自适应列宽
    ui->tableView->setSortingEnabled(true); // 可以按列来排序
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);// 表格单元格为只读
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu); // 可以自定义右键菜单
    qDebug()<<doctormodel;
    ui->tableView->setModel(doctormodel);

}

void ShowTableForm::showcaseimagetable()
{
    QSqlQueryModel *caseimagemodel = new QSqlQueryModel;
    caseimagemodel->setQuery(QString("select * from ") + "CaseImage");
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

    ui->tableView->resizeColumnsToContents(); // 自适应列宽
    ui->tableView->setSortingEnabled(true); // 可以按列来排序
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);// 表格单元格为只读
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu); // 可以自定义右键菜单

    ui->tableView->setModel(caseimagemodel);
}

void ShowTableForm::doctorback()
{
    this->show();
}

void ShowTableForm::caseimageback()
{
    this->show();
}

void ShowTableForm::patientback()
{
    this->show();
}
