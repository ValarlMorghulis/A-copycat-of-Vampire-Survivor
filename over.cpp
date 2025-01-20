#include "over.h"
#include "ui_over.h"

over::over(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::over)
{
    ui->setupUi(this);
    this->setFixedSize(1920,1200);

    ui->confirm->setStyleSheet("QPushButton{background-color:rgba(45,63,197);border-radius:25px;color:white;border:10px solid rgba(196,156,89);}\
                           QPushButton:pressed{background-color:rgba(116,20,18);}");

    switch(chosenrole)
    {
    case 1:ui->role->setStyleSheet("border:5px solid rgba(196,156,89);image: url(:/new/prefix1/resourses/role1.png);border-radius:15px;");break;
    case 2:ui->role->setStyleSheet("border:5px solid rgba(196,156,89);image: url(:/new/prefix1/resourses/role2.png);border-radius:15px;");break;
    case 3:ui->role->setStyleSheet("border:5px solid rgba(196,156,89);image: url(:/new/prefix1/resourses/role3.png);border-radius:15px;");break;
    }
    switch(chosenmap)
    {
    case 1:ui->map2->setText("疯狂森林");break;
    case 2:ui->map2->setText("锦钿书库");break;
    }
    ui->time2->setText(gametime.toString("mm:ss"));
    ui->kill2->setText(QString::number(kill));
    ui->gain2->setText(QString::number(gain));
}

over::~over()
{
    delete ui;
}

void over::on_confirm_clicked()
{
    this->close();
    emit Over();
}
