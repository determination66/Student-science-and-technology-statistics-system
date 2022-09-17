#ifndef FORM_H
#define FORM_H
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
private:
    QLineEdit *qle1;
private slots:
    //得到数据的槽函数
    void getData(QString);
};

#endif // FORM_H
