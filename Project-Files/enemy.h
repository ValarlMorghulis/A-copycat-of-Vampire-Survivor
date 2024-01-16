#ifndef ENEMY_H
#define ENEMY_H

#include"public.h"
#include<QLineF>
#include<QGraphicsPixmapItem>
#include<QList>
#include<QTimer>

class Enemy : public QGraphicsPixmapItem
{
public:
    int hp;
    int type;
    int map;
    int speed;
    int attack;
    bool death=false;
    bool becollected=false;
    bool boss=false;
    bool turkey=false;
    bool barrier=false;
    Enemy(int type,int map,qreal randx,qreal randy);
    ~Enemy(){}
    void move();
    void moveup();
    void movedown();
    void moveright();
    void moveleft();
    void turn();
    void bemoved(QPoint dir,int mspeed);
    bool hurt(int num);
    void change();
    int width;
    int height;

};

#endif // ENEMY_H
