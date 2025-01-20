#include "enemy.h"

Enemy::Enemy(int type,int map,qreal randx,qreal randy)
{
    this->type=type;
    this->map=map;
    if(map==1){
        switch (type) {
        case 1:{
            if(randx>960){
                QPixmap enemy(":/new/prefix1/resourses/bat1.png");
                enemy=enemy.scaled(QSize(66,48));
                width=66;
                height=48;
                this->setPixmap(enemy);
            }
            else{
                QPixmap enemy(":/new/prefix1/resourses/bat2.png");
                enemy=enemy.scaled(QSize(66,48));
                width=66;
                height=48;
                this->setPixmap(enemy);
            }
            hp=qrand()%5;
            attack=3;
            speed=2;
            break;
            }
        case 2:{
            if(randx>960){
                QPixmap enemy(":/new/prefix1/resourses/bat1.png");
                enemy=enemy.scaled(QSize(110,80));
                width=110;
                height=80;
                this->setPixmap(enemy);
            }
            else{
                QPixmap enemy(":/new/prefix1/resourses/bat2.png");
                enemy=enemy.scaled(QSize(110,80));
                width=110;
                height=80;
                this->setPixmap(enemy);
            }
            hp=45;
            attack=5;
            speed=2;
            break;
            }
        case 3:{
            if(randx>960){
                QPixmap enemy(":/new/prefix1/resourses/boss1.png");
                enemy=enemy.scaled(QSize(110,80));
                width=110;
                height=80;
                this->setPixmap(enemy);
            }
            else{
                QPixmap enemy(":/new/prefix1/resourses/boss1_2.png");
                enemy=enemy.scaled(QSize(110,80));
                width=110;
                height=80;
                this->setPixmap(enemy);
            }
            boss=true;
            hp=500;
            attack=8;
            speed=3;
            break;
            }
        case 4:{
            int x=rand()%2;
            if(x==0) {
                QPixmap barrier1(":/new/prefix1/resourses/barrier1.png");
                width=31;
                height=49;
                hp=10;
                this->setPixmap(barrier1);
            }
            else {
                QPixmap barrier2(":/new/prefix1/resourses/barrier2.png");
                width=32;
                height=49;
                hp=1000000;
                this->setPixmap(barrier2);
            }
            barrier=true;
            break;
            }
        }
    }
    else if (map==2) {
        switch (type) {
        case 1:{
            if(randx>960){
                QPixmap enemy(":/new/prefix1/resourses/wood1.png");
                enemy=enemy.scaled(QSize(60,90));
                width=60;
                height=90;
                this->setPixmap(enemy);
            }
            else{
                QPixmap enemy(":/new/prefix1/resourses/wood2.png");
                enemy=enemy.scaled(QSize(60,90));
                width=60;
                height=90;
                this->setPixmap(enemy);
            }
            hp=5;
            attack=3;
            speed=2;
            break;
            }
        case 2:{
            if(randx>960){
                QPixmap enemy(":/new/prefix1/resourses/vegetable1.png");
                enemy=enemy.scaled(QSize(60,60));
                width=60;
                height=60;
                this->setPixmap(enemy);
            }
            else{
                QPixmap enemy(":/new/prefix1/resourses/vegetable2.png");
                enemy=enemy.scaled(QSize(60,60));
                width=60;
                height=60;
                this->setPixmap(enemy);
            }
            hp=5;
            attack=3;
            speed=2;
            break;
            }
        case 3:{
            if(randx>960){
                QPixmap enemy(":/new/prefix1/resourses/boss2.png");
                enemy=enemy.scaled(QSize(80,150));
                width=80;
                height=150;
                this->setPixmap(enemy);
            }
            else{
                QPixmap enemy(":/new/prefix1/resourses/boss2_2.png");
                enemy=enemy.scaled(QSize(80,150));
                width=80;
                height=150;
                this->setPixmap(enemy);
            }
            boss=true;
            hp=500;
            attack=8;
            speed=3;
            break;
            }
        case 4:{
            int x=rand()%2;
            if(x==0) {
                QPixmap barrier1(":/new/prefix1/resourses/barrier1.png");
                width=62;
                height=99;
                hp=10;
                this->setPixmap(barrier1);
            }
            else {
                QPixmap barrier2(":/new/prefix1/resourses/barrier2.png");
                width=64;
                height=99;
                hp=1000000;
                this->setPixmap(barrier2);
            }
            barrier=true;
            break;
            }
        }
    }
    this->setPos(randx,randy);
}

void Enemy::move()
{
    if(boss==false)
    {
        if(death==false||becollected==true)
        {
            turn();
            QLineF line(this->x(),this->y(),960,600);
            qreal rad=line.angle()*3.14/180;
            this->moveBy(cos(rad)*speed,-sin(rad)*speed);
        }
    }
    else {
        if(death==false)
        {
            turn();
            QLineF line(this->x(),this->y(),960,600);
            qreal rad=line.angle()*3.14/180;
            this->moveBy(cos(rad)*speed,-sin(rad)*speed);
        }
    }
}

void Enemy::moveup()
{
    if(death==false||becollected==true)
    {
        this->moveBy(0,-speed);
    }
}

void Enemy::movedown()
{
    if(death==false||becollected==true)
    {
        this->moveBy(0,speed);
    }
}

