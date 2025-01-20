#include "setting.h"
#include "ui_setting.h"

setting::setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
    this->setFixedSize(1920,1200);

    ui->back->setStyleSheet("QPushButton{background-color:rgba(194,60,34);border-radius:25px;color:white;border:10px solid rgba(196,156,89);}\
                            QPushButton:pressed{background-color:rgba(116,20,18);}");
    ui->money->setText(QString::number(money));
}

setting::~setting()
{
    delete ui;
}

void setting::on_back_clicked()
{
    emit this->back();
}

void setting::on_slider1_valueChanged(int value)
{
    player->setVolume(value);
}


void setting::on_slider2_valueChanged(int value)
{
    music->setVolume(value);
}

void setting::on_checkBox_clicked(bool checked)
{
    if(checked==true){
        music->setVolume(0);
        player->setVolume(0);
        ui->slider1->setValue(0);
        ui->slider2->setValue(0);
    }
    else {
        music->setVolume(50);
        player->setVolume(50);
        ui->slider1->setValue(50);
        ui->slider2->setValue(50);
    }
}

void setting::on_initialize_clicked()
{
    music->setVolume(50);
    player->setVolume(50);
    ui->checkBox->setCheckState(Qt::Unchecked);
    ui->slider1->setValue(50);
    ui->slider2->setValue(50);
}

