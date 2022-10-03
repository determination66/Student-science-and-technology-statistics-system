#ifndef MANAGE_H
#define MANAGE_H

#include <QWidget>

namespace Ui {
class Manage;
}

class Manage : public QWidget
{
    Q_OBJECT

public:
    explicit Manage(QWidget *parent = nullptr);
    ~Manage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Manage *ui;
};

#endif // MANAGE_H
