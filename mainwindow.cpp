#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <assert.h>
#include "imageconvertor.h"
#include "beziercurve.h"
#include "casemanageform.h"
#include <QGraphicsScene>
#include <QMouseEvent>
#include <iostream>
#include <QMatrix>
#include <QDesktopWidget>

#include <vector>
#include <QPoint>
#include <QDebug>
#include <QFileDialog>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow){
    m_ui->setupUi(this);

    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    int g_nActScreenW = screenRect.width();
    int g_nActScreenH = screenRect.height();
    this->setWindowTitle("");
    this->resize(1500, 880);
    this->move(g_nActScreenW/2-1500/2, g_nActScreenH/2-880/2);


    m_pix0 = new QPixmap;
    m_pix  = new QPixmap;
    m_patientDatabase = new PatientDatabase;
    m_patientDatabase->open();
    m_patientDatabase->createTable();

    this->setDefaultParameters();
 }


MainWindow::~MainWindow(){
    delete m_patientDatabase;
    delete m_pix;
    delete m_pix0;
    delete m_ui;
}

void MainWindow::setDefaultParameters(){
    m_ratio     = 1.0;
    m_action    = MainWindow::None;
    m_rotate  = 0;

    m_paintRect = QRect(30, 150, 1140, 665);
    m_pixRect   = m_paintRect;
    m_pixPos    = QPoint(0, 0);
    m_offset    = QPoint(0, 0);
    m_press     = false;
    m_originPoints.clear();
    m_curvePoints.clear();
}

