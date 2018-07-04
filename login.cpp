#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"

#include <iostream>
#include <QMessageBox>
#include <QString>
#include <QPainter>
#include <QtSql/QSqlQuery>
#include <QTime>
#include <QTimer>
#include <QtEvents>
#include <QDesktopWidget>

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);    

    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    int g_nActScreenW = screenRect.width();
    int g_nActScreenH = screenRect.height();
    this->setWindowTitle("登录窗口");
    this->setFixedSize(1080, 600);
    this->move(g_nActScreenW/2-1080/2, g_nActScreenH/2-600/2);

    ui->lineEdit_username->setPlaceholderText("username");
    ui->lineEdit_password->setPlaceholderText("password");
    ui->lineEdit_captcha->setPlaceholderText("captcha");
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);



 //   connect(ui->pushButton_cancel, SIGNAL(clicked()), this, SLOT(on_pushButton_cancel_clicked() ));
//    connect(ui->pushButton_login ,  SIGNAL(clicked()), this, SLOT(on_pushButton_login_clicked() ));
    //connect(&m_timer, SIGNAL(timeout()), this, SLOT(Timer_Timeout()));
//    connect(ui->pushButton_login ,  SIGNAL(clicked()), this, SLOT(on_pushButton_login_clicked() ));

    qsrand(QTime::currentTime().second() * 1000 + QTime::currentTime().msec());

    m_captcha = getCaptcha();
    m_color   = getColor();

    m_timer.start(200);

}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_login_clicked()
{
    qDebug("LoginBtn_Clicked start");
/*
    bool success=false;//标识是否成功打开数据库
    if(!db.open()){//打开不成功
        QMessageBox::about(this,"Message","connect error!");
        return;
    }
*/
    m_user = ui->lineEdit_username->text().trimmed();//trimmed():Delete space
    m_pwd  = ui->lineEdit_password->text().trimmed();//PwdLineEdit.text();

    QString captcha = ui->lineEdit_captcha->text().replace(" ", "");

    std::cout << captcha.toStdString() << std::endl;
    std::cout << m_captcha.toStdString() << std::endl;

    MainWindow *w=new MainWindow;
    w->show();
    this->close();
  /*  if(captcha.toLower() == m_captcha.toLower())
    {
        if(m_user.isEmpty())
        {
            QMessageBox::information(this, "Info", "User ID can not be empty");
            m_captcha = getCaptcha();
        }
        else if(m_pwd.isEmpty())
        {
            QMessageBox::information(this, "Info", "Password can not be empty");
            m_captcha = getCaptcha();
        }
        else
        {
            Home *w=new Home;
            w->show();
            this->close();

            //done(Accepted);
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Captcha is not macthed");

        m_captcha = getCaptcha();

        //        CaptEdit.selectAll();
    }
    qDebug("LoginBtn_Clicked end");
    emit Timer_Timeout();
    //this->paintEvent(NULL);

 //    hos_main *w=new hos_main;
//    w->show();
   // this->close();
    /*
    bool success=false;//标识是否成功打开数据库
    if(!db.open()){//打开不成功
        QMessageBox::about(this,"Message","connect error!");
        return;
    }
    else{
        QString user=ui->usr_name->text().trimmed();//获取用户名
        QString pwd=ui->usr_pwd->text().trimmed();//用户密码
        if(""==user)//若输入的用户名空
            QMessageBox::about(this,"Message","Please input user name");
        else if(""==pwd)//若输入的密码为空
            QMessageBox::about(this,"Msssage","Please input password");
        else{
           QSqlQuery query;
           if(query.exec("select*from TMS")){//从保存用户名和密码的表TMS中选择元组
               while(query.next()){
                   if(user==query.value(0).toString() && pwd==query.value(1).toString()){
                       success=true;//注value从0开始。
                       db.close();
                       break;
                   }
               }
               if(success){//用户名和密码匹配成功
                   hos_main *w=new hos_main;
                   w->show();
                   this->close();
               }
               else
                   QMessageBox::about(this,"Message","Logining error");
           }
        }
    }
    */
}

void Login::on_pushButton_cancel_clicked()
{
    this->close();
}


void Login::paintEvent(QPaintEvent *evt)
{
    int pos_x = 180+150+150+410, pos_y = 100+122+120+27;
    int w = 100, h = 30, wc = w/4;
    QPainter painter(this);

    painter.fillRect(pos_x, pos_y, w, h, Qt::white);

    painter.setFont(QFont("Comic Sans MS"));

    for(int i = 0; i < pos_y; i++)
    {
        painter.setPen(m_color[i % 4]);
        painter.drawPoint(pos_x + (qrand() % w), pos_y + (qrand() % h));
    }

    for(int i = 0; i < 4; i++)
    {
        painter.setPen(m_color[i]);
        painter.drawText(pos_x + wc * i, pos_y, wc, h, Qt::AlignCenter, QString(m_captcha[i]));
    }
}

void Login::mousePressEvent(QMouseEvent* event){
    int x = event->globalX();
    int y = event->globalY();
 //   int disX = x - originX;
 //   int disY = y - originY;
 //   QPoint pos = this->pos();
 //   pos.setX();
 //   pos.setY();
}

QString Login::getCaptcha()
{
    QString ret = "";

    for(int i = 0; i < 4; i++)
    {
        int c = (qrand() % 2) ? 'a' : 'A';

        ret += static_cast<QChar>(c + qrand() % 26);
    }

    return ret;
}

Qt::GlobalColor* Login::getColor()
{
    static Qt::GlobalColor colors[4];

    for(int i = 0; i < 4; i++)
    {
        colors[i] = static_cast<Qt::GlobalColor>((qrand() % 4) + 4);
    }

    return colors;
}


void Login::Timer_Timeout()
{
    m_color = getColor();
    m_captcha = getCaptcha();

    update();
}

QString Login::GetUser()
{
    return m_user;
}

QString Login::GetPwd()
{
    return m_pwd;
}
