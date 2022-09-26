#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();//个人成果录入

    void on_pushButton_2_clicked();//个人成果查询

    void on_pushButton_5_clicked();//关闭界面

    void on_pushButton_4_clicked();//报错

    void on_toolButton_clicked();//背景音乐播放

    void GetData(QString);
public:
    Ui::MainWindow* GetUi()
    {
        return ui;
    }

private:
    Ui::MainWindow *ui;
    QMediaPlaylist* playlist;
    QMediaPlayer* player;
};

#endif // MAINWINDOW_H
