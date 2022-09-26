#ifndef LOGIN_H
#define LOGIN_H

//这个为登录头文件
#include <QWidget>
#include "mainwindow.h"
#include <QAbstractButton>
#include <QKeyEvent>
#include<QMessageBox>


namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
    //enter事件函数
    virtual void keyPressEvent(QKeyEvent*event);
    //进行比对登录
    void SignIn();
    //展示下拉框账号密码
    void RemPwd();

private slots:
    //点击登录按钮
    void on_bt_login_clicked();
    //游客访问
    void on_bt_login_2_clicked();
    //管理员登录
    void on_bt_admin_clicked();

signals:
    //传递账号给分页面
    void sendData(QString);
private:
    Ui::login *ui;

    //分页面--对象--有账号
    MainWindow mw;

};

#endif //LOGIN_H
