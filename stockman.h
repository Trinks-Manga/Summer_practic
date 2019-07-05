#ifndef STOCKMAN_H
#define STOCKMAN_H
#include "entity.h"
#include "field.h"
#include <vector>


class StockMan : public Entity
{
protected:
private:
    StockMan(int x, int y);
    double money;
    static int radi;
public:
    static StockMan& getInstance(int x, int y){
        static StockMan instance(x, y);
        return instance;
    }
    void update(int Enemys) override;
    void check(std::vector<Entity*> En, int** map) override;
    int PayDay(int m) override;
    bool IsMoney() override;
};

#endif // STOCKMAN_H
