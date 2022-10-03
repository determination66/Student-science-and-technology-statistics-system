#ifndef ADDSTU_H
#define ADDSTU_H

#include <QWidget>

namespace Ui {
class addstu;
}

class addstu : public QWidget
{
    Q_OBJECT

public:
    explicit addstu(QWidget *parent = nullptr);
    ~addstu();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::addstu *ui;
};

#endif // ADDSTU_H
