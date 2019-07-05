#include "box.h"
#include "pest.h"
#include "stockman.h"

double Box::damage = 0.05;
int Box::radi = 70;

Box::Box(int time, int type, int x1, int y1){
    durability = 1;
    rad = radi;
    x=x1;
    y=y1;
    this->time = time;
    cost = time / 10;
    this->type = type;
}

bool Box::update(){
    time--;
    if (time <= 0 || durability == 0)
        return true;
    return false;
}

int* Box::Catch(std::vector<Entity *> *En){
    for (int i = 0; i < En->size(); i++){
        if (typeid(*(*En)[i]) == typeid(Pest))
        if (rad > sqrt(((*En)[i]->x - x) * ((*En)[i]->x - x) + ((*En)[i]->y - y) * ((*En)[i]->y - y)) && (*En)[i]->typeGoods == type){
            durability -= damage;
            cost *= durability;
        }
    }
    return NULL;
}
