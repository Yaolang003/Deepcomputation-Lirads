#include "login.h"
#include "mainwindow.h"
#include <QApplication>

#include "patientdatabase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // MainWindow w;
   // w.show();
    Login login;
    login.show();
/*
    PatientInfo pat;
    pat.id = "123456";
    pat.name = "孙悟空";
    pat.sex = "男";
    pat.identity = "123456789012345678";
    pat.age = "500";
    pat.birth = "20180808";
    pat.phone = "12345678901";
    pat.address = "湖南省湘潭市雨湖区水帘洞";
    pat.imagePath = "/liards/images/timg.jpeg";
    pat.report = "正常";

    PatientDatabase db;
    db.open();
    db.createTable();
    db.insert(pat);
    pat.id = "123457";
    db.insert(pat);
    pat.id = "123458";
    db.insert(pat);
    pat.id = "123459";
    db.insert(pat);
    db.show();
*/
 /*   MainWindow z;

    QSqlDatabase db;
    z.show();

    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("liradsdatabases");
    db.setUserName("root");
    db.setPassword("deepcomp");
    db.open();
*/
    return a.exec();
}
