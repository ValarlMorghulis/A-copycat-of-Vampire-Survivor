#include "shop.h"
#include "ui_shop.h"

shop::shop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::shop)
{
    ui->setupUi(this);
    this->setFixedSize(1920,1200);

    ui->back->setStyleSheet("QPushButton{background-color:rgba(194,60,34);border-radius:25px;color:white;border:10px solid rgba(196,156,89);}\
                            QPushButton:pressed{background-color:rgba(116,20,18);}");
    ui->buy->setEnabled(false);
    ui->money->setText(QString::number(money));
    ui->choose1_1->setEnabled(false);
    ui->choose1_2->setEnabled(false);
    ui->choose1_3->setEnabled(false);
    ui->choose2_1->setEnabled(false);
    ui->choose2_2->setEnabled(false);
    ui->choose2_3->setEnabled(false);
    ui->choose2_4->setEnabled(false);
    ui->choose2_5->setEnabled(false);
    ui->choose3_1->setEnabled(false);
    ui->choose3_2->setEnabled(false);
    ui->choose4_1->setEnabled(false);
    ui->choose4_2->setEnabled(false);
    ui->choose5_1->setEnabled(false);
    ui->choose5_2->setEnabled(false);
    ui->choose6_1->setEnabled(false);
    ui->choose6_2->setEnabled(false);

    if(maxhp>0){
        ui->choose1_1->setCheckState(Qt::Checked);
        if(maxhp>1){
            ui->choose1_2->setCheckState(Qt::Checked);
            if(maxhp>2){
                ui->choose1_3->setCheckState(Qt::Checked);
            }
        }
    }

    if(addhp>0){
        ui->choose2_1->setCheckState(Qt::Checked);
        if(addhp>1){
            ui->choose2_2->setCheckState(Qt::Checked);
            if(addhp>2){
                ui->choose2_3->setCheckState(Qt::Checked);
                if(addhp>3){
                    ui->choose2_4->setCheckState(Qt::Checked);
                    if(addhp>4){
                        ui->choose2_5->setCheckState(Qt::Checked);
                    }
                }
            }
        }
    }

    if(addspeed>0){
        ui->choose3_1->setCheckState(Qt::Checked);
        if(addspeed>1){
            ui->choose3_2->setCheckState(Qt::Checked);
        }
    }

    if(subintrval>0){
        ui->choose4_1->setCheckState(Qt::Checked);
        if(subintrval>1){
            ui->choose4_2->setCheckState(Qt::Checked);
        }
    }

    if(addduration>0){
        ui->choose5_1->setCheckState(Qt::Checked);
        if(addduration>1){
            ui->choose5_2->setCheckState(Qt::Checked);
        }
    }

    if(addzone>0){
        ui->choose6_1->setCheckState(Qt::Checked);
        if(addzone>1){
            ui->choose6_2->setCheckState(Qt::Checked);
        }
    }
}

shop::~shop()
{
    delete ui;
}

void shop::on_back_clicked()
{
    emit this->back();
}

