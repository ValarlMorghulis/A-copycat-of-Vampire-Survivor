#include "bossbullet.h"

bossbullet::bossbullet(QPoint d,QPointF pos)
{
    speed=10;
    dir=d;
    damage=10;
    QPixmap picture(":/new/prefix1/resourses/ball.png");
    picture=picture.scaled(QSize(50,50));
    this->setPixmap(picture);
    this->setPos(pos);
}

bool bossbullet::move()
{
    this->moveBy(dir.x()*speed,dir.y()*speed);
    if(this->x()>1920||this->x()<0||this->y()>1200||this->y()<0)return true;
    if(beremoved==true)return true;
    else return false;
}

void bossbullet::bemoved(QPoint d,int mspeed)
{
    this->moveBy(d.x()*mspeed,d.y()*mspeed);
}
