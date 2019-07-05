#include "entity.h"
#include "field.h"

Entity::Entity()
{

}

void Entity::AStar(int x1, int y1, int x2, int y2, int** map){
    double **F = new double*[Field::sizeMap];
    for (int i = 0; i < Field::sizeMap; i++)
        F[i] = new double[Field::sizeMap];
    x1/=10;
    y1/=10;
    x2/=10;
    y2/=10;
    int current_x = x1, current_y = y1;
    for (int i = 0; i < Field::sizeMap; i++)
        for (int j = 0; j < Field::sizeMap; j++){
                F[i][j] = 0;
            }
    std::vector<std::pair<int,int>> open;
    std::vector<std::pair<int,int>> used;
    std::pair<int,int> **direction = new std::pair<int,int>*[Field::sizeMap];
    for (int i = 0; i < Field::sizeMap; i++)
        direction[i] = new std::pair<int, int>[Field::sizeMap];
    used.push_back(std::make_pair(x1,y1));
    direction[x1][y1]= std::make_pair(0,0);
    F[x1][y1] = -1;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++){
            if (x1 + i < Field::sizeMap && x1 + i >= 0  && y1 + j < Field::sizeMap && y1 + j >= 0)
            if (map[x1 + i][y1 + j] == 0){
                open.push_back(std::make_pair(x1 + i, y1 + j));
                direction[x1 + i][y1 + j] = std::make_pair(i, j);
                F[x1 + i][y1 + j] = std::sqrt((x1 + i - x2) * (x1 + i - x2) + (y1 + j - y2) * (y1 + j - y2)) +
                        std::sqrt((x1 + i - x1) * (x1 + i - x1) + (y1 + j - y1) * (y1 + j - y1));
            }
        }
    while (true){
        double min = Field::sizeMap * Field::sizeMap * Field::sizeMap;
        int temp_x = 0, temp_y = 0;
        for (int i = 0; i < open.size(); i++){
            if (F[open[i].first][open[i].second] < min){
                temp_x = open[i].first;
                temp_y = open[i].second;
                min = F[open[i].first][open[i].second];
            }
        }
        if (temp_x == x2 && temp_y == y2)
            break;
        used.push_back(std::make_pair(temp_x, temp_y));
        for (int i = 0; i < open.size();i++)
            if (open[i].first == temp_x && open[i].second == temp_y)
                open.erase(open.begin() + i);
        current_x = temp_x;
        current_y = temp_y;

        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++){
                if (current_x + i < Field::sizeMap && current_x + i >= 0  && current_y + j < Field::sizeMap && current_y + j >= 0)
                if ((map[current_x + i][current_y + j] == 0 || current_x + i == x2 && current_y + j == y2) && F[current_x + i][current_y + j] == 0){
                    open.push_back(std::make_pair(current_x + i, current_y + j));
                    direction[current_x + i][current_y + j] = std::make_pair(i, j);
                    F[current_x + i][current_y + j] = std::sqrt((current_x + i - x2) * (current_x + i - x2) + (current_y + j - y2) * (current_y + j - y2)) +
                            std::sqrt((i) * (i) + (j) * (j));
                }
            }
    }
    std::vector<std::pair<int,int>> way;
    way.push_back(std::make_pair(used[used.size() - 1].first, used[used.size() - 1].second));
    current_x = way[0].first - direction[way[0].first][way[0].second].first;
    current_y = way[0].second - direction[way[0].first][way[0].second].second;
    while(current_x != x1 || current_y != y1){
        way.push_back(std::make_pair(current_x, current_y));
        for (int i = 0; i < used.size(); i++){
            if (used[i].first == current_x && used[i].second == current_y)
            {
                int temp_x = current_x, temp_y = current_y;
                current_x -= direction[temp_x][temp_y].first;
                current_y -= direction[temp_x][temp_y].second;
                break;
            }
        }
    }
    way.push_back(std::make_pair(current_x, current_y));
    Hway = way;
    way.clear();
    used.clear();
    open.clear();
}

bool Entity::IsMoney(){
    return true;
}
