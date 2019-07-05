#ifndef FIELD_H
#define FIELD_H


#include <vector>
#include "entity.h"
#include "static_item.h"
#include <fstream>
#define Pests 1
#define stockman 2
#define box 3
#define wall 4
#define trap 5



class Field
{
public:
    int static sizeMap;
    int static cellsize;
    int** map;
    Field();
    void update();
    std::vector<Entity*> En;
    std::vector<Static_item*> Stat;
};

#endif // FIELD_H
