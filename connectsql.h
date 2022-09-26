#ifndef CONNECTSQL_H
#define CONNECTSQL_H
//连接数据库的一个类，方便操作,相关的数据库
#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>
#include<QString>
#include<QDebug>
#include<QMessageBox>
#include<QSqlTableModel>

class connectsql
{
public:
    connectsql();
    QSqlDatabase GetDatabase();//获取当前数据库对象
    int GetResNum();
private:
    //数据库对象，在操作时进行操作关联此对象
     QSqlDatabase db;
};

#endif // CONNECTSQL_H
