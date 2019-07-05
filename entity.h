#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

class Entity
{
public:
    Entity();
    int x, y;
    int cell_x, cell_y;
    bool hand;
    int rad;
    int typeGoods;
    virtual void update(int Enemys) = 0;
    virtual void check(std::vector<Entity*> En, int** map) = 0;
    virtual int PayDay(int m){return 0;}
    virtual bool IsMoney();
    std::vector<std::pair<int,int>> Hway;
protected:
    int dx, dy;
    void AStar(int x1, int y1, int x2, int y2, int** map);
};

#endif // ENTITY_H
