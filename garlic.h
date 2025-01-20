#ifndef GARLIC_H
#define GARLIC_H

#include<QGraphicsPixmapItem>

class Garlic : public QGraphicsPixmapItem
{
public:
    Garlic();
    int s;
    int damage;
    void upgrade(int level);
};

#endif // GARLIC_H
