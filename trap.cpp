#include "trap.h"
#include "pest.h"
#include <typeinfo.h>

int Trap::radi = 60;
int Trap::timeofLife = 200;
int Trap::costs = 50;

Trap::Trap(int x1, int y1)
{
    rad = radi;
    x = x1;
    y = y1;
    time = timeofLife;
    cost = costs;
}

bool Trap::update(){
    time--;
    if (time <= 0){
        return 1;
    }
    else {
        return 0;
    }
}

int* Trap::Catch(std::vector<Entity *> *En){
    for (int i = 0; i< En->size(); i++){
        if (typeid(*(*En)[i]) == typeid(Pest)){
            if (rad > sqrt(((*En)[i]->x - x) * ((*En)[i]->x - x) + ((*En)[i]->y - y) * ((*En)[i]->y - y))){
                Entity *temp;
                int* t = new int[2];
                t[0] = (*En)[i]->x;
                t[1] = (*En)[i]->y;
                temp = (*En)[i];
                delete temp;
                En->erase(En->begin() + i);
                time /= 2;
                return t;
            }
        }
    }
    return NULL;
}