void shop::on_buy_clicked()
{
    if(money>=need){
        switch (choose) {
        case 1:{
            if(maxhp<=3)
            {
                maxhp++;
                if(maxhp>0){
                    ui->choose1_1->setCheckState(Qt::Checked);
                    if(maxhp>1){
                        ui->choose1_2->setCheckState(Qt::Checked);
                        if(maxhp>2){
                            ui->choose1_3->setCheckState(Qt::Checked);
                            ui->buy->setEnabled(false);
                            ui->buy->setStyleSheet("QPushButton{background-color:grey;border-radius:25px;color:white;border:10px solid rgba(196,156,89);}");
                            ui->buy->setText("已满级！");
                        }
                    }
                }
                playerhp=100+10*maxhp;
            }
            break;
        }
        case 2:{
            addhp++;
            if(addhp>0){
                ui->choose2_1->setCheckState(Qt::Checked);
                if(addhp>1){
                    ui->choose2_2->setCheckState(Qt::Checked);
                    if(addhp>2){
                        ui->choose2_3->setCheckState(Qt::Checked);
                        if(addhp>3){
                            ui->choose2_4->setCheckState(Qt::Checked);
                            if(addhp>4){
                                ui->choose2_5->setCheckState(Qt::Checked);
                                ui->buy->setEnabled(false);
                                ui->buy->setStyleSheet("QPushButton{background-color:grey;border-radius:25px;color:white;border:10px solid rgba(196,156,89);}");
                                ui->buy->setText("已满级！");
                            }
                        }
                    }
                }
            }
            break;
        }
        case 3:{
            addspeed++;
            if(addspeed>0){
                ui->choose3_1->setCheckState(Qt::Checked);
                if(addspeed>1){
                    ui->choose3_2->setCheckState(Qt::Checked);
                    ui->buy->setEnabled(false);
                    ui->buy->setStyleSheet("QPushButton{background-color:grey;border-radius:25px;color:white;border:10px solid rgba(196,156,89);}");
                    ui->buy->setText("已满级！");
                }
            }
            break;
        }
        case 4:{
            subintrval++;
            if(subintrval>0){
                ui->choose4_1->setCheckState(Qt::Checked);
                if(subintrval>1){
                    ui->choose4_2->setCheckState(Qt::Checked);
                    ui->buy->setEnabled(false);
                    ui->buy->setStyleSheet("QPushButton{background-color:grey;border-radius:25px;color:white;border:10px solid rgba(196,156,89);}");
                    ui->buy->setText("已满级！");
                }
            }
            break;
        }
        case 5:{
            addduration++;
            if(addduration>0){
                ui->choose5_1->setCheckState(Qt::Checked);
                if(addduration>1){
                    ui->choose5_2->setCheckState(Qt::Checked);
                    ui->buy->setEnabled(false);
                    ui->buy->setStyleSheet("QPushButton{background-color:grey;border-radius:25px;color:white;border:10px solid rgba(196,156,89);}");
                    ui->buy->setText("已满级！");
                }
            }
            break;
        }
        case 6:{
            addzone++;
            if(addzone>0){
                ui->choose6_1->setCheckState(Qt::Checked);
                if(addzone>1){
                    ui->choose6_2->setCheckState(Qt::Checked);
                    ui->buy->setEnabled(false);
                    ui->buy->setStyleSheet("QPushButton{background-color:grey;border-radius:25px;color:white;border:10px solid rgba(196,156,89);}");
                    ui->buy->setText("已满级！");
                }
            }
            break;
        }
        }
        submoney(need);
    }
    else {
        QMessageBox::information(this,"提示","金钱不足！");
    }
    ui->money->setText(QString::number(money));
}

void shop::on_choose1_clicked()
{
    choose=1;
    need=300;
    ui->needmoney->setText(QString::number(need));
    if(maxhp==3){
        ui->buy->setEnabled(false);
        ui->buy->setText("已满级！");
        ui->buy->setStyleSheet("QPushButton{background-color:grey;border-radius:25px;color:white;border:10px solid rgba(196,156,89);}");
    }
    else {
        ui->buy->setEnabled(true);
        ui->buy->setText("购 买");
        ui->buy->setStyleSheet("QPushButton{background-color:rgba(98,179,101);border-radius:25px;color:white;border:10px solid rgba(196,156,89);}\
                                  QPushButton:pressed{background-color:rgba(116,20,18);}");
    }
    ui->choose1->setStyleSheet("QPushButton{border:5px solid red;border-radius:15px;image: url(:/new/prefix1/resourses/maxhp.png);}");
    ui->choose2->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/hp++.png);}");
    ui->choose3->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/speed++.png);}");
    ui->choose4->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/interval--.png);}");
    ui->choose5->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/duration++.png);}");
    ui->choose6->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/collectzone++.png);}");
    ui->information->setText("每强化一层，生命上限+10%，最多+30%");
}

void shop::on_choose2_clicked()
{
    choose=2;
    need=200;
    ui->needmoney->setText(QString::number(need));
    if(addhp==5){
        ui->buy->setEnabled(false);
        ui->buy->setText("已满级！");
        ui->buy->setStyleSheet("QPushButton{background-color:grey;border-radius:25px;color:white;border:10px solid rgba(196,156,89);}");
    }
    else {
        ui->buy->setEnabled(true);
        ui->buy->setText("购 买");
        ui->buy->setStyleSheet("QPushButton{background-color:rgba(98,179,101);border-radius:25px;color:white;border:10px solid rgba(196,156,89);}\
                                  QPushButton:pressed{background-color:rgba(116,20,18);}");
    }
    ui->choose1->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/maxhp.png);}");
    ui->choose2->setStyleSheet("QPushButton{border:5px solid red;border-radius:15px;image: url(:/new/prefix1/resourses/hp++.png);}");
    ui->choose3->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/speed++.png);}");
    ui->choose4->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/interval--.png);}");
    ui->choose5->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/duration++.png);}");
    ui->choose6->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/collectzone++.png);}");
    ui->information->setText("每强化一层，每秒生命恢复+0.1，最多+0.5");
}

