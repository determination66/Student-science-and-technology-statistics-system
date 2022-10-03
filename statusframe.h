#ifndef STATUSFRAME_H
#define STATUSFRAME_H

#include <QDialog>
#include"managestu.h"

namespace Ui {
class Statusframe;
}

class Statusframe : public QDialog
{
    Q_OBJECT

public:
    explicit Statusframe(QWidget *parent = 0);
    ~Statusframe();

private slots:

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();//查看目前通过成果

    void on_pushButton_7_clicked();//审核目前提交成果

    void on_pushButton_9_clicked();

private:
    Ui::Statusframe *ui;
};

#endif // STATUSFRAME_H
