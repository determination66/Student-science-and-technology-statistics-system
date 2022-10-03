
/*
 * 导员审核成果
 * 通过保存到对应文件 未通过数据删除
 */
#include "to_examine.h"
#include "ui_to_examine.h"
#include "QTableWidget"
#include "QTableWidgetItem"
#include "QString"
#include "QStringList"
#include "QFile"
#include "QPropertyAnimation"
#include<qdebug.h>
#include<QMessageBox>
#include"connectsql.h"

To_examine::To_examine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::To_examine)
{

    ui->setupUi(this);
    sub=NULL;
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


    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中
    connect(ui->tableWidget->horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(sort(int)));

    //进入动画
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}

To_examine::~To_examine()
{
    delete sub;
    delete ui;
}

//关闭界面
void To_examine::on_pushButton_clicked()
{

    this->close();
}

//清空目前列表
void To_examine::qing()
{
    if(sub!=NULL)
    {
        delete sub;
        sub=NULL;
    }
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    ui->label_3->setText("");
}

//具体每行数据
void To_examine::open_sql(QString d)
{
    connectsql csql;
    QSqlQuery query=QSqlQuery(csql.GetDatabase());
    //获取属性个数，数据库中进行查询
    QString sql=QString("select count(*) from information_schema.COLUMNS where TABLE_SCHEMA='demo' and table_name='%1' ").arg(d);
    qDebug()<<query.exec(sql);
    query.first();
    int col=query.value(0).toInt();
    qDebug()<<"数据库的col="<<col;
    //获取查询个数
    sql=QString("select count(*) from `%1` where `issubmit`='un'").arg(d);
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
    sql=QString("select * from `%1` where `issubmit`='un'").arg(d);
    query.exec(sql);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableWidget->setStyleSheet("selection-background-color:pink");//设置选中颜色：粉色
     while(query.next())
     {
        int row=ui->tableWidget->rowCount();
        qDebug()<<"row="<<row;
        ui->tableWidget->insertRow(row);
        QTableWidgetItem *item;
        item=new QTableWidgetItem(query.value("id").toString());
        item->setTextAlignment(Qt::AlignCenter);
        QFont font;
        font.setPointSize(11);//字体大小
        item->setFont(font);
        ui->tableWidget->setItem(row,0,item);
//      输出信息，然后最后一列输入
        for(int i=0;i<col-2;i++)
        {
         item=new QTableWidgetItem(query.value(i).toString());
          item->setTextAlignment(Qt::AlignCenter);
          QFont font;
          //font.setBold(true);//设置为粗体
          font.setPointSize(11);//字体大小
          item->setFont(font);
          ui->tableWidget->setItem(row,i+1,item);
         }

        QPushButton *btnPass = new QPushButton;
        QPushButton *btnUnPass = new QPushButton;// 创建按钮
        btnPass->setText(QString("通过"));					// 设置按钮名称
        ui->tableWidget->setCellWidget(row,ui->tableWidget->columnCount()-2,btnPass);
        connect(btnPass, &QPushButton::clicked,[=]()
        {
            connectsql cl;
            QString valueid = ui->tableWidget->model()->index(row,0).data().toString();
           // qDebug() << "cell内容： " << valueid;
            QString sl=QString("update `%1` set `issubmit`='y' where `id`='%2'").arg(d).arg(valueid);
            QSqlQuery q=QSqlQuery(cl.GetDatabase());
            qDebug()<<q.exec(sl);
            btnPass->setDisabled(true);
            btnUnPass->hide();
            btnPass->setText("已通过！");
         });


        btnUnPass->setText(QString("不通过"));		// 设置按钮名称.
        ui->tableWidget->setCellWidget(row,ui->tableWidget->columnCount()-1,btnUnPass);
        connect(btnUnPass, &QPushButton::clicked,[=]()
        {
            connectsql cl;
            QString valueid = ui->tableWidget->model()->index(row,0).data().toString();
            //qDebug() << "cell内容： " << valueid;
            QString sl=QString("update `%1` set `issubmit`='n' where `id`='%2'").arg(d).arg(valueid);
            QSqlQuery q=QSqlQuery(cl.GetDatabase());
            if(!q.exec(sl)){
                QMessageBox::warning(this,"提示","操作失败！");
            }
            btnUnPass->setDisabled(true);
            btnPass->hide();
            btnUnPass->setText("未通过！");
         });
     }
}


//科研成果数据显示
void To_examine::on_pushButton_11_clicked()
{
    //清空目前table
    qing();

    QTableWidgetItem *item;
    //设置表头
    QStringList str;
    str<<"编号"<<"姓名"<<"类型"<<"成果名称"<<"学号"<<"通过"<<"不通过";
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
    QString d="fruit_1";
    open_sql(d);
}

//科研训练
void To_examine::on_pushButton_8_clicked()
{
    //清空目前table
    qing();
    QTableWidgetItem *item;
    //设置表头
    QStringList str;
    str<<"编号"<<"姓名"<<"成果类型"<<"时间"<<"备注"<<"学号"<<"通过"<<"不通过";
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
    QString d="fruit_3";
    open_sql(d);
}

//技能证书
void To_examine::on_pushButton_12_clicked()
{
    //清空目前table
    qing();
    QTableWidgetItem *item;
    //设置表头
    QStringList str;
    str<<"编号"<<"姓名"<<"证书名称"<<"获得时间"<<"编号(有则填)"<<"学号"<<"通过"<<"不通过";
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
    QString d="fruit_5";
    open_sql(d);
}

//知识产权
void To_examine::on_pushButton_7_clicked()
{
    //清空目前table
    qing();
    QTableWidgetItem *item;
    //设置表头
    QStringList str;
    str<<"编号"<<"姓名"<<"类型"<<"成果名称"<<"账号"<<"通过"<<"不通过";
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
    QString d="fruit_2";
    open_sql(d);
}

//学科与科技竞赛
void To_examine::on_pushButton_9_clicked()
{
    //清空目前table
    qing();
    QTableWidgetItem *item;
    //设置表头
    QStringList str;
    str<<"编号"<<"姓名"<<"竞赛名称"<<"获奖名次"<<"获奖时间"<<"学号"<<"通过"<<"不通过";
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
    QString d="fruit_4";
    open_sql(d);
}

//创业实践和创新创业教育
void To_examine::on_pushButton_13_clicked()
{
    //清空目前table
    qing();
    QTableWidgetItem *item;
    //设置表头
    QStringList str;
    str<<"编号"<<"姓名"<<"实践名称"<<"成果时间"<<"账号"<<"通过"<<"不通过";
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
    QString d="fruit_6";
    open_sql(d);
}

//关界面
void To_examine::on_pushButton_2_clicked()
{
    if(sub!=NULL)
    {
        delete sub;
        sub=NULL;
    }
    this->close();
}

//最后通过清除
void To_examine::on_pushButton_14_clicked()
{
    if(sub!=NULL)
    {
        delete sub;
        sub=NULL;
    }
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    ui->label_3->setText("");
}

