#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include "role.h"
#include "setting.h"
#include "shop.h"
#include"public.h"
#include<QFile>
#include<QFileDialog>

namespace Ui {
class interface;
}

class interface : public QWidget
{
    Q_OBJECT

public:
    explicit interface(QWidget *parent = 0);
    ~interface();
    role *r;
    setting* s;
    shop* sh;

signals:
    void send(interface* in);

private slots:
    void on_quit_clicked();

    void on_start_clicked();


    void on_set_clicked();

    void on_shop_clicked();

private:
    Ui::interface *ui;
};

#endif // INTERFACE_H
