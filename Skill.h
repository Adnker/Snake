#pragma once
#ifndef SKILL_H
#define SKILL_H
#include "Player.h"
#include "Map.h"

//疾跑技能标识
const int skill_flag_jipao = 1;
//路障技能标识
const int skill_flag_luzhang = 2;
//传送技能标识
const int skill_flag_chuangsong = 3;

#pragma message("Loading skill...")

class Skiller
{
public:
	~Skiller();
	int CreateSkiller(class Map* map);
	//技能筛选器 使用技能
	int Use_Skill(int skill_flag_,int flag_player);
	//获取技能名字 自动转化为索引
	const wchar_t* Getskill_name(int index);
	//获取技能总数
	int Getskill_sum();
	//获取玩家指针
	class Player* GetRed_Player();
	class Player* GetBlue_Player();
private:
	//筛选 将player设置为对应的玩家
	//返回值为对应使用预选点位是否被占用
	int PlayerChoise(int flag_player_);
	//技能函数
	int skill_jipao(int flag_player_);
	int skill_luzhang(int flag_player_);
	int skill_chuangsong(int flag_player_);
	//存放技能名字
	const wchar_t* skill_name[3] = { L"疾跑",L"路障",L"传送" };
	//现有技能总数
	int skill_sum = 3;
	class Map* map;
	class Player* red_player;
	class Player* blue_player;
	class Player* player;
};

#pragma message("Skill is loaded")

#endif // !SKILL_H
