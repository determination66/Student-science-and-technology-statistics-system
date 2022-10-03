#ifndef loginwindow_H
#define loginwindow_H

#include <QMainWindow>
#include <QMediaPlayer>

namespace Ui {
class loginwindow;
}

class loginwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit loginwindow(QWidget *parent = 0);
    ~loginwindow();

private slots:
    void on_pushButton_clicked();//个人成果录入

    void on_pushButton_2_clicked();//个人成果查询

    void on_pushButton_5_clicked();//关闭界面

    void on_pushButton_4_clicked();//报错

    void on_toolButton_clicked();//背景音乐播放

    void GetData(QString);
public:
    Ui::loginwindow* GetUi()
   {
        return ui;
    }

private:
    Ui::loginwindow *ui;
    QMediaPlaylist* playlist;
    QMediaPlayer* player;
};

#endif // loginwindow_H
