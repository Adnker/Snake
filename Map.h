#pragma once
#ifndef MAP_H
#define MAP_H
#include "Input.h"

struct Map_Point
{
	bool quyu_Point;
	bool zhan_Point;
};

static struct Map_Point Map_None = { 0,0 };
const int ZHAN = 1;
const int NONE = 0;

class Map {
public:
	int CreateMap();
	int Update(Point* point_);

	//获取回合数
	int Gethuihe();
	//获取地图点位
	Map_Point GetMapState(Point* point_);
private:
	//回合数
	int huihe;
	//初始地图位置设定
	struct Map_Point map[7][7] = 
	{
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None},
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None},
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None},
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None},
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None},
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None},
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None}
	};
};

#endif // !MAP_H
