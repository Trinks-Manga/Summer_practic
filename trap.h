#ifndef TRAP_H
#define TRAP_H

#include "entity.h"
#include "static_item.h"

class Trap  : public Static_item
{
public:
    static int radi;
    static int timeofLife;
    static int costs;
    Trap(int x1, int y1);
    bool update() override;
    int* Catch(std::vector<Entity *> *En) override;
};

#endif // TRAP_H
