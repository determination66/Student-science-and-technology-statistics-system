/*
 * 报错
 * 将用户提出的意见保存到文件
 */

#include "love.h"
#include "ui_love.h"
#include "QPropertyAnimation"
#include "QString"
#include"connectsql.h"

Love::Love(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Love)
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

Love::~Love()
{
    delete ui;
}

//提交错误学号报错 保存学号
void Love::on_pushButton_clicked()
{
    QString errinfo=ui->textEdit->toPlainText();
    connectsql csql;
    QSqlQuery query=QSqlQuery(csql.GetDatabase());
    QString sql=QString("insert into feedback (`text`) values ('%1')").arg(errinfo);
    bool ok=query.exec(sql);
    if(ok)
    {
        QMessageBox::information(this,"提示","谢谢反馈！");
        this->show();
    }
    else
    {
        QMessageBox::warning(this,"提示","反馈信息提交失败，请稍后提交!");
    }
}

//关闭界面
void Love::on_pushButton_2_clicked()
{
    this->close();
}
