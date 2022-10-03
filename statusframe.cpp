/*
 * 导员功能界面
 * 查看目前通过成果
 * 审核成果
 * 排序
 * 导入数据
 */

#include "statusframe.h"
#include "ui_statusframe.h"
#include <QString>
#include <QFile>
#include "look.h"
#include "to_examine.h"
#include "QPropertyAnimation"
#include"feedback.h"



Statusframe::Statusframe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Statusframe)
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

    //设置文字竖排显示
    ui->label_2->setText("管\n理\n员\n");

    //进入动画
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}

Statusframe::~Statusframe()
{
    delete ui;
}


//导员查看通过数据
void Statusframe::on_pushButton_8_clicked()
{
    Look p;
    p.exec();
}


//导员审核数据
void Statusframe::on_pushButton_7_clicked()
{
    To_examine p;
    p.exec();
}

//反馈信息查询
void Statusframe::on_pushButton_6_clicked()
{
    feedback fb;
    fb.exec();
}

//查看学生信息
void Statusframe::on_pushButton_9_clicked()
{
    ManageStu ms;
    ms.exec();

}

