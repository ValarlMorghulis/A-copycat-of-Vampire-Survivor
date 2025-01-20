#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include"public.h"

namespace Ui {
class setting;
}

class setting : public QWidget
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = 0);
    ~setting();

signals:
    void back();//返回主界面

private slots:
    void on_back_clicked();

    void on_slider1_valueChanged(int value);

    void on_checkBox_clicked(bool checked);

    void on_initialize_clicked();

    void on_slider2_valueChanged(int value);

private:
    Ui::setting *ui;
};

#endif // SETTING_H
