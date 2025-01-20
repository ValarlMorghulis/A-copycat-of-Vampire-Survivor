#include "bullet_stone.h"

Bulletstone::Bulletstone(int right,int up,int addduration,int level)
{
    switch(level)
    {
    case 1:{
        damage=10;
        speed=8;
        duration=200+16*addduration;
        break;
    }
    case 2:{
        damage=15;
        speed=10;
        duration=200+16*addduration;
        break;
    }
    case 3:{
        damage=20;
        speed=10;
        duration=260+16*addduration;
        break;
    }
    case 4:{
        damage=20;
        speed=10;
        duration=260+16*addduration;
        break;
    }
    case 5:{
        damage=25;
        speed=12;
        duration=260+16*addduration;
        break;
    }
    case 6:{
        damage=30;
        speed=12;
        duration=320+16*addduration;
        break;
    }
    }
    qreal z=rand()%90;
    switch(right){
    case 0:{
        switch(up)
        {
        case 1:{
            dirx=cos((z-135)*3.14/180);
            diry=sin((z-135)*3.14/180);
            break;
        }
        case 2:{
            dirx=cos((z+45)*3.14/180);
            diry=sin((z+45)*3.14/180);
            break;
        }
        }
        break;
    }
    case 1:{
        dirx=cos((z-45)*3.14/180);
        diry=sin((z-45)*3.14/180);
        break;
    }
    case 2:{
        dirx=cos((z+135)*3.14/180);
        diry=sin((z+135)*3.14/180);
        break;
    }
    }
    this->setPos(960,600);
    QPixmap picture(":/new/prefix1/resourses/bullet.png");
    this->setPixmap(picture);
}

bool Bulletstone::move()
{
    duration--;
    if(duration<=0)return true;
    else {
        this->moveBy(dirx*speed,diry*speed);
        if(this->x()<0)dirx=-dirx;
        else if (this->x()>1920) dirx=-dirx;
        else if(this->y()<0) diry=-diry;
        else if(this->y()>1200)diry=-diry;
        return false;
    }
}

void Bulletstone::bemoved(QPoint dir, int mspeed)
{
    if(this->x()>0&&this->x()<1920&&this->y()>0&&this->y()<1200)this->moveBy(dir.x()*mspeed,dir.y()*mspeed);
}
