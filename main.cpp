#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        //记得widget个form可以删除
    MainWindow w;
    w.show();

    return a.exec();
}
