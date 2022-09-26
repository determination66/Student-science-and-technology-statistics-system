/*
 * 学生个人提交成果界面
 * 以listwidget表形式收集信息 保存到到未审核文件中
 * 导员打开这些文件进行审核
 * 一次只可提交一个成果
 */
#include "dialog.h"
#include "ui_dialog.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QFile>
#include <QString>
#include <QRadioButton>
#include "QPropertyAnimation"
#include"connectsql.h"
#include"submit.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
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

Dialog::~Dialog()
{
    delete ui;
}

//编辑对应条目
void Dialog::textchange(QListWidgetItem* item)
{

    //QString str=item->text();
    item->setFlags(item->flags()|Qt::ItemIsEditable);
    ui->listWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
}

//保存到数据库中
void Dialog::save(QString d,QString sstr,
                  QListWidgetItem *item,QString name,
                  QString student_num,QString student_lel)
{
    QString str=item->text();
    qDebug()<<"电话"<<student_lel;
    connectsql csql;
    QSqlQuery query=QSqlQuery(csql.GetDatabase());
    //插入信息到指定表当中  类型 成果名 姓名 学号
    QString sql=QString("insert into `%1` (`type`,`fruitname`,`name`,`usernum`) values ('%2','%3','%4','%5')")
            .arg(d).arg(sstr).arg(str).arg(name).arg(student_num);
    qDebug()<<d<<sstr<<str<<name<<student_num;
    bool ok=query.exec(sql);
    if(ok)
    {
        QMessageBox::information(this,"提示","上报成果成功！");
        //qDebug()<<"上报成果成功！";
    }
    else
    {
        QMessageBox::warning(this,"提示","上报成果失败！");
        //qDebug()<<"上报成果失败！";
    }
}

