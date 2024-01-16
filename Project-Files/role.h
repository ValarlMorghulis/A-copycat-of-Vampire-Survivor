#ifndef ROLE_H
#define ROLE_H

#include <QWidget>
#include "map.h"
#include"public.h"
#include<QMessageBox>

namespace Ui {
class role;
}

class role : public QWidget
{
    Q_OBJECT

public:
    explicit role(QWidget *parent = 0);
    ~role();
    map* m;
    bool ifchoose=false;

signals:
    void back();//返回主界面
    void Over();

private slots:
    void on_back_clicked();

    void on_confirm_clicked();

    void on_role1_clicked();

    void on_role2_clicked();


    void on_role3_clicked();

private:
    Ui::role *ui;
};

#endif // ROLE_H
