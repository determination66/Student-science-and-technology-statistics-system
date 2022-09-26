/*
 * 主界面
 * 各功能开始界面，转接打开到对应功能界面
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "search.h"
#include "love.h"
#include "QPropertyAnimation"
#include <QMediaPlaylist>
#include <QMediaPlayer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置界面标题
    setWindowTitle(QString("大学生课外科技活动成果管理系统"));
    //设置界面图标
    setWindowIcon(QIcon("D:\\qtproject\\untitled1\\wust.png"));

    //设置界面背景
    setWindowFlags(Qt::WindowCloseButtonHint | Qt::MSWindowsFixedSizeDialogHint);
    QPixmap pixmap("D:\\qtproject\\untitled1\\background.png");
    QPalette palette=this->palette();
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);
    QPalette palette2=this->palette();
    palette2.setBrush(QPalette::WindowText,Qt::white);
    this->setPalette(palette2);

    //居中显示
    ui->label->setAlignment(Qt::AlignHCenter);

    //进入动画
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    //animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();

    //播放背景音乐
    playlist = new QMediaPlaylist;
    //connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    playlist->addMedia(QUrl::fromLocalFile("D:\\qtproject\\untitled1\\最伟大的作品 - 周杰伦.mp3"));
    //playlist->addMedia(QUrl::fromLocalFile("D:\\qtproject\\untitled1\\最伟大的作品 - 周杰伦.mp3"));
    playlist->setCurrentIndex(1);
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

    player=new QMediaPlayer;
    player->setPlaylist(playlist);
    player->play();
    //先关闭背景音乐
    on_toolButton_clicked();

}

MainWindow::~MainWindow()
{
    delete ui;
}



//学生个人成果录入
void MainWindow::on_pushButton_clicked()
{
    Dialog p;
    p.exec();
}

//学生个人成果查询界面
void MainWindow::on_pushButton_2_clicked()
{
    Search p;
    p.exec();
}


//用户界面
void MainWindow::on_pushButton_4_clicked()
{
    Love p;
    p.exec();
}

//关闭系统
void MainWindow::on_pushButton_5_clicked()
{
    this->close();
}


void MainWindow::GetData(QString str)
{
    qDebug()<<"mainwindow接收账号"<<str;
}


//暂停播放音乐
void MainWindow::on_toolButton_clicked()
{
    if(ui->toolButton->text()=="🎵播放")
    {
        player->play();
        ui->toolButton->setText("🎵暂停");
    }else
    {
        player->pause();
        ui->toolButton->setText("🎵播放");
    }
}
