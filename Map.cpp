#include "Map.h"
#include "Input.h"

int Map::Clear()
{
	huihe = 1;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			map[i][j] = Map_None;
		}
	}
	return 0;
}

int Map::CreateMap()
{
	huihe = 0;
	return 0;
}

//flag = true
int Map::Updata(Point* point_, int flag_player_,int flag_point_, bool flag_)
{
	auto point = &map[point_->x][point_->y];
	point->zhan_Point = flag_point_;
	point->flag_player = flag_player_;
	point->huihe = huihe;
	if (flag_) {
		huihe++;
	}
	Print();
	return 0;
}

int Map::Updatahuihe()
{
	huihe++;
	return 0;
}

int Map::Print()
{
	std::cout << huihe << std::endl;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (map[i][j].zhan_Point != NONE) {
				std::cout << "X£º" << i + 1 << "  Y£º" << j + 1 << std::endl;
			}
		}
	}
	return 0;
}

int Map::Gethuihe()
{
	return huihe;
}

Map_Point Map::GetMapState(Point* point_)
{
	return map[point_->x][point_->y];
}

Map_Point Map::GetMapStatexy(int x, int y)
{
	if (x < 0 || x > 6 || y < 0 || y > 6) { return{ ZHAN,0,0 }; }
	return map[x][y];
}

bool Map::IsThoughLine(int x1, int y1, int x2, int y2)
{
	Map_Point point1 = map[x1][y1];
	Map_Point point2 = map[x2][y2];
	if ((point1.huihe - point2.huihe > -2 || point1.huihe - point2.huihe < 2) &&
		point1.zhan_Point == ZHAN && point2.zhan_Point == ZHAN) {
		return true;
	}
	return false;
}