bool MainWindow::updatePix()
{
    *m_pix = *m_pix0;
    if(m_pix->data_ptr() == 0 ) return false;
    // rotate
    m_rotate = m_rotate % 4;
    m_rotate = m_rotate >= 0 ? m_rotate : m_rotate + 4;

    QMatrix  rotateMat;
    rotateMat.rotate(m_rotate*90);
    *m_pix = m_pix->transformed(rotateMat);

    //// for m_ratio
    int pixWidth  = m_pix->width() * m_ratio;
    int pixHeight = m_pix->height() * m_ratio;
   // if( m_action == MainWindow::Zoom )
    {
         *m_pix = m_pix->scaled(pixWidth, pixHeight);
    }

    //// for m_offset
    int max_offset_width   = m_paintRect.width() /2 + pixWidth /2 -10;
    int max_offset_height  = m_paintRect.height()/2 + pixHeight/2 -10;

    if( m_offset.x() <=  -max_offset_width )
    {
        m_offset.setX( -max_offset_width );
    }
    else if( m_offset.x() > max_offset_width )
    {
        m_offset.setX( max_offset_width );
    }

    if( m_offset.y() <  -max_offset_height )
    {
        m_offset.setY( -max_offset_height );
    }
    else if( m_offset.y() > max_offset_height )
    {
        m_offset.setY( max_offset_height );
    }

    int pixRect_x =  m_paintRect.width()/2 + m_offset.x() - pixWidth/2;
    if( pixRect_x < 0 )
    {
        pixRect_x = 0;
    }
    //pixRect_x += m_paintRect.x();
    int pixRect_y = m_paintRect.height()/2 + m_offset.y() - pixHeight/2;
    if( pixRect_y < 0 )
    {
        pixRect_y = 0;
    }
    //pixRect_y += m_paintRect.y();

    int pixPos_x = pixWidth/2  - m_paintRect.width()/2  - m_offset.x();
    if( pixPos_x < 0)
    {
        pixPos_x = 0;
    }
    int pixPos_y = pixHeight/2 - m_paintRect.height()/2 - m_offset.y();
    if( pixPos_y < 0)
    {
        pixPos_y = 0;
    }

    int pixRect_width  = (pixWidth  - pixPos_x) > m_paintRect.width() ?
                m_paintRect.width() : (pixWidth  - pixPos_x);
    if( pixRect_width >  (m_paintRect.width() - pixRect_x) )
    {
        pixRect_width = m_paintRect.width() - pixRect_x;
    }

    int pixRect_height = (pixHeight - pixPos_y ) > m_paintRect.height() ?
                m_paintRect.height() : (pixHeight - pixPos_y);
    if( pixRect_height > (m_paintRect.height() - pixRect_y) )
    {
        pixRect_height = m_paintRect.height() - pixRect_y;
    }

    pixRect_x += m_paintRect.x();
    pixRect_y += m_paintRect.y();
    m_pixRect = QRect(pixRect_x, pixRect_y, pixRect_width, pixRect_height);
    m_pixPos  = QPoint(pixPos_x, pixPos_y);

    /// for marked
    if(m_action == MainWindow::Marked && !m_curvePoints.empty()){

        QPainter painter(m_pix0);
        float ratio = (float)m_pix0->width()/m_pix->width();

        for(QVector<QPoint>::iterator it= m_curvePoints.begin();
            it != m_curvePoints.end(); ++it){
            int x = ( (it->x() - m_pixRect.x() )  ) * ratio + m_pixPos.x()/m_ratio;
            int y = ( (it->y() - m_pixRect.y() )  ) * ratio + m_pixPos.y()/m_ratio;
            it->setX( x );
            it->setY( y );
        }
        painter.setPen(QPen(Qt::red, 2));
        painter.drawConvexPolygon(m_curvePoints);
        painter.setPen(QPen(Qt::blue, 5));
        for(QVector<QPoint>::iterator it= m_originPoints.begin();
            it != m_originPoints.end(); ++it){
            int x = ( (it->x() - m_pixRect.x() )  ) * ratio + m_pixPos.x()/m_ratio;
            int y = ( (it->y() - m_pixRect.y() )  ) * ratio + m_pixPos.y()/m_ratio;
            it->setX( x );
            it->setY( y );
        }
        for(QVector<QPoint>::iterator it= m_originPoints.begin();
            it != m_originPoints.end(); ++it){
            painter.drawPoint(*it);
        }
        m_action == MainWindow::None;
      //  *m_pix0 = *m_pix;
        m_originPoints.clear();
        m_curvePoints.clear();
    }
    return true;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    m_press  = true;
    m_prePos = event->pos();
    if(m_action == MainWindow::Mark){
        if(m_pixRect.contains(event->pos())){
            m_originPoints.push_back(event->pos());
            bezierCurve(m_originPoints, m_curvePoints);
        }
    }
    this->update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(m_action == MainWindow::Move){
        if(m_paintRect.contains(event->pos())){
            if(m_press){
                m_offset.setX(m_offset.x() + event->pos().x() - m_prePos.x() );
                m_offset.setY(m_offset.y() + event->pos().y() - m_prePos.y() );
                m_prePos = event->pos();
            }
        }
    }
    this->update();
    event->accept();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if(m_press)
        m_press=false;
    event->accept();
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if(m_action == MainWindow::Zoom)
    {
        if (event->delta()>0)
        {
            m_ratio+=0.1*m_ratio;
            if(m_ratio>4.5)
                m_ratio = 5.000;
        }
        else
        {
            m_ratio-=0.1*m_ratio;
            if(m_ratio<0.018)
                m_ratio = 0.01;
        }
        this->update();
    }
    event->accept();
}

void MainWindow::paintEvent(QPaintEvent *event)
{

    if( ! this->updatePix()) return;

    this->updatePix();

    QPainter painter(this);
    painter.drawRect(m_paintRect.x()-1,    m_paintRect.y()-1,
                     m_paintRect.width()+1,m_paintRect.height()+1);
    painter.drawTiledPixmap(m_pixRect, *m_pix, m_pixPos);

   if(m_action == MainWindow::Mark){
        painter.setPen(QPen(Qt::green, 2));
        painter.drawConvexPolygon(m_curvePoints);
        painter.setPen(QPen(Qt::blue, 5));
        for(QVector<QPoint>::iterator it= m_originPoints.begin();
            it != m_originPoints.end(); ++it){
            painter.drawPoint(*it);
        }
    }

    QString str;
    str.sprintf("%.0f%",m_ratio*100);
    m_ui->zoomRatio_lineEdit->setText(str) ;
}

void MainWindow::on_quickSearch_clicked(){
    this->setDefaultParameters();

    m_imageFileName = "timg.jpeg";
    m_pix0->load(m_imageFileName);
    *m_pix = *m_pix0;

    m_ui->markTab_date_label->setText("2018年5月29日");
    m_ui->markTab_id_label->setText("20180429");
    m_ui->markTab_name_label->setText("孙悟空");
    m_ui->markTab_age_label->setText("18");
    m_ui->markTab_sex_label->setText("男");

    this->update();
}