//提交数据到相关数据库中
void Dialog::on_pushButton_clicked()
{
    QString name=ui->lineEdit->text();
    QString student_num=ui->lineEdit_2->text();
    QString student_lel=ui->lineEdit_3->text();
    //将改变的数据加到数据库中
    //科研成果
    if (ui->radioButton->isChecked())
    {
        int c=0;
        for(int i=0;i<ui->listWidget->count();i++)
        {
            QListWidgetItem* item=ui->listWidget->item(i);
            QString str=item->text();
            QString d="fruit_1";
            if(i==0&&str!="获得的国家级、省级科技成果奖")
            {
                c++;
            }else if(i==1&&str!="在公开出版的学术期刊上发表的论文以及被省级以上学术会议收录的论文")
            {
                c++;


                save(d,"论文",item,name,student_num,student_lel);
            }
            else if(i==2&&str!="在报刊、杂志上发表作品")
            {
                c++;
                save(d,"在报刊、杂志上发表作品",item,name,student_num,student_lel);
            }
            else if(i==3&&str!="其它")
            {
                c++;
                save(d,"其它",item,name,student_num,student_lel);
            }
        }
        if(c==0)
        {
            Submit p;
            p.exec();
        }
    }
    //知识产权
    else if(ui->radioButton_2->isChecked())
    {
        int c=0;
        for(int i=0;i<ui->listWidget->count();i++)
        {
            QListWidgetItem* item=ui->listWidget->item(i);
            QString str=item->text();
            QString d="fruit_2";
            if(i==0&&str!="获得专利")
            {
                c++;
                save(d,"获得专利",item,name,student_num,student_lel);
            }else if(i==1&&str!="软件著作权")
            {
                c++;
                save(d,"软件著作权",item,name,student_num,student_lel);
            }
            else if(i==2&&str!="其他")
            {
                c++;
                save(d,"其它",item,name,student_num,student_lel);
            }
        }
        if(c==0)
        {
            Submit p;
            p.exec();
        }
    }
    //科研训练
    else if(ui->radioButton_3->isChecked())
    {
        QString strict_name,strict_time,add;
        int flag=1;//标志是否合法
        for(int i=0;i<ui->listWidget->count();i++)
        {
            QListWidgetItem *item=ui->listWidget->item(i);
            QString s=item->text();
            if(i==0)
            {
                if(s!="参加训练名称")
                    strict_name=s;
                else
                {
                    flag=0;
                    Submit p;
                    p.exec();
                    break;
                }
            }
            if(i==1)
            {
                if(s!="时间")
                    strict_time=s;
                else
                {
                    flag=0;
                    Submit p;
                    p.exec();
                    break;
                }
            }
            if(i==2)
            {
                if(s=="备注")
                add="无备注";
                else add=s;
            }
        }
        if(flag)
        {
            connectsql csql;
            QSqlQuery query=QSqlQuery(csql.GetDatabase());

            QString sql=QString("insert into `fruit_3` (`fruitname`,`name`,`usernum`,`fruittime`,`tip`) values ('%1','%2','%3','%4','%5')")
                   .arg(strict_name).arg(name).arg(student_num).arg(strict_time).arg(add);
            bool ok=query.exec(sql);
            if(ok)
            {
                QMessageBox::information(this,"提示","上报成果成功！");
                //qDebug()<<"上报成果成功！";
            }
            else
            {
                QMessageBox::warning(this,"提示","上报成果失败！");
                //qDebug()<<"上报成果失败！";
            }
        }
    }
    //学科与科技竞赛
    else if(ui->radioButton_4->isChecked())
    {
        //"竞赛名称","级别","获奖名次","时间","学分值"
        QString name=ui->lineEdit->text();
        QString student_num=ui->lineEdit_2->text();
        QString con_name,con_order,con_time;
        int flag=1;//标志是否合法
        for(int i=0;i<ui->listWidget->count();i++)
        {
            QListWidgetItem *item=ui->listWidget->item(i);
            QString s=item->text();
            if(i==0)
            {
                if(s!="竞赛名称")
                    con_name=s;
                else
                {
                    flag=0;
                    Submit p;
                    p.exec();
                    break;
                }
            }
            if(i==1)
            {
                if(s!="获奖名次")
                    con_order=s;
                else
                {
                    flag=0;
                    Submit p;
                    p.exec();
                    break;
                }
            }
            if(i==2)
            {
                if(s!="时间")
                    con_time=s;
                else
                {
                    flag=0;
                    Submit p;
                    p.exec();
                    break;
                }
            }
        }
        if(flag)
        {
            connectsql csql;
            QSqlQuery query=QSqlQuery(csql.GetDatabase());

            QString sql=QString("insert into `fruit_4` (`fruitname`,`name`,`usernum`,`fruittime`,`level`)"
                     " values ('%1','%2','%3','%4','%5')")
                    .arg(con_name).arg(name).arg(student_num).arg(con_time).arg(con_order);
            bool ok=query.exec(sql);
            if(ok)
            {
                QMessageBox::information(this,"提示","上报成果成功！");
            }
            else
            {
                QMessageBox::warning(this,"提示","上报成果失败！");
            }
        }
    }
    //技能证书
    else if(ui->radioButton_5->isChecked())
    {
        //"证书名称","获得时间","编号(有则填)"
        QString name=ui->lineEdit->text();
        QString student_num=ui->lineEdit_2->text();
        QString student_lel=ui->lineEdit_3->text();
        QString cred_name,cred_time,cred_num;
        int flag=1;//标志是否合法
        for(int i=0;i<ui->listWidget->count();i++)
        {
            QListWidgetItem *item=ui->listWidget->item(i);
            QString s=item->text();
            if(i==0)
            {
                if(s!="证书名称")cred_name=s;
                else
                {
                    flag=0;
                    Submit p;
                    p.exec();
                    break;
                }

            }
            if(i==1)
            {
                if(s!="获得时间")cred_time=s;
                else
                {
                    flag=0;
                    Submit p;
                    p.exec();
                    break;

                }
            }
            if(i==2)
            {
                if(s=="编号(有则填)")cred_num="无编号";
                else cred_num=s;
            }
        }
        if(flag)
        {
            connectsql csql;
            QSqlQuery query=QSqlQuery(csql.GetDatabase());

            QString sql=QString("insert into `fruit_5` (`fruitname`,`name`,`usernum`,`fruittime`,`fruitnum`)"
                     " values ('%1','%2','%3','%4','%5')")
                    .arg(cred_name).arg(name).arg(student_num).arg(cred_time).arg(cred_num);
            bool ok=query.exec(sql);
            if(ok)
            {
                QMessageBox::information(this,"提示","上报成果成功！");
                this->show();
            }
            else
            {
                QMessageBox::warning(this,"提示","上报成果失败！");
            }
        }
    }
    //创业实践和创新创业教育
    else if(ui->radioButton_6->isChecked())
    {
        //"参加创业实践或创新创业教育名称","参加时间","是否有证书"
        QString name=ui->lineEdit->text();
        QString student_num=ui->lineEdit_2->text();
        QString student_lel=ui->lineEdit_3->text();
        QString ed_name,ed_time;
        int flag=1;//标志是否合法
        for(int i=0;i<ui->listWidget->count();i++)
        {
            QListWidgetItem *item=ui->listWidget->item(i);
            QString s=item->text();
            if(i==0)
            {
                if(s!="参加创业实践或创新创业教育名称")ed_name=s;
                else
                {
                    flag=0;
                    Submit p;
                    p.exec();
                    break;
                }
            }
            if(i==1)
            {
                if(s!="参加时间")ed_time=s;
                else
                {
                    flag=0;
                    Submit p;
                    p.exec();
                    break;
                }
            }
        }
        if(flag)
        {
            connectsql csql;
            QSqlQuery query=QSqlQuery(csql.GetDatabase());

            QString sql=QString("insert into `fruit_6` (`fruitname`,`name`,`usernum`,`fruittime`)"
                     " values ('%1','%2','%3','%4')")
                    .arg(ed_name).arg(name).arg(student_num).arg(ed_time);
            bool ok=query.exec(sql);
            if(ok)
            {
                QMessageBox::information(this,"提示","上报成果成功！");
                this->show();
            }
            else
            {
                QMessageBox::warning(this,"提示","上报成果失败！");
            }
        }

        //关闭界面
        this->close();
        }
}

