#ifndef STONE_H
#define STONE_H


#include<QGraphicsPixmapItem>
#include<QTimer>
#include<QLineF>

class Bulletstone : public QGraphicsPixmapItem
{
public:
    int speed;
    int damage;
    int duration;

    qreal dirx;
    qreal diry;

    Bulletstone(int right,int up,int addduratioon,int level);

    bool move();

    void bemoved(QPoint dir,int mspeed);

    ~Bulletstone(){}
};

#endif // STONE_H
