#include "garlic.h"

Garlic::Garlic()
{
    damage=5;
    s=200;
    this->setPos(960-s/2,600-s/2);
    QPixmap picture(":/new/prefix1/resourses/garlic.png");
    picture=picture.scaled(QSize(s,s));
    this->setPixmap(picture);
}

void Garlic::upgrade(int level)
{
    switch(level)
    {
    case 1:{
        damage=5;
        s=200;
        break;
    }
    case 2:{
        damage=7;
        s=240;
        break;
    }
    case 3:{
        damage=8;
        s=240;
        break;
    }
    case 4:{
        damage=9;
        s=280;
        break;
    }
    case 5:{
        damage=11;
        s=280;
        break;
    }
    case 6:{
        damage=12;
        s=320;
        break;
    }
    }

    this->setPos(960-s/2,600-s/2);
    QPixmap picture(":/new/prefix1/resourses/garlic.png");
    picture=picture.scaled(QSize(s,s));
    this->setPixmap(picture);
}
