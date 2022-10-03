#ifndef MANAGESTU_H
#define MANAGESTU_H

#include <QDialog>

namespace Ui {
class ManageStu;
}

class ManageStu : public QDialog
{
    Q_OBJECT

public:
    explicit ManageStu(QWidget *parent = nullptr);
    ~ManageStu();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ManageStu *ui;
};

#endif // MANAGESTU_H
