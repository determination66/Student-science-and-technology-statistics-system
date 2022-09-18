#include "form.h"

Form::Form(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowTitle("form接收界面！");
    this->setFixedSize(600,300);
    qle1 = new QLineEdit(this);
    qle1->setGeometry(120,20,200,40);
}

Form::~Form()
{}

void Form::getData(QString str)
{
    qle1->setText(str);
}
