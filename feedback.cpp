#include "feedback.h"
#include "ui_feedback.h"
#include"connectsql.h"
#include<QPropertyAnimation>

feedback::feedback(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::feedback)
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

feedback::~feedback()
{
    delete ui;
}

void feedback::on_pushButton_clicked()
{

    QStandardItemModel* model = new QStandardItemModel();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     ui->tableView->verticalHeader()->hide();
    QStringList labels = QString("反馈信息,编号").simplified().split(",");
    model->setHorizontalHeaderLabels(labels);
    ui->tableView->setModel(model);

    connectsql csql;
    QSqlQuery query=QSqlQuery(csql.GetDatabase());
    QString sql=QString("select * from feedback");
    qDebug()<<query.exec(sql);
    int num=0;
     while(query.next())
     {
        QStandardItem* item = 0;
        for(int i = 0;i<2; i++){
         // 给item赋值
         item = new QStandardItem(QString(query.value(i).toString()));
         // 表格内元素设置字体居中
          item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
         // 设置表格单元格内容
         model->setItem(num,i,item);

     }
         num++;
     }
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {"
                               "color: black;padding-left: 4px;border: 1px solid #6c6c6c;}");

}

