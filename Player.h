#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Main_Window.h"
#include "Input.h"
#include "Skill.h"
using namespace std;

//区域标识
//用于标识区域
struct QuYu {
	QuYu(int skill_, int x_, int y_) {
		skill = skill_;
		x = x_;
		y = y_;
	}
	//那个技能的区域
	int skill;
	//在地图哪里 地图坐标
	int x;
	int y;
};

//蓝方玩家标识
const int Red_Player = 0;
//红方玩家标识
const int Blue_Player = 1;
//死亡
const int DEAD = 0;
//存活
const int LIFE = 1;

//特殊标识 出现特殊标识后从基地缓冲区中加载新基地
const Point Point_None = { 0,0 };
#pragma message ("Loading Player...")
class Player{
public:
	friend class Skiller;
	//重置玩家类
	void Clear();
	int CreatePlayer(class Main_Window* main_window,
		class Input* input_,class Map* map_,class Player* player_, int flag_);
	int Updata();

	//更新移动和技能的使用次数
	void UpdataSum();
	//获取预选位置的坐标 地图坐标
	struct Point Getyuxuan_point();
	//获取基地位置的坐标 地图坐标
	vector<Point*>* Getjidi_point();
	//获取玩家行走路线 地图坐标
	vector<Point*>* Getmove_point();
	//设置技能
	void ChangeSkill(int skill_);
	//获取技能标识
	int Getskill_flag();
private:
	//转化为地图中心矩形坐标
	//创建新的点位 分配内存
	//point_ = 数组索引
	Point* ToMapPoint(Point* point_);
	//转化为基地格式的地图左边
	//创建新的点位 分配内存
	Point* TojidiPoint(Point* point_);
	//判断玩家行走点位是否正确
	//flag_ = 特殊标志
	//point_ = 使用哪个点进行判断
	int MoveIsRight(bool flag_ = false, Point point_ = { 0,0 });
	//玩家行动
	int Movetion();
	//玩家使用技能
	int Skill();
	//判断玩家是否死亡
	int IsLife();
	//存放玩家现在的技能总数及其手牌
	vector<int> skill_num;//手牌
	vector<int> skill_sum;//总数
	//训练营模式下使用单个技能
	int skill = -1;
	//玩家区域
	vector<QuYu*> quyu;
	//玩家可移动次数
	int move_flag = 1;
	//玩家使用技能此时 为-1时为还未确定技能
	int skill_flag = 1;
	//存放玩家行走路线 地图坐标
	vector<Point*> move_point;//已经被转化为地图点位
	//存放玩家基地 地图坐标
	vector<Point*> jidi_point;
	//玩家标志 Red_Player = 0 Blue_Player = 1
	int flag;
	//提示标志 未被使用 = 0 使用时 > 0 && < 150
	int flag_window;
	//玩家预选位置 -1索引
	struct Point yuxuan_point;
	//玩家上一步 -1索引
	struct Point before_point;

	//class
	class Input* input;
	class Main_Window* main_window;
	class Map* map;
	class Player* player;//敌人
	class Skiller* skiller;
};
#pragma message("Player is loaded")

#endif // !PLAYER_H
