#include "Map.h"
#include "Input.h"

int Map::CreateMap()
{
    huihe = 0;
    return 0;
}

int Map::Update(Point *point_,int flag_)
{
    huihe++;
    std::cout << huihe << std::endl;
    auto point = &map[point_->x - 1][point_->y - 1];
    point->zhan_Point = ZHAN;
    point->flag_player = flag_;
    point->huihe = huihe;
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

Map_Point Map::GetMapStatexy(int x, int y)
{
    x -= 1;
    y -= 1;
    if (x < 0 || x > 6 || y < 0 || y > 6) { return{ ZHAN,0,0 }; }
    return map[x][y];
}

bool Map::IsThoughLine(int x1, int y1,int x2,int y2)
{
    Map_Point point1 = map[x1][y1];
    Map_Point point2 = map[x2][y2];
    if (point1.huihe - point2.huihe == -2 || point1.huihe - point2.huihe == 2) {
        return true;
    }
    return false;
}