void Enemy::moveright()
{
    if(death==false||becollected==true)
    {
        this->moveBy(speed,0);
    }
}

void Enemy::moveleft()
{
    if(death==false||becollected==true)
    {
        this->moveBy(-speed,0);
    }
}

void Enemy::turn()
{
    if(death==false){
        if(this->x()>960){
            if(map==1){
                switch(type){
                case 1:{
                    QPixmap enemy(":/new/prefix1/resourses/bat1.png");
                    enemy=enemy.scaled(QSize(66,48));
                    width=66;
                    height=48;
                    this->setPixmap(enemy);
                    break;
                }
                case 2:{
                    QPixmap enemy(":/new/prefix1/resourses/bat1.png");
                    enemy=enemy.scaled(QSize(110,80));
                    width=110;
                    height=80;
                    this->setPixmap(enemy);
                    break;
                }
                case 3:{
                    QPixmap enemy(":/new/prefix1/resourses/boss1.png");
                    enemy=enemy.scaled(QSize(150,120));
                    width=150;
                    height=120;
                    this->setPixmap(enemy);
                    break;
                }
                }
            }
            else {
                switch(type){
                case 1:{
                    QPixmap enemy(":/new/prefix1/resourses/wood1.png");
                    enemy=enemy.scaled(QSize(60,90));
                    width=60;
                    height=90;
                    this->setPixmap(enemy);
                    break;
                }
                case 2:{
                    QPixmap enemy(":/new/prefix1/resourses/vegetable1.png");
                    enemy=enemy.scaled(QSize(70,70));
                    width=60;
                    height=60;
                    this->setPixmap(enemy);
                    break;
                }
                case 3:{
                    QPixmap enemy(":/new/prefix1/resourses/boss2.png");
                    enemy=enemy.scaled(QSize(80,150));
                    width=80;
                    height=150;
                    this->setPixmap(enemy);
                    break;
                }
                }
            }
        }
        else {
            if(map==1){
                switch(type){
                case 1:{
                    QPixmap enemy(":/new/prefix1/resourses/bat2.png");
                    enemy=enemy.scaled(QSize(66,48));
                    width=66;
                    height=48;
                    this->setPixmap(enemy);
                    break;
                }
                case 2:{
                    QPixmap enemy(":/new/prefix1/resourses/bat2.png");
                    enemy=enemy.scaled(QSize(110,80));
                    width=110;
                    height=80;
                    this->setPixmap(enemy);
                    break;
                }
                case 3:{
                    QPixmap enemy(":/new/prefix1/resourses/boss1_2.png");
                    enemy=enemy.scaled(QSize(150,120));
                    width=150;
                    height=120;
                    this->setPixmap(enemy);
                    break;
                }
                }
            }
            else {
                switch(type){
                case 1:{
                    QPixmap enemy(":/new/prefix1/resourses/wood2.png");
                    enemy=enemy.scaled(QSize(60,90));
                    width=60;
                    height=90;
                    this->setPixmap(enemy);
                    break;
                }
                case 2:{
                    QPixmap enemy(":/new/prefix1/resourses/vegetable2.png");
                    enemy=enemy.scaled(QSize(60,60));
                    width=60;
                    height=60;
                    this->setPixmap(enemy);
                    break;
                }
                case 3:{
                    QPixmap enemy(":/new/prefix1/resourses/boss2_2.png");
                    enemy=enemy.scaled(QSize(80,150));
                    width=80;
                    height=150;
                    this->setPixmap(enemy);
                    break;
                }
                }
            }
        }
    }
}

void Enemy::bemoved(QPoint dir,int mspeed)
{
    if(barrier==false)
    {
    turn();
    }
    this->moveBy(dir.x()*mspeed,dir.y()*mspeed);
}

bool Enemy::hurt(int num)
{
    if(barrier==false){
        QPixmap p;
        this->setPixmap(p);
    }
    hp=hp-num;
    if(hp<=0){
        if(barrier==false)kill++;
        attack=0;
        speed=5;
        death=true;
        return true;
    }
    return false;
}

void Enemy::change()
{
    switch (type) {
    case 1:{
        int x=rand()%50;
        if(x==5)
        {
            turkey=true;
            QPixmap p(":/new/prefix1/resourses/turkey.png");
            p=p.scaled(QSize(50,42));
            this->setPixmap(p);
        }
        else {
            QPixmap p(":/new/prefix1/resourses/gem1.png");
            this->setPixmap(p);
        }
        break;
        }
    case 2:{
        int x=rand()%50;
        if(x==5)
        {
            turkey=true;
            QPixmap p(":/new/prefix1/resourses/turkey.png");
            p=p.scaled(QSize(50,42));
            this->setPixmap(p);
        }
        else {
            QPixmap p(":/new/prefix1/resourses/gem2.png");
            this->setPixmap(p);
        }
        break;
        }
    case 3:{
        QPixmap p(":/new/prefix1/resourses/reward.png");
        this->setPixmap(p);
        break;
        }
    case 4:{
        QPixmap p(":/new/prefix1/resourses/littlemoney.png");
        p=p.scaled(QSize(33,33));
        this->setPixmap(p);
        break;
        }
    }
    speed=17;
}
