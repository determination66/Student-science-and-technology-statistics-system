#include "managestu.h"
#include "ui_managestu.h"
#include"connectsql.h"

ManageStu::ManageStu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageStu)
{
    ui->setupUi(this);
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
}

ManageStu::~ManageStu()
{
    delete ui;
}


void ManageStu::on_pushButton_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    QTableWidgetItem *item;
    //设置表头
    QStringList str;
    str<<"姓名"<<"学号"<<"电话"<<"密码";
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
    connectsql csql;
    QSqlQuery query=QSqlQuery(csql.GetDatabase());
    QString sql=QString("select * from student");
    query.exec(sql);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableWidget->setStyleSheet("selection-background-color:pink");//设置选中颜色：粉色
     while(query.next())
     {
        int row=ui->tableWidget->rowCount();
        //qDebug()<<"row="<<row;
        ui->tableWidget->insertRow(row);
        QTableWidgetItem *item;
        item=new QTableWidgetItem(query.value("id").toString());
        item->setTextAlignment(Qt::AlignCenter);
        QFont font;
        font.setPointSize(11);//字体大小
        item->setFont(font);
        ui->tableWidget->setItem(row,0,item);
        for(int i=0;i<4;i++)
        {
         item=new QTableWidgetItem(query.value(i).toString());
          item->setTextAlignment(Qt::AlignCenter);
          QFont font;
          font.setPointSize(11);//字体大小
          item->setFont(font);
          ui->tableWidget->setItem(row,i,item);
         }
     }
}

