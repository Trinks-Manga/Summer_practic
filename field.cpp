#include "field.h"
#include "stockman.h"
#include "pest.h"
#include "entity.h"
#include "static_item.h"
#include "box.h"
#include "trap.h"
#include <vector>
#include <QRandomGenerator>
#define maxRand 1000
#define chancePest 980
#define chanceBox 800

int Field::sizeMap = 50;
int Field::cellsize = 10;


Field::Field()
{
    StockMan *SM = &StockMan::getInstance(25, 25);
    En.push_back(SM);
    map = new int*[sizeMap];
    for (int i = 0; i < sizeMap; i++)
        map[i] = new int[sizeMap];
    for (int i = 0; i < sizeMap; i++)
        for (int j = 0; j < sizeMap; j++)
            map[i][j] = 0;
    std::ifstream in("Map.txt");
    int x;
    while(in >> x){
        for (int j = 0; j < 15; j++)
            map[j][x] = wall;
        for (int j = 24; j < 40; j++)
            map[j][x] = wall;
    }
    map[25][25] = stockman;
}

void Field::update(){
    for(int i = 0; i < En.size();i++)
    {
        int x, y;
        x = En[i]->x/cellsize;
        y = En[i]->y/cellsize;
        En[i]->check(En, map);
        if (map[En[i]->x/cellsize][En[i]->y/cellsize] != 0){
            En[i]->x = x * cellsize;
            En[i]->y = y * cellsize;
        }else
        map[x][y] = 0;
        if (typeid(*En[i]) == typeid(StockMan)){
            map[En[i]->x/cellsize][En[i]->y/cellsize] = stockman;
            if (En[i]->hand && En[i]->IsMoney()){
                Trap *tr = new Trap(En[i]->cell_x, En[i]->cell_y);

                En[i]->PayDay(-tr->cost);
                Stat.push_back(tr);
                En[i]->cell_x = En[i]->cell_y = -1;
                En[i]->hand = false;
            }
        }
        else {
            map[En[i]->x/cellsize][En[i]->y/cellsize] = Pests;
        }
    }
    for (int i = 0; i < Stat.size(); i++){
        if (typeid(*Stat[i]) == typeid(Trap)){
            int *t;
            t = Stat[i]->Catch(&En);
            if (t != NULL){
                map[t[0] / cellsize][t[1]/cellsize] = 0;
            }
            map[Stat[i]->x / cellsize][Stat[i]->y / cellsize] = trap;
        }
        else{
            int *t;
            t = Stat[i]->Catch(&En);
            map[Stat[i]->x / cellsize][Stat[i]->y / cellsize] = box;
        }
        if (Stat[i]->update()){
            if (typeid(*Stat[i]) == typeid(Trap))
                map[Stat[i]->x / cellsize][Stat[i]->y / cellsize] = 0;
            else
            {
                map[Stat[i]->x / cellsize][Stat[i]->y / cellsize] = wall;
                En[0]->PayDay(Stat[i]->cost);
            }
            delete Stat[i];
            Stat.erase(Stat.begin() + i);
        }

    }
    if (qrand() % maxRand > chancePest){
        Pest *pest = new Pest(qrand() % 4, qrand() % sizeMap, qrand() % sizeMap);
        while (map[pest->x/cellsize][pest->y/cellsize] != 0){
            pest->x = qrand() % sizeMap;
            pest->y = qrand() % sizeMap;
        }
        En.push_back((pest));
        map[pest->x/cellsize][pest->y/cellsize] = Pests;
    }
    if (qrand() % maxRand > chanceBox){
        for (int i = 0; i < sizeMap; i++)
            for (int j = 0; j < sizeMap; j++){
                if (map[i][j] == wall){
                    Box *b = new Box(qrand() % 80 + 100, qrand() % 5, i * cellsize, j * cellsize);
                    Stat.push_back((b));
                    map[i][j] = box;
                    return;
                }
            }
    }
}

