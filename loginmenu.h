#ifndef LOGINMENU_H
#define LOGINMENU_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class LoginMenu;
}

class LoginMenu : public QWidget
{
    Q_OBJECT

public:
    explicit LoginMenu(QWidget *parent = nullptr);
    ~LoginMenu();
private slots:
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

    void GetData(QString);

    void on_pushButton_3_clicked();

    //void on_pushButton_4_clicked();

private:
    Ui::LoginMenu *ui;
};

#endif // LOGINMENU_H
