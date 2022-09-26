#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QListWidgetItem>


#define N 5
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void save(QString d,QString sstr,QListWidgetItem *item,QString name,QString student_num,QString student_lel);

    void textchange(QListWidgetItem*);//双击行后 开启编辑

    void on_pushButton_clicked();//提交数据

    void on_radioButton_clicked();//各个类别科研成果 列表显示

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_pushButton_2_clicked();//关闭界面

private:
    Ui::Dialog *ui;

};

#endif // DIALOG_H
