#ifndef BOSSBULLET_H
#define BOSSBULLET_H

#include<QGraphicsPixmapItem>

class bossbullet: public QGraphicsPixmapItem
{
public:
    bossbullet(QPoint d,QPointF pos);
    int speed;
    int damage;
    bool beremoved=false;

    QPoint dir;
    bool move();

    void bemoved(QPoint d,int mspeed);

    ~bossbullet(){}
};


#endif // BOSSBULLET_H
