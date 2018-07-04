#include "caseimageform.h"
#include "ui_caseimageform.h"
#include <QMessageBox>
#include <QFileDialog>
caseimageform::caseimageform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::caseimageform)
{
    ui->setupUi(this);

    ui->audit_status->addItem("待审核");
    ui->audit_status->addItem("审核中");
    ui->audit_status->addItem("已审核");

    ui->diagnostic_state->addItem("待诊断");
    ui->diagnostic_state->addItem("诊断中");
    ui->diagnostic_state->addItem("已诊断");

    ui->aidiagnostic_state->addItem("待诊断");
    ui->aidiagnostic_state->addItem("诊断中");
    ui->aidiagnostic_state->addItem("已诊断");

    qRegisterMetaType<QVariant>("QVariant");
}

caseimageform::~caseimageform()
{
    delete ui;
}

void caseimageform::save_caseimage(QVariant namex)
{
    CaseImageGet save=namex.value<CaseImageGet>();
    ui->caseimage_id->setText(namex.value<CaseImageGet>().caseimage_id);
    ui->date->setDisplayFormat(namex.value<CaseImageGet>().date);//QDateEdit 显示数据
    ui->imagepath->setText(namex.value<CaseImageGet>().imagepath);
    ui->ai_imagepath->setText(namex.value<CaseImageGet>().ai_imagepath);
    ui->results->setText(namex.value<CaseImageGet>().results);
    ui->airesults->setText(namex.value<CaseImageGet>().ai_results);
    ui->audit_status->setItemText(0,namex.value<CaseImageGet>().audit_status);
    ui->audit_date->setDisplayFormat(namex.value<CaseImageGet>().audit_date);
    ui->report->setText(namex.value<CaseImageGet>().report);
    ui->diagnostic_state->setItemText(0,namex.value<CaseImageGet>().diagnostic_state);
    ui->aidiagnostic_state->setItemText(0,namex.value<CaseImageGet>().ai_diagnostic_state);
//  ui->doctor_id->setText(namex.value<CaseImageGet>().doctor_id);
//  ui->patient_id->setText(namex.value<CaseImageGet>().patient_id);
    this->show();
}

void caseimageform::on_submit_clicked()
{
    ShowTableForm *w=new ShowTableForm;
    QObject::connect(this,SIGNAL(turnback()),w,SLOT(caseimageback()));

    CaseImage sub;
    sub.caseimage_id=ui->caseimage_id->text();
    sub.date=ui->date->text();
    sub.imagepath=ui->imagepath->text();
    sub.ai_imagepath=ui->ai_imagepath->text();
    sub.results=ui->results->document()->toPlainText();
    sub.ai_results=ui->airesults->document()->toPlainText();
    sub.audit_status=ui->audit_status->currentText();
    sub.audit_date=ui->audit_date->text();
    sub.report=ui->report->document()->toPlainText();
//    sub.diagnostic_state=ui->diagnostic_state->text();
//    sub.ai_diagnostic_state=ui->aidiagnostic_state->text();
    sub.diagnostic_state=ui->diagnostic_state->currentText();
    sub.ai_diagnostic_state=ui->aidiagnostic_state->currentText();
    sub.doctor_id="3";
    sub.patient_id="123325";
/*
    if(sub.caseimage_id==ui->caseimage_id->text())
    {
        QMessageBox::warning(this,tr("warning!"),tr("请重新输入ID"),QMessageBox::Yes);
        return;
    }
*/
    CaseImageDatabase subm;
    subm.insert(sub);

    w->showcaseimagetable();
    this->hide();
    emit turnback();
}

void caseimageform::on_uploadimage_clicked()
{
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(tr("打开图片"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件器
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    //设置可以选择多个文件，默认为只能选择一个文件QFileDialog::ExistingFiles
    fileDialog->setFileMode(QFileDialog::ExistingFiles);

    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //打印所有选择的文件的路径
    QStringList fileNames;

    if(fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
    }
    qDebug()<<fileNames;
    for(auto tmp:fileNames)
    {
        qDebug()<<tmp;
//        qDebug()<<tmp[1];
    QString file=fileNames.join("");
        qDebug()<<file;

        QImage *imgSource = new QImage(QString(file));

        ui->image1->resize(imgSource->width(),imgSource->height());
        QImage *imgScaled = new QImage();


        *imgScaled = imgSource->scaled(400,160,Qt::KeepAspectRatio);
        ui->image1->setMaximumSize(400,160);

        ui->image1->setPixmap(QPixmap::fromImage(*imgScaled));
    }
}

void caseimageform::on_savefile_clicked()
{
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(tr("打开图片"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件器
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    //设置可以选择多个文件，默认为只能选择一个文件QFileDialog::ExistingFiles
    fileDialog->setFileMode(QFileDialog::ExistingFiles);

    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //打印所有选择的文件的路径
    QStringList fileNames;

    if(fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
    }
    qDebug()<<fileNames;
    for(auto tmp:fileNames)
    {
        qDebug()<<tmp;
        qDebug()<<tmp[1];
    QString file=fileNames.join("");
        qDebug()<<file;

        QImage *imgSource = new QImage(QString(file));

        ui->ai_image->resize(imgSource->width(),imgSource->height());
        QImage *imgScaled = new QImage();


        *imgScaled = imgSource->scaled(400,160,Qt::KeepAspectRatio);
        ui->ai_image->setMaximumSize(400,160);

        ui->ai_image->setPixmap(QPixmap::fromImage(*imgScaled));


    }
}
