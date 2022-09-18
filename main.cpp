#include "mainwindow.h"
#include <QApplication>
#include<QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        //记得widget个form可以删除
//    QFile f("D:\\qtproject\\build-untitled1-Desktop_Qt_5_15_2_MinGW_64_bit-Debug\\infotxt\\未审核内容\\未审核技能证书.txt");
//    QFile f("D:\\qtproject\\untitled1\\infotxt\\未审核内容\\未审核技能证书.txt");
//    if(!f.open(QIODevice::ReadOnly))
//    {
//        qDebug()<<"无法打开文件";
//    };
//    while(!f.atEnd())
//    {
//        QByteArray line = f.readLine();
//        QString str(line);
//        qDebug()<< str;
//    }
//    f.close();
//    qDebug()<<"mian_on_text被执行完毕！";
    MainWindow w;
    w.show();

    return a.exec();
}
