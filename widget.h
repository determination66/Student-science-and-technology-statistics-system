#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

#include "form.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
signals:
    //发送数据的信号，不需要实体函数，在头文件定义就可以
    void sendData(QString);
private:
    QPushButton *Btn;
    Form *f;
    QLineEdit *qle;
private slots:
    void clicked_button();
};
#endif // WIDGET_H
