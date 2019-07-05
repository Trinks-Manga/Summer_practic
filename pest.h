#ifndef PEST_H
#define PEST_H

#include <vector>
#include "entity.h"

class Pest : public Entity
{
    static int radi;
public:
    Pest(int type, int x, int y);
    void update(int Enemys) override;
    void check(std::vector<Entity*> En, int** map) override;
};

#endif // PEST_H