//展示科研成果fruit_1
void Dialog::on_radioButton_clicked()
{
    ui->listWidget->clear();

      //添加标题 科研成果分类
      QListWidgetItem* headerItem;
      QString a[4]={"获得的国家级、省级科技成果奖","在公开出版的学术期刊上发表的论文以及被省级以上学术会议收录的论文","在报刊、杂志上发表作品","其它"};
      for(int i=0;i<4;i++)
      {
          headerItem=new QListWidgetItem;
          headerItem->setSizeHint(QSize(200, 60));
          headerItem->setText(a[i]);
          ui->listWidget->addItem(headerItem);
      }

      headerItem=new QListWidgetItem;
      headerItem->setText("若是论文请依次填写论文名称、作者、排序、刊物名称、发表年月、收录情况、学分值等等");
      headerItem->setSizeHint(QSize(200, 60));
      ui->listWidget->addItem(headerItem);

      headerItem=new QListWidgetItem;
      headerItem->setText("最好写完整信息");
      headerItem->setSizeHint(QSize(200, 60));
      ui->listWidget->addItem(headerItem);

      if(ui->listWidget->currentRow()<4)
          connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(textchange(QListWidgetItem*)));

}

//知识产权fruit_2
void Dialog::on_radioButton_2_clicked()
{
    ui->listWidget->clear();

    //添加标题
    QListWidgetItem* headerItem;
    QString a[4]={"获得专利","软件著作权","其他"};
    for(int i=0;i<3;i++)
    {
        headerItem=new QListWidgetItem;
        headerItem->setSizeHint(QSize(200, 60));
        headerItem->setText(a[i]);
        ui->listWidget->addItem(headerItem);
    }

    connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(textchange(QListWidgetItem*)));

}

//科研训练
void Dialog::on_radioButton_3_clicked()
{
    ui->listWidget->clear();

    //添加标题
    QListWidgetItem* headerItem;
    QString a("参加训练名称"),b("时间"),c("备注");
    headerItem=new QListWidgetItem;
    headerItem->setText(a);
    headerItem->setSizeHint(QSize(200, 60));
    ui->listWidget->addItem(headerItem);

    headerItem=new QListWidgetItem;
    headerItem->setSizeHint(QSize(200, 60));
    headerItem->setText(b);
    ui->listWidget->addItem(headerItem);

    headerItem=new QListWidgetItem;
    headerItem->setText(c);
    headerItem->setSizeHint(QSize(200, 60));
    ui->listWidget->addItem(headerItem);

    connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(textchange(QListWidgetItem*)));

}

//学科与科技竞赛
void Dialog::on_radioButton_4_clicked()
{
    ui->listWidget->clear();

    //添加标题
    QListWidgetItem* headerItem;
    QString a[5]={"竞赛名称","获奖名次","时间"};
    for(int i=0;i<5;i++)
    {
        headerItem=new QListWidgetItem;
        headerItem->setSizeHint(QSize(200, 60));
        headerItem->setText(a[i]);
        ui->listWidget->addItem(headerItem);
    }
    connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(textchange(QListWidgetItem*)));
}

//技能证书
void Dialog::on_radioButton_5_clicked()
{
    ui->listWidget->clear();

    //添加标题
    QListWidgetItem* headerItem;
    QString a[3]={"证书名称","获得时间","编号(有则填)"};
    for(int i=0;i<3;i++)
    {
        headerItem=new QListWidgetItem;
        headerItem->setText(a[i]);
        headerItem->setSizeHint(QSize(200, 60));
        ui->listWidget->addItem(headerItem);
    }


    connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(textchange(QListWidgetItem*)));
}

//创业实践和创新创业教育
void Dialog::on_radioButton_6_clicked()
{
    ui->listWidget->clear();

    //添加标题
    QListWidgetItem* headerItem;
    QString a[3]={"参加创业实践或创新创业教育名称","参加时间"};
    for(int i=0;i<3;i++)
    {
        headerItem=new QListWidgetItem;
        headerItem->setText(a[i]);
        headerItem->setSizeHint(QSize(200, 60));
        ui->listWidget->addItem(headerItem);
    }
    connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(textchange(QListWidgetItem*)));
}

//退出界面
void Dialog::on_pushButton_2_clicked()
{
    this->close();
}