void shop::on_choose3_clicked()
{
    choose=3;
    need=300;
    ui->needmoney->setText(QString::number(need));
    if(addspeed==2){
        ui->buy->setEnabled(false);
        ui->buy->setText("已满级！");
        ui->buy->setStyleSheet("QPushButton{background-color:grey;border-radius:25px;color:white;border:10px solid rgba(196,156,89);}");
    }
    else {
        ui->buy->setEnabled(true);
        ui->buy->setText("购 买");
        ui->buy->setStyleSheet("QPushButton{background-color:rgba(98,179,101);border-radius:25px;color:white;border:10px solid rgba(196,156,89);}\
                                  QPushButton:pressed{background-color:rgba(116,20,18);}");
    }
    ui->choose1->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/maxhp.png);}");
    ui->choose2->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/hp++.png);}");
    ui->choose3->setStyleSheet("QPushButton{border:5px solid red;border-radius:15px;image: url(:/new/prefix1/resourses/speed++.png);}");
    ui->choose4->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/interval--.png);}");
    ui->choose5->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/duration++.png);}");
    ui->choose6->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/collectzone++.png);}");
    ui->information->setText("每强化一层，角色移动速度+5%，最多+10%");
}

void shop::on_choose4_clicked()
{
    choose=4;
    need=350;
    ui->needmoney->setText(QString::number(need));
    if(subintrval==2){
        ui->buy->setEnabled(false);
        ui->buy->setText("已满级！");
        ui->buy->setStyleSheet("QPushButton{background-color:grey;border-radius:25px;color:white;border:10px solid rgba(196,156,89);}");
    }
    else {
        ui->buy->setEnabled(true);
        ui->buy->setText("购 买");
        ui->buy->setStyleSheet("QPushButton{background-color:rgba(98,179,101);border-radius:25px;color:white;border:10px solid rgba(196,156,89);}\
                                  QPushButton:pressed{background-color:rgba(116,20,18);}");
    }
    ui->choose1->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/maxhp.png);}");
    ui->choose2->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/hp++.png);}");
    ui->choose3->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/speed++.png);}");
    ui->choose4->setStyleSheet("QPushButton{border:5px solid red;border-radius:15px;image: url(:/new/prefix1/resourses/interval--.png);}");
    ui->choose5->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/duration++.png);}");
    ui->choose6->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/collectzone++.png);}");
    ui->information->setText("每强化一层，武器使用频率+2.5%，最多+5%");
}

void shop::on_choose5_clicked()
{
    choose=5;
    need=300;
    ui->needmoney->setText(QString::number(need));
    if(addduration==2){
        ui->buy->setEnabled(false);
        ui->buy->setText("已满级！");
        ui->buy->setStyleSheet("QPushButton{background-color:grey;border-radius:25px;color:white;border:10px solid rgba(196,156,89);}");
    }
    else {
        ui->buy->setEnabled(true);
        ui->buy->setText("购 买");
        ui->buy->setStyleSheet("QPushButton{background-color:rgba(98,179,101);border-radius:25px;color:white;border:10px solid rgba(196,156,89);}\
                                  QPushButton:pressed{background-color:rgba(116,20,18);}");
    }
    ui->choose1->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/maxhp.png);}");
    ui->choose2->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/hp++.png);}");
    ui->choose3->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/speed++.png);}");
    ui->choose4->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/interval--.png);}");
    ui->choose5->setStyleSheet("QPushButton{border:5px solid red;border-radius:15px;image: url(:/new/prefix1/resourses/duration++.png);}");
    ui->choose6->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/collectzone++.png);}");
    ui->information->setText("每强化一层，武器持续时间+15%，最多+30%");

}

void shop::on_choose6_clicked()
{
    choose=6;
    need=250;
    ui->needmoney->setText(QString::number(need));
    if(addzone==2){
        ui->buy->setEnabled(false);
        ui->buy->setText("已满级！");
        ui->buy->setStyleSheet("QPushButton{background-color:grey;border-radius:25px;color:white;border:10px solid rgba(196,156,89);}");
    }
    else {
        ui->buy->setEnabled(true);
        ui->buy->setText("购 买");
        ui->buy->setStyleSheet("QPushButton{background-color:rgba(98,179,101);border-radius:25px;color:white;border:10px solid rgba(196,156,89);}\
                                  QPushButton:pressed{background-color:rgba(116,20,18);}");
    }
    ui->choose1->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/maxhp.png);}");
    ui->choose2->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/hp++.png);}");
    ui->choose3->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/speed++.png);}");
    ui->choose4->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/interval--.png);}");
    ui->choose5->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);border-radius:15px;image: url(:/new/prefix1/resourses/duration++.png);}");
    ui->choose6->setStyleSheet("QPushButton{border:5px solid red;border-radius:15px;image: url(:/new/prefix1/resourses/collectzone++.png);}");
    ui->information->setText("每强化一层，道具拾取范围+25%，最多+50%");
}
