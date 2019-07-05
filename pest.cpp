#include "pest.h"
#include "box.h"
#include "field.h"
#include "stockman.h"
#include <QRandomGenerator>


int Pest::radi = 150;

Pest::Pest(int type, int x, int y)
{
    this->x = x * Field::cellsize;
    this->y = y * Field::cellsize;
    typeGoods = type;
    dx = dy = 0;
    cell_x = cell_y = -1;
    rad = radi;
}

void Pest::check(std::vector<Entity*> En, int** map){
    for (int i = 0; i < En.size(); i++)
    {
        if (typeid(*En[i]) == typeid (StockMan)){
            if (rad > sqrt((En[i]->x - x) * (En[i]->x - x) + (En[i]->y - y) * (En[i]->y - y))){
                cell_x = En[i]->x;
                cell_y = En[i]->y;
                update(2);
                return;
          }


    }
    }
    update(0);
    return;
}

void Pest::update(int Enemys){
        if (Enemys == 2){
            dx = this->x - cell_x;
            dy = this->y - cell_y;
            if (dx != 0)
            dx/=abs(dx);
            if (dy != 0)
            dy/=abs(dy);
        }
        else{
        dx = qrand() % 3 - 1;
        dy = qrand() % 3 - 1;
        }
    this->x += dx * Field::cellsize;
    if (this->x >= Field::sizeMap * Field::cellsize) this->x = Field::sizeMap * Field::cellsize - Field::cellsize;
    if (this->x < 0) this->x = 0;
    this->y += dy * Field::cellsize;

    if (this->y >= Field::sizeMap * Field::cellsize) this->y = Field::sizeMap * Field::cellsize - Field::cellsize;
    if (this->y < 0) this->y = 0;
}

