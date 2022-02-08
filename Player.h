#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Input.h"
#include "Main_Window.h"
#include "Skill.h"
using namespace std;

//用于标识玩家的行动点位
//保存索引
struct Move_point {
	/*
	* flag = 特殊标识
	* JIDI 基地特俗标识
	* QUYU 区域特殊标识
	* NULL 移动 无特殊标识
	* >0 待定
	*/
	Move_point(Point point_, int flag_) {
		point = new Point(point_);
		flag = flag_;
	}
	struct Point* point;
	int flag;
};

//蓝方玩家标识
const int Red_Player = 0;
//红方玩家标识
const int Blue_Player = 1;

//死亡
const int DEAD = 0;
//存活
const int LIFE = 1;

class Player{
public:
	friend class Skiller;
	int CreatePlayer(class Main_Window* main_window_, class Input* input_, class Map* map_, class Player* player_,
		class Skiller* skiller_, int flag_);
	int Updata();
	void UpdataSum();//更新玩家的移动和技能次数
	int Clear();//重置玩家
	Point Getyuxuan_point();//获取玩家预选点位
	Point JidiToMap(struct Move_point* point_);//将基地的索引坐标转化为地图坐标
	Point ToMapPoint(Point* point_);//将索引转化为地图坐标
	vector<int>* Getskill();//获取玩家技能
	int Getskill_sum(int index = 0);//获取玩家对应技能的可使用次数
	vector<Move_point*>* GetMove_point();//获取玩家移动数组
	int Changeskill(int index);//修改玩家的技能选择
	int Getskill_num(int index_);//获取玩家技能对应的可使用次数
	string Getpicture_name();//获取玩家图片名字
	bool SkillNeedShow();//获取玩家的技能是否需要绘制
	int ShowSkill_index();//获取玩家需要展示的技能的索引
	SDL_Rect ShowSkill_rect();//获取玩家需要展示的技能矩形
	int CreateAllSkill();//为玩家分发技能 只在竞技模式中使用
	int AddSkill();//为玩家分发技能 只在竞技模式中使用
private:
	Point* GetBeforePoint();//获取玩家上一个可用点位
	int CanMove();//判断玩家是否能继续移动
	int MoveIsRight(bool flag_ = false, Point point_ = { -1,-1 });//判断玩家选择的点位是否正确 flag_是否是外来点位
	int Movetion(int flag_ = false);//玩家选择移动
	int Skill(int index_ = 0);//玩家选择使用技能
	int IsLife();//玩家是否存活
	int Change_skill_state(int flag);//修改skill_state的状态


	int flag;//玩家标识，标明玩家此对象是红方还是蓝方
	int window_time;//用于记录玩家提示窗口的显示时间
	int skill_state = -1;//用于记录玩家技能展示的状态 -1时不展示 > -1 时展示且其为需要展示的技能索引
	int skill_num;//保存玩家可使用技能的次数
	int move_num;//保存玩家可移动的次数
	Point yuxuan_point;//保存玩家预选点位
	vector<int> skill;//保存玩家的技能
	vector<int> skill_sum;//保存玩家技能对应的可使用次数
	vector<int> skill_all;//保存玩家技能卡堆剩余技能
	std::string picture_name;//保存玩家的图片路径

	/*
	* flag:
	* = 0 表示无特殊意义
	* = -1 表示基地点位
	* = -2 表示区域点位
	* > 0 待定
	* 
	* 第一个点位必定是基地
	*/
	vector<struct Move_point*> move_point;//保存玩家行动路线

	//class
	class Input* input;
	class Main_Window* main_window;
	class Map* map;
	class Player* player;//敌人
	class Skiller* skiller;
};

#endif // !PLAYER_H
