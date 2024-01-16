#include "knife.h"


Knife::Knife(int right,int up,int level)
{
    speed=10;
    switch(level)
    {
    case 1:{
        damage=10;
        break;
    }
    case 2:{
        damage=10;
        break;
    }
    case 3:{
        damage=15;
        break;
    }
    case 4:{
        damage=15;
        break;
    }
    case 5:{
        damage=20;
        break;
    }
    case 6:{
        damage=25;
        break;
    }
    }

    int x,y;
    qreal angle=0;
    switch(right){
    case 0:{
        x=0;
        switch (up) {
        case 0:angle=0;break;
        case 1:angle=-90;break;
        case 2:angle=90;break;
        }
        break;
    }
    case 1:{
        x=1;
        switch (up) {
        case 0:angle=0;break;
        case 1:angle=-45;break;
        case 2:angle=45;break;
        }
        break;
    }
    case 2:{
        x=-1;
        switch (up) {
        case 0:angle=180;break;
        case 1:angle=-135;break;
        case 2:angle=135;break;
        }
        break;
    }
    }
    switch (up) {
    case 0:y=0;break;
    case 1:y=-1;break;
    case 2:y=1;break;
    }

    dir=QPoint(x,y);
    this->setPos(960,600);
    this->setRotation(angle);


    QPixmap picture(":/new/prefix1/resourses/knife.png");
    this->setPixmap(picture);
}

bool Knife::move()
{
    this->moveBy(dir.x()*speed,dir.y()*speed);
    if(this->x()>1920||this->x()<0||this->y()>1200||this->y()<0)return true;
    if(beremoved==true)return true;
    else return false;
}

void Knife::bemoved(QPoint d,int mspeed)
{
    this->moveBy(d.x()*mspeed,d.y()*mspeed);
}