void MainWindow::on_saveImage_toolButton_clicked()
{
    m_pix->save("marked_"+m_imageFileName);
    this->update();
}

void MainWindow::on_zoom_toolButton_clicked()
{
    m_action = MainWindow::Zoom;
    this->update();
}

void MainWindow::on_move_toolButton_clicked()
{
    m_action = MainWindow::Move;
    this->update();
}

void MainWindow::on_anticlockwise_toolButton_clicked()
{
    -- m_rotate;
    this->update();
}

void MainWindow::on_clockwise_toolButton_clicked()
{
    ++ m_rotate;
    this->update();
}

void MainWindow::on_mark_toolButton_clicked()
{
    m_action = MainWindow::Mark;
    m_originPoints.clear();
    m_curvePoints.clear();
}


void MainWindow::on_marked_toolButton_clicked()
{
    m_action = MainWindow::Marked;
    this->update();
}

void MainWindow::on_reset_toolButton_clicked()
{
    setDefaultParameters();
    this->update();
}

void MainWindow::on_unmarked_toolButton_clicked()
{
    m_imageFileName = "timg.jpeg";
    m_pix0->load(m_imageFileName);
    *m_pix = *m_pix0;
    this->update();
}


/*


void MainWindow::generateOriginPoints(const QPointF &pos){
    int num = m_ui->makedPointsNum_spinBox->value();
    float rad = 5*num/2/3.1416;
    float dtheta = 2*3.1416/num;
    m_originPoints.clear();
    for(int i=0; i<=num; ++i){
        QPointF pt(i*std::cos(i*dtheta), i*std::sin(i*dtheta));
        m_originPoints.push_back(pt);
    }
}
*/

void MainWindow::on_caseManage_toolButton_clicked()
{
    CaseManageForm *w = new CaseManageForm;
    w->m_patientDatabase = m_patientDatabase;
    w->show();
}

void MainWindow::on_batchButton_clicked()
{
    ShowTableForm *w =new ShowTableForm;
    w->show();
}

Point p0 = Point(-1,-1);
bool select_flag = false;
Mat img,showImg;
Mat imgmask;

void onMouse(int event,int x,int y,int flags,void*param)
{
    if(event==CV_EVENT_LBUTTONDOWN)
    {
        p0.x = x;
        p0.y = y;
       select_flag = true;
    }
    else if(select_flag && event == CV_EVENT_MOUSEMOVE)
    {
        Point pt = Point(x,y);
        line(showImg,p0,pt,Scalar(255,0,0),2,8,0);
        line(imgmask,p0,pt,Scalar::all(0),2,8,0);
        p0 = pt;
        imshow("showImg",showImg);
    }
    else if(select_flag && event == CV_EVENT_LBUTTONUP)
    {
        select_flag = false;
        p0 = Point(-1,-1);
        //img.copyTo(showImg);

    }

    else if(event == CV_EVENT_LBUTTONDBLCLK)//右击显示抠出的图
    {
        Mat dst;//若希望将圈选的结果相加，定义在外头
        floodFill(imgmask,Point(x,y),Scalar(0));//point种子点所在的连通域被填充
        Mat ddt=255-imgmask;
        //imshow("floodFill",ddt);
        img.copyTo(dst,ddt);//mask中所有不为零的点被dst对应的值填充
        imshow("dst",dst);
        img.copyTo(showImg);
        imgmask.setTo(Scalar(255));//重新取值
    }

}



void MainWindow::on_cutimage_toolButton_clicked()
{
    QWidget *wn = new QWidget;
    wn->setWindowTitle("disp image");

    QString filename = QFileDialog::getOpenFileName(0, "Open File", "", "*.jpg *.png *.bmp *.jpeg", 0);
    if (filename.isNull()) {
        qDebug()<<"打开失败";
    }

    Mat image = imread(filename.toLatin1().data(), 1);
    imshow("showImg",image);
    img = image;
    img.copyTo(showImg);

    imgmask.create(img.size(),CV_8UC1);
    imgmask.setTo(Scalar(255));

    namedWindow("showImg");
    imshow("showImg",showImg);
    setMouseCallback("showImg",onMouse,0);

}

