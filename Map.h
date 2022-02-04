#pragma once
#ifndef MAP_H
#define MAP_H
#include "Input.h"

struct Map_Point
{
	//地图点位是否被占用
	int zhan_Point;
	//玩家标识
	int flag_player;
	//第几步
	int huihe;
};

//用于特殊标识定位
const int QUYU = -2;
const int JIDI = -1;

//地图点位区域使用，可以行走
const int QUYU_NONE = 3;
//地图点位区域占用，不可以行走
const int QUYU_ZHAN = 2;
//地图点位被占用
const int ZHAN = 1;
//地图点位未被占用
const int NONE = 0;

//地图点位无人占用
//const int Red_Player = 0;
//const int Blue_Player = 1;
const int NOONE = -1;

//空地图点位
static struct Map_Point Map_None = { NONE, NOONE , 49 };

#pragma message ("Loading Map...")
class Map {
public:
	int Clear();
	int CreateMap();
	/*  
		//point_ 坐标 自动转化为索引
		//flag_ 是否更新回合
		//flag_point_ 点位设置为什么状态
		//地图点位区域使用，可以行走
		const int QUYU_NONE = 3;
		//地图点位区域占用，不可以行走
		const int QUYU_ZHAN = 2;
		//地图点位被占用
		const int ZHAN = 1;
		//地图点位未被占用
		const int NONE = 0;
	*/
	int Updata(Point* point_, int flag_player_, int flag_point, bool flag_);
	//更新回合
	int Updatahuihe();

	//显示地图点位情况
	int Print();

	//获取回合数
	int Gethuihe();
	//获取地图点位 函数自动转化为索引（-1）
	Map_Point GetMapState(Point* point_);
	//获取地图点位 函数自动转化为索引（-1）
	Map_Point GetMapStatexy(int x, int y);
	//判断是否穿线
	bool IsThoughLine(int x1, int y1, int x2, int y2);
private:
	//回合数
	int huihe;
	//初始地图位置设定
	struct Map_Point map[7][7] = {
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None},
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None},
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None},
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None},
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None},
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None},
		{Map_None,Map_None,Map_None,Map_None,Map_None,Map_None,Map_None}
	};
};
#pragma message ("Map is loaded")

#endif // !MAP_H
