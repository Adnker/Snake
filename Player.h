#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Main_Window.h"
#include "Input.h"
using namespace std;

const int Red_Player = 0;
const int Blue_Player = 1;

const int DEAD = 0;
const int LIFE = 1;

class Player {
public:
	int CreatePlayer(class Main_Window* main_window,
		class Input* input_,class Map* map_,int flag_);
	int Updata();
	//获取预选位置的坐标
	struct Point Getyuxuan_point();
	struct Point Getjidi_point();
	//获取玩家行走路线
	vector<Point*> Getmove_point() { return move_point; }
private:
	//转化为地图中心矩形坐标
	Point* ToMapPoint(Point* point_);
	//判断玩家行走点位是否正确
	int MoveIsRight(bool flag_ = false, Point point_ = { 0,0 });
	//玩家行动
	int Movetion();
	//判断玩家是否死亡
	int IsLife();
	//存放玩家现在的技能总数及其手牌
	vector<int> skill_num;//手牌
	vector<int> skill_sum;//总数
	//训练营模式下使用单个技能
	int skill;
	//存放玩家行走路线
	vector<Point*> move_point;//已经被转化为地图点位
	//存放玩家基地
	struct Point jidi_point;
	//玩家标志
	int flag;
	//提示标志
	int flag_window;
	//玩家预选位置 -1为索引
	struct Point yuxuan_point;
	//玩家上一步 -1才是索引
	struct Point before_point;
	//Input
	class Input* input;
	//Main_Window
	class Main_Window* main_window;
	//Map
	class Map* map;
};

#endif // !PLAYER_H
