#ifndef BULLET_H
#define BULLET_H

#include<QGraphicsPixmapItem>

class Knife : public QGraphicsPixmapItem
{
public:
    int speed;
    int damage;
    bool beremoved=false;

    QPoint dir;

    Knife(int right,int up,int level);

    bool move();

    void bemoved(QPoint d,int mspeed);

    ~Knife(){}

};

#endif // BULLET_H
