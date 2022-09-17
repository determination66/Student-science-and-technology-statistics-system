#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("widget发送界面！");
    this->setFixedSize(800,600);
    Btn = new QPushButton(this);
    Btn->setGeometry(300,200,100, 50);
    qle = new QLineEdit(this);
    qle->setGeometry(120,20,200,40);
    Btn->setText("发送");

    f = new Form();
    connect(Btn,SIGNAL(clicked()),this,SLOT(clicked_button()));
    //这里才是连接信号和槽函数的重点
    connect(this,SIGNAL(sendData(QString)),f,SLOT(getData(QString)));
}

Widget::~Widget()
{
}

void Widget::clicked_button()
{
    f->show();
    QString strss = qle->text();
    emit sendData(strss);//发送数据，使用emit
}

