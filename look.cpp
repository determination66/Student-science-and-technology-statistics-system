/*
 *学生通过名字查询自己提交的成果
 * 以tablewidget展示成果
 * 通过显示绿色 正在审核显示红色
 */
#include "look.h"
#include "ui_look.h"
#include "QTableWidget"
#include "QTableWidgetItem"
#include "QString"
#include "QStringList"
#include "QPropertyAnimation"
#include<QDebug>
#include"connectsql.h"
#include<qsqlquery.h>
#include<qmessagebox.h>

Look::Look(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Look)
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

    //居中显示
    ui->label->setAlignment(Qt::AlignHCenter);

    //进入动画
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    //animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}

Look::~Look()
{
    delete ui;
}

//排序
void Look::sort(int column)
{
    static bool f = true;
    ui->tableWidget->sortByColumn(column, f ? Qt::AscendingOrder : Qt::DescendingOrder);
    f = !f;
}

//关闭界面
void Look::on_pushButton_clicked()
{
    this->close();
}

//查询数据库文件
void Look::search_sql(QString d)
{
    connectsql csql;
    QSqlQuery query=QSqlQuery(csql.GetDatabase());
    //获取属性个数，数据库中进行查询
    QString sql=QString("select count(*) from information_schema.COLUMNS where TABLE_SCHEMA='demo' and table_name='%1' ").arg(d);
    query.exec(sql);
    query.first();
    int col=query.value(0).toInt();

    //获取查询个数
    sql=QString("select count(*) from `%1` where `issubmit`='y'").arg(d);
    query.exec(sql);
    query.first();
    int sum=query.value(0).toInt();
    qDebug()<<"查询人数为:"<<sum;
    if(sum==0)
    {
        //清空目前table
        ui->tableWidget->clear();
        ui->tableWidget->setColumnCount(0);
        ui->tableWidget->setRowCount(0);
        QMessageBox::information(this,"提示","当前没有相关信息！");
        return;
    }
    //qDebug()<<"col="<<col;
    //获取表格当中的属性
    sql=QString("select * from `%1` where `issubmit`='y'").arg(d);
    query.exec(sql);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
     while(query.next())
     {

        int row=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        QTableWidgetItem *item;
        for(int i=0;i<col-1;i++)
        {

          item=new QTableWidgetItem(query.value(i).toString());
          item->setTextAlignment(Qt::AlignCenter);
          QFont font;
          //font.setBold(true);//设置为粗体
          font.setPointSize(11);//字体大小
          item->setFont(font);
          ui->tableWidget->setItem(row,i,item);
        }

     }
}

//科研成果
void Look::on_pushButton_10_clicked()
{
    //清空目前table
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);

    QTableWidgetItem *item;
    //设置表头
    QStringList str;
    str<<"姓名"<<"类型"<<"成果名称"<<"学号";
    //设置tablewidget列数
    ui->tableWidget->setColumnCount(str.count());
    //将列名称输入 table
    for(int i=0;i<ui->tableWidget->columnCount();i++)
    {
        item=new QTableWidgetItem(str.at(i));
        QFont font;
        font.setBold(true);//设置为粗体
        font.setPointSize(11);//字体大小
        item->setFont(font);

        ui->tableWidget->setHorizontalHeaderItem(i,item);
    }
    search_sql("fruit_1");
}

//科研训练
void Look::on_pushButton_3_clicked()
{
    //清空目前table
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);

    QTableWidgetItem *item;
    //设置表头
    QStringList str;
    str<<"姓名"<<"成果名称"<<"时间"<<"备注"<<"账号";

    //设置tablewidget列数
    ui->tableWidget->setColumnCount(str.count());
    //将列名称输入 table
    for(int i=0;i<ui->tableWidget->columnCount();i++)
    {
        item=new QTableWidgetItem(str.at(i));
        QFont font;
        font.setBold(true);//设置为粗体
        font.setPointSize(11);//字体大小
        item->setFont(font);
        ui->tableWidget->setHorizontalHeaderItem(i,item);
    }
    search_sql("fruit_2");

}

//技能证书
void Look::on_pushButton_5_clicked()
{
    //清空目前table
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);

    QTableWidgetItem *item;
    //设置表头
    QStringList str;
    str<<"姓名"<<"证书名称"<<"成果时间"<<"成果编号"<<"账号";
    //设置tablewidget列数
    ui->tableWidget->setColumnCount(str.count());
    //将列名称输入 table
    for(int i=0;i<ui->tableWidget->columnCount();i++)
    {
        item=new QTableWidgetItem(str.at(i));
        QFont font;
        font.setBold(true);//设置为粗体
        font.setPointSize(11);//字体大小
        item->setFont(font);
        ui->tableWidget->setHorizontalHeaderItem(i,item);
    }
       search_sql("fruit_3");

}

//知识产权
void Look::on_pushButton_2_clicked()
{
    //清空目前table
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);

    QTableWidgetItem *item;
    //设置表头
    QStringList str;
   str<<"姓名"<<"类型"<<"产权名称"<<"账号";
    //设置tablewidget列数
    ui->tableWidget->setColumnCount(str.count());
    //将列名称输入 table
    for(int i=0;i<ui->tableWidget->columnCount();i++)
    {
        item=new QTableWidgetItem(str.at(i));
        QFont font;
        font.setBold(true);//设置为粗体
        font.setPointSize(11);//字体大小
        item->setFont(font);
        ui->tableWidget->setHorizontalHeaderItem(i,item);
    }
    search_sql("fruit_4");
}

//学科与科技竞赛
void Look::on_pushButton_4_clicked()
{
    //清空目前table
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);

    QTableWidgetItem *item;
    //设置表头
    QStringList str;
    str<<"姓名"<<"竞赛名称"<<"获奖名次"<<"获奖实践"<<"学号";
    //设置tablewidget列数
    ui->tableWidget->setColumnCount(str.count());
    //将列名称输入 table
    for(int i=0;i<ui->tableWidget->columnCount();i++)
    {
        item=new QTableWidgetItem(str.at(i));
        QFont font;
        font.setBold(true);//设置为粗体
        font.setPointSize(11);//字体大小
        item->setFont(font);
        ui->tableWidget->setHorizontalHeaderItem(i,item);
    }
       search_sql("fruit_5");
}

//创业实践和创新创业教育
void Look::on_pushButton_6_clicked()
{
    //清空目前table
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);

    QTableWidgetItem *item;
    //设置表头
    QStringList str;
    str<<"姓名"<<"实践名称"<<"参加时间"<<"学号";
    //设置tablewidget列数
    ui->tableWidget->setColumnCount(str.count());
    //qDebug()<<"创新时间"<<str.count();
    //将列名称输入 table
    for(int i=0;i<ui->tableWidget->columnCount();i++)
    {
        item=new QTableWidgetItem(str.at(i));
        QFont font;
        font.setBold(true);//设置为粗体
        font.setPointSize(11);//字体大小
        item->setFont(font);
        ui->tableWidget->setHorizontalHeaderItem(i,item);
    }
       search_sql("fruit_6");
}
