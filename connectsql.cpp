#include "connectsql.h"
#include<QMessageBox>
#include<QDebug>
#include<QSqlQuery>
connectsql::connectsql()
{
    //ODBC查询数据
    //连接数据库mysql
    if(QSqlDatabase::contains("qt_sql_default_connection"))
      db = QSqlDatabase::database("qt_sql_default_connection");
    else
      db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("myconnect"); //odbc中的设置的Data　source name
    db.setUserName("root");
    db.setPassword("tiger");//每个人的密码都不相同
    if(!db.open())//当数据库加载失败，那么弹窗提醒
    {
        qDebug()<<"error open database because"<<db.lastError().text();
        return;
    }
    //切换到demo数据库
    QSqlQuery result = db.exec("use demo");
    //sql后面输入想要执行的语句，查询账号和密码匹配
}

//返回成果数目
int connectsql::GetResNum()
{
    QString sql=QString("select count(*) from contestresult");
    QSqlQuery q;
    q.exec(sql);
    q.next();
    int num=q.value(0).toInt();
    //qDebug()<<"统计数目为："<<q.value(0).toInt();
    return num;
}

//返回数据库对象
 QSqlDatabase connectsql::GetDatabase()
{
   return db;
}
