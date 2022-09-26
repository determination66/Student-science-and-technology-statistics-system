#include <QApplication>
#include<QFile>
#include"login.h"
#include"connectsql.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login lg;
    lg.show();

    return a.exec();
}
