#ifndef STATIC_ITEM_H
#define STATIC_ITEM_H

#include <vector>
#include "entity.h"

class Static_item
{
public:
    Static_item();
    int time;
    int rad;
    int cost;
    int x, y;
    virtual bool update() = 0;
    virtual int* Catch(std::vector<Entity *> *En);
};

#endif // STATIC_ITEM_H
