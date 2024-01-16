#include "map.h"
#include "ui_map.h"

map::map(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::map)
{
    ui->setupUi(this);
    this->setFixedSize(1920,1200);


    ui->confirm->setStyleSheet("QPushButton{background-color:rgba(98,179,101);border-radius:25px;color:white;border:10px solid rgba(196,156,89);}\
                           QPushButton:pressed{background-color:rgba(116,20,18);}");
    ui->back->setStyleSheet("QPushButton{background-color:rgba(194,60,34);border-radius:25px;color:white;border:10px solid rgba(196,156,89);}\
                            QPushButton:pressed{background-color:rgba(116,20,18);}");

    chosenmap=1;
    ui->money->setText(QString::number(money));
}

map::~map()
{
    delete ui;
}


void map::on_back_clicked()
{
    emit this->back();
}

void map::on_confirm_clicked()
{
    if(ifchoose==true)
    {
        if(chosenmap==1){
            QFile gamefile1("D://QTgame//1//1//resourses//1.txt");
            if(gamefile1.exists()){
                QMessageBox msgBox;
                msgBox.setText("检测到存档");
                msgBox.setInformativeText("是否继续游戏?");
                msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                msgBox.setDefaultButton(QMessageBox::Ok);
                int ret = msgBox.exec();
                if(ret == QMessageBox::Ok){
                    read=chosenmap;
                }
            }
        }
        else{
            QFile gamefile2("D://QTgame//1//1//resourses//2.txt");
            if(gamefile2.exists()){
                QMessageBox msgBox;
                msgBox.setText("检测到存档");
                msgBox.setInformativeText("是否继续游戏?");
                msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                msgBox.setDefaultButton(QMessageBox::Ok);
                int ret = msgBox.exec();
                if(ret == QMessageBox::Ok){
                    read=chosenmap;
                }
            }
        }
        this->g=new game;
        this->close();
        this->g->show();
        connect(this->g,&game::Over,this,[=](){
            emit Over();
               });
    }
    else{
        QMessageBox::information(this,"提示","请选择关卡！");
    }
}

void map::on_map1_clicked()
{
    chosenmap=1;
    ifchoose=true;
    ui->map1->setStyleSheet("QPushButton{border:5px solid red;image: url(:/new/prefix1/resourses/forest.png);}");
    ui->map2->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);image: url(:/new/prefix1/resourses/library.png);}");
}

void map::on_map2_clicked()
{
    chosenmap=2;
    ifchoose=true;
    ui->map1->setStyleSheet("QPushButton{border:5px solid rgba(196,156,89);image: url(:/new/prefix1/resourses/forest.png);}");
    ui->map2->setStyleSheet("QPushButton{border:5px solid red;image: url(:/new/prefix1/resourses/library.png);}");
}
