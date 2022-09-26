#include "login.h"
#include "ui_login.h"
#include "QPropertyAnimation"
#include"check.h"
#include"connectsql.h"

//登录的cpp文件
login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
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

    //暗注释,请输入账号
    QLineEdit* lineEdit = ui->combox_user->lineEdit();
    lineEdit->setPlaceholderText(QStringLiteral("请输入账号..."));
    ui->line_pwd->setPlaceholderText(QStringLiteral("请输入密码..."));
    //关闭按钮失效
    //this->setWindowFlags(Qt::WindowMinMaxButtonsHint);
    //去掉最大化、最小化按钮，保留关闭按钮
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    //连接信号和槽函数的重点
    connect(this,SIGNAL(sendData(QString)),&mw,SLOT(GetData(QString)));

}

void login::SignIn()
{    
        //ODBC查询数据
        //数据库查找并且匹配 用户名和密码
        QString user=ui->combox_user->currentText();
        QString pwd=ui->line_pwd->text();
        connectsql csql;
        QSqlQuery query=QSqlQuery(csql.GetDatabase());
        if(user=="")
        {
            QMessageBox::warning(this,"提示","账号为空");
            return;
        }
        if(pwd=="")
        {
            QMessageBox::warning(this,"错误","密码为空");
            return;
        }
       QString sql = tr("select usernum,password from student where usernum='%1'and password='%2'").arg(user).arg(pwd);
       qDebug()<<query.exec(sql);    //执行mysql语句
        //没有找到相匹配的用户
        if(!query.first())
        {
           QMessageBox::warning(this,"提示","账号或密码输入错误，请重试！!");
        }
        else//账号密码正确，那么登录
        {
            query.exec(sql);
            this->hide();
            mw.show();

        }
}

login::~login()
{
    delete ui;
}


//点击登录时，执行的函数
void login::on_bt_login_clicked()
{
   this->SignIn();
   //传送数据到分页面，发送数据
    QString username=ui->combox_user->currentText();
    emit sendData(username);   
}

//点击enter，确认键时捕获，并且调用登录函数用来登录
void login::keyPressEvent(QKeyEvent*event)
{
    switch (event->key())
    {
            case Qt::Key_Return://Enter键
            case Qt::Key_Enter://数字键盘的Enter键
            {
                //也是进行登录
                this->on_bt_login_clicked();
            }
            break;
            default:
            break;
    }
}


//游客访问
void login::on_bt_login_2_clicked()
{
    this->hide();
    mw.show();    
}

//管理员
void login::on_bt_admin_clicked()
{
    Check p;
    p.exec();
}

