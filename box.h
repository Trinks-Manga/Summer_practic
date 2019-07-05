#ifndef BOX_H
#define BOX_H

#include "entity.h"
#include "static_item.h"

class Box : public Static_item
{
    static int radi;
    static double damage;
    double durability;
    int type;
public:
    Box(int time, int type, int x1, int y1);
    bool update() override;
    int* Catch(std::vector<Entity *> *En) override;
};

#endif // BOX_H
