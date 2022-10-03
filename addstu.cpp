#include "addstu.h"
#include "ui_addstu.h"
#include <QListWidget>
#include <QString>
#include <QListWidgetItem>
#include<QMessageBox>
#include "QPropertyAnimation"
#include"connectsql.h"

addstu::addstu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addstu)
{
    ui->setupUi(this);
    //设置界面标题
    setWindowTitle(QString("大学生课外科技活动成果管理系统"));
    //设置界面图标
    setWindowIcon(QIcon("D:\\qtproject\\untitled1\\wust.png"));

    //设置界面背景
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    QPixmap pixmap("D:\\qtproject\\untitled1\\background.png");
    QPalette palette=this->palette();
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);
    QPalette palette2=this->palette();
    palette2.setBrush(QPalette::WindowText,Qt::white);
    this->setPalette(palette2);

    //进入动画
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}

addstu::~addstu()
{
    delete ui;
}

//清空
void addstu::on_pushButton_5_clicked()
{
    //姓名，学号，密码1，密码2，电话
    ui->LineEdit->clear();
    ui->LineEdit_2->clear();
    ui->LineEdit_3->clear();
    ui->LineEdit_4->clear();
    ui->LineEdit_5->clear();
}

//注册信息
void addstu::on_pushButton_4_clicked()
{
    QString name=ui->LineEdit->text();
    QString usernum=ui->LineEdit_2->text();
    QString pwd=ui->LineEdit_3->text();
    QString pwd2=ui->LineEdit_4->text();
    QString phone=ui->LineEdit_5->text();
    if(name==""||usernum==""||pwd==""||pwd2==""||phone=="")
    {
        QMessageBox::warning(this,"提示","请输入完整信息！");
        return;
    }

    connectsql csql;
    QSqlQuery query=QSqlQuery(csql.GetDatabase());
    QString sql=tr("select * from student where `usernum`='%1'").arg(usernum);
    query.exec(sql);
    //找到相同账号的用户
    if(query.first())
    {
       QMessageBox::information(this,"提示","注册失败，请确认学号是否正确！");
       return;
    }
    else
    {
        sql=QString("insert into `student` values('%1','%2','%3','%4')").arg(name)
                .arg(usernum).arg(phone).arg(pwd);
        if(!query.exec(sql))
        {

            QMessageBox::warning(this,"提示","注册失败，数据库连接失败!");
            return;
        }
        else
        {
            if(pwd!=pwd2)
            {
                QMessageBox::warning(this,"提示","请确保两次密码输入相同！");
                return;
            }
             QMessageBox::information(this,"提示","注册成功！");
        }
    }
    //qDebug()<<name<<" "<<usernum<<" "
    //<<pwd<<" "<<pwd2<<" "<<phone;
}

//退出
void addstu::on_pushButton_6_clicked()
{
    this->hide();
}

