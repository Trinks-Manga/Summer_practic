#include "stockman.h"
#include "pest.h"
#include "field.h"
#include "trap.h"
#include <QRandomGenerator>

int StockMan::radi = 350;

StockMan::StockMan(int x, int y)
{
    money = 100;
    dx = dy = 0;
    this->x = x * Field::cellsize;
    this->y = y * Field::cellsize;
    cell_x = cell_y = -1;
    hand = false;
    rad = radi;
}

void StockMan::update(int Enemys){
    dx = dy = 0;
    if (!hand){
    if (Enemys || cell_x >= 0){
        if (Hway.size() != 0){
            this->x = Hway[Hway.size() - 1].first * Field::cellsize;
            this->y = Hway[Hway.size() - 1].second * Field::cellsize;
            Hway.pop_back();
        }
        else {
            hand = true;
        }
    }else{
        dx = qrand() % 3 - 1;
        dy = qrand() % 3 - 1;
    }
    this->x += dx * Field::cellsize;
    if (this->x >= Field::cellsize * Field::sizeMap) this->x = Field::cellsize * Field::sizeMap - Field::cellsize;
    if (this->x < 0) this->x = 0;
    this->y += dy * Field::cellsize;
    if (this->y >= Field::cellsize * Field::sizeMap) this->y = Field::cellsize * Field::sizeMap - Field::cellsize;
    if (this->y < 0) this->y = 0;
    }
}


void StockMan::check(std::vector<Entity*> En, int** map){
    if (!hand){
    for (int i = 0; i < En.size(); i++){
        if (typeid(*En[i]) == typeid (Pest)){
            if (rad > sqrt((En[i]->x - x) * (En[i]->x - x) + (En[i]->y - y) * (En[i]->y - y)) && cell_x == -1 && !hand){
                AStar(x, y,En[i]->x , En[i]->y, map);
                cell_x = En[i]->x;
                cell_y = En[i]->y;
                update(1);
            return;
            }
        }
    }
    hand = false;
    update(0);
    }
    return;
}

int StockMan::PayDay(int m){
    money += m;
    return money;
}

bool StockMan::IsMoney(){
    if (money >= Trap::costs)
        return true;
    return false;
}
