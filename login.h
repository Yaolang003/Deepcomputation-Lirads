#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QTimer>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::Login *ui;


protected:
    void mousePressEvent(QMouseEvent* event);

    QString getCaptcha();
    void paintEvent(QPaintEvent *evt);
    Qt::GlobalColor* getColor();

    void Timer_Timeout();
    QString GetUser();
    QString GetPwd();


private:

    QString m_user;
    QString m_pwd;
    QString m_captcha;
    Qt::GlobalColor* m_color;
    QTimer m_timer;
};

#endif // LOGIN_H
