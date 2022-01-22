#include "Map.h"
#include "Input.h"

int Map::CreateMap()
{
    huihe = 0;
    return 0;
}

int Map::Update(Point *point_)
{
    huihe++;
    std::cout << huihe << std::endl;
    map[point_->x - 1][point_->y - 1].zhan_Point = ZHAN;
    return 0;
}

int Map::Gethuihe()
{
    return huihe;
}

Map_Point Map::GetMapState(Point* point_)
{
    return map[point_->x - 1][point_->y - 1];
}
