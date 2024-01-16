#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include "game.h"
#include"public.h"
#include<QMessageBox>

namespace Ui {
class map;
}

class map : public QWidget
{
    Q_OBJECT

public:
    explicit map(QWidget *parent = 0);
    ~map();
    game* g;
    bool ifchoose=false;

signals:
    void back();//返回选角界面
    void Over();

private slots:
    void on_back_clicked();

    void on_confirm_clicked();

    void on_map1_clicked();

    void on_map2_clicked();

private:
    Ui::map *ui;
};

#endif // MAP_H
