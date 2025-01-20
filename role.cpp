#include "role.h"
#include "ui_role.h"

role::role(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::role)
{
    ui->setupUi(this);
    this->setFixedSize(1920,1200);

    //按钮
    ui->back->setStyleSheet("QPushButton{background-color:rgba(194,60,34);border-radius:25px;color:white;border:10px solid rgba(196,156,89);}\
                           QPushButton:pressed{background-color:rgba(116,20,18);}");
    ui->confirm->setStyleSheet("QPushButton{background-color:rgba(98,179,101);border-radius:25px;color:white;border:10px solid rgba(196,156,89);}\
                           QPushButton:pressed{background-color:rgba(116,20,18);}");
    ui->role1->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/role1.png);}");
    ui->role2->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/role2.png);}");



    ui->money->setText(QString::number(money));
}

role::~role()
{
    delete ui;
}


void role::on_back_clicked()
{
    emit this->back();
}

void role::on_confirm_clicked()
{
    if(ifchoose==true)
    {
        this->m=new map;
        connect(this->m,&map::back,this,[=](){
                        this->m->close();
                        this->show();
               });
        this->close();
        this->m->show();
        connect(this->m,&map::Over,this,[=](){
            emit Over();
               });
    }
    else{
        QMessageBox::information(this,"提示","请选择角色！");
    }
}

void role::on_role1_clicked()
{
    chosenrole=1;
    ifchoose=true;
    ui->role1->setStyleSheet("QPushButton{border:5px solid red;border-radius:15px;image: url(:/new/prefix1/resourses/role1.png);}");
    ui->role2->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/role2.png);}");
    ui->role3->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/role3.png);}");
    ui->information->setText("每升10级，造成伤害+10%，最多+50%。");
}

void role::on_role2_clicked()
{
    chosenrole=2;
    ifchoose=true;
    ui->role1->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/role1.png);}");
    ui->role2->setStyleSheet("QPushButton{border:5px solid red;border-radius:15px;image: url(:/new/prefix1/resourses/role2.png);}");
    ui->role3->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/role3.png);}");
    ui->information->setText("每升10级，飞射速度+10%，最多+30%。");
}



void role::on_role3_clicked()
{
    chosenrole=3;
    ifchoose=true;
    ui->role1->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/role1.png);}");
    ui->role2->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/role2.png);}");
    ui->role3->setStyleSheet("QPushButton{border:5px solid red;border-radius:15px;image: url(:/new/prefix1/resourses/role3.png);}");
    ui->information->setText("飞射物数量+1，对所有武器有效。");
}
