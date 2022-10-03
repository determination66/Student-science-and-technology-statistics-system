#include "manage.h"
#include "ui_manage.h"
#include"connectsql.h"

Manage::Manage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Manage)
{
    //ui->setupUi(this);
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
}

Manage::~Manage()
{
    delete ui;
}

void Manage::on_pushButton_clicked()
{
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
        qDebug()<<"row="<<row;
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
          //font.setBold(true);//设置为粗体
          font.setPointSize(11);//字体大小
          item->setFont(font);
          ui->tableWidget->setItem(row,i+1,item);
         }
     }
}

