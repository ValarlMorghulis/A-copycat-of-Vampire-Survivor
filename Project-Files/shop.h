#ifndef SHOP_H
#define SHOP_H

#include <QWidget>
#include"public.h"
#include<QMessageBox>

namespace Ui {
class shop;
}

class shop : public QWidget
{
    Q_OBJECT

public:
    int choose;
    int need;
    explicit shop(QWidget *parent = nullptr);
    ~shop();

signals:
    void back();//返回主界面

private slots:
    void on_back_clicked();

    void on_buy_clicked();

    void on_choose1_clicked();

    void on_choose2_clicked();

    void on_choose3_clicked();

    void on_choose4_clicked();

    void on_choose5_clicked();

    void on_choose6_clicked();

private:
    Ui::shop *ui;
};

#endif // SHOP_H
