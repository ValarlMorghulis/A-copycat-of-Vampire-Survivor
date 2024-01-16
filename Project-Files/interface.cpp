#include "interface.h"
#include "ui_interface.h"

interface::interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::interface)
{
    ui->setupUi(this);
    this->setFixedSize(1920,1200);



    musiclist->setCurrentIndex(0);
    music->play();


    if(!file.open(QIODevice::ReadOnly))return; //判断文件是否正常打开

    QString str;
    //钱
    str=file.readLine();
    str=file.readLine();
    money=str.toInt();

    //等级
    str=file.readLine();
    str=file.readLine();
    level=str.toInt();

    //角色
    str=file.readLine();
    str=file.readLine();
    unlockedrole=str.toInt();

    //提升初始血量
    str=file.readLine();
    str=file.readLine();
    maxhp=str.toInt();

    //回血
    str=file.readLine();
    str=file.readLine();
    addhp=str.toInt();

    //提升初始速度
    str=file.readLine();
    str=file.readLine();
    addspeed=str.toInt();

    //提升拾取范围
    str=file.readLine();
    str=file.readLine();
    addzone=str.toInt();

    //减少间隙
    str=file.readLine();
    str=file.readLine();
    subintrval=str.toInt();

    //增加持续时间
    str=file.readLine();
    str=file.readLine();
    addduration=str.toInt();

    file.close();

    //按钮
    ui->start->setStyleSheet("QPushButton{background-color:rgba(45,63,197);border-radius:25px;color:white;border:10px solid rgba(196,156,89);}\
                           QPushButton:pressed{background-color:rgba(116,20,18);}");
    ui->shop->setStyleSheet("QPushButton{background-color:rgba(98,179,101);border-radius:25px;color:white;border:10px solid rgba(196,156,89);}\
                           QPushButton:pressed{background-color:rgba(116,20,18);}");
    ui->quit->setStyleSheet("QPushButton{background-color:rgba(194,60,34);border-radius:25px;color:white;border:10px solid rgba(196,156,89);}\
                            QPushButton:pressed{background-color:rgba(116,20,18);}");
    ui->set->setStyleSheet("QPushButton{background-color:rgba(45,63,197);border-radius:25px;color:white;border:10px solid rgba(196,156,89);}\
                            QPushButton:pressed{background-color:rgba(116,20,18);}");


    //文本                       
    ui->money->setText(QString::number(money));
}

interface::~interface()
{
    delete ui;
}

void interface::on_quit_clicked()
{
    this->close();
}

void interface::on_start_clicked()
{
    this->r=new role;
    connect(this->r,&role::back,this,[=](){
        ui->money->setText(QString::number(money));
               this->r->close();
               this->show();
           });
    this->hide();
    this->r->show();
    connect(this->r,&role::Over,this,[=](){
        interface *in=new interface;
        in->show();
           });
}

void interface::on_set_clicked()
{
    this->s=new setting;
    connect(this->s,&setting::back,this,[=](){
               this->s->close();
               this->show();
           });
    this->hide();
    this->s->show();
}

void interface::on_shop_clicked()
{
    this->sh=new shop;
    connect(this->sh,&shop::back,this,[=](){
        ui->money->setText(QString::number(money));
               this->sh->close();
               this->show();
           });
    this->hide();
    this->sh->show();
}
