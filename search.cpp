/*
 * 学生查找自己的成果
 * 通过颜色辨别是否审核
 */

#include "search.h"
#include "ui_search.h"
#include <QListWidget>
#include <QString>
#include <QListWidgetItem>
#include <QFile>
#include<QMessageBox>
#include "QPropertyAnimation"
#include"connectsql.h"

Search::Search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Search)
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

Search::~Search()
{
    delete ui;
}

void Search::sear(QString name)
{
    QListWidgetItem *item;
    connectsql csql;
    QSqlQuery query=QSqlQuery(csql.GetDatabase());
    QString d[6]={"fruit_1","fruit_2","fruit_3","fruit_4","fruit_5","fruit_6"};
    QString tit[6]={
        "科研成果\t\t姓名\t类型\t成果名称\t账号",
        "知识产权\t\t姓名\t类型\t成果名称\t账号",
        "科研训练\t\t姓名\t成果名称\t时间\t备注\t账号",
        "学科与科技竞赛\t\t姓名\t竞赛名称\t获奖名次\t获奖时间\t账号",
        "技能证书\t姓名\t证书名称\t成果时间\t成果编号\t账号",
        "创业实践和创新教育\t\t姓名\t实践名称\t成果时间\t账号"
    };
    int sum=0;
    for(int i=0;i<6;i++)
    {
        item=new QListWidgetItem;
        QFont font;
        font.setBold(true);//设置为粗体
        font.setPointSize(14);//字体大小
        item->setFont(font);
        //未查询到当前信息
        item->setText(tit[i]);
        //将对应类别和信息显示到list
        item->setSizeHint(QSize(100, 100));
        ui->listWidget->addItem(item);//添加一个list中的对象
        QString sql=QString("select count(*) from information_schema.COLUMNS where TABLE_SCHEMA='demo' and table_name='%1'").arg(d[i]);
        qDebug()<<query.exec(sql);
        query.first();
        int col=query.value(0).toInt();
        //qDebug()<<"col="<<col;
        sql=QString("select * from `%1` where `name` like'%2'").arg(d[i]).arg(name);
        query.exec(sql);
        int k=0;
        while(query.next())
        {
            k++;
            QString line="";
           for(int j=0;j<col-1;j++)
           {
                line=line+"\t"+query.value(j).toString()+"\t";
           }
           //qDebug()<<line;
           item=new QListWidgetItem;
           QFont font;
           //font.setBold(true);//设置为粗体
           font.setPointSize(11);//字体大小
           item->setFont(font);
           item->setText(line);
           //将对应类别和信息显示到list
           if(query.value("issubmit").toString()=="n")
           item->setBackground(QColor("pink"));//未通过显示红色背景
           else item->setBackground(QColor("lightgreen"));//通过显示绿色背景
           item->setSizeHint(QSize(100, 100));
           ui->listWidget->addItem(item);//添加一个list中的对象
        }
        sum+=k;
    }
    qDebug()<<"总计的个数为："<<sum;
}

void Search::on_pushButton_clicked()
{
    ui->listWidget->clear();
    QString name=ui->lineEdit->text();
    sear(name);
    if(ui->listWidget->count()==0)
    {
        QListWidgetItem *item=new QListWidgetItem;
        QFont font;
        font.setBold(true);//设置为粗体
        font.setPointSize(15);//字体大小
        item->setFont(font);
        item->setTextAlignment(Qt::AlignHCenter);
        item->setText("未申报课外科技活动成果");
        ui->listWidget->addItem(item);
    }
}

void Search::on_pushButton_2_clicked()
{
    this->close();
}
