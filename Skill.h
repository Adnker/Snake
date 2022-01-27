#pragma once
#ifndef SKILL_H
#define SKILL_H
#include "Player.h"
#include "Map.h"
#include "Skill_flag.h"

#pragma message("Loading skill...")

class Skiller
{
public:
	~Skiller();
	int CreateSkiller(class Map* map);
	//技能筛选器 使用技能
	int Use_Skill(int skill_flag_, int flag_player);
	//获取技能名字 自动转化为索引
	const wchar_t* Getskill_name(int index);
	//获取技能总次数
	int Getskill_flag_sum(int index_);
	//获取技能总数
	int Getskill_sum();
	//获取玩家指针
	class Player* GetRed_Player();
	class Player* GetBlue_Player();
	//判断技能是否是生存性技能
	int IsLiveSkill(int skill_flag_);
private:
	//筛选 将player设置为对应的玩家
	//返回值为对应使用预选点位是否被占用
	//flag_  = false 是否反转玩家
	int PlayerChoise(int flag_player_, bool flag_ = false);
	//存放技能名字
	const wchar_t* skill_name[7] = { L"疾跑",L"路障",L"传送",L"控制",L"交换",L"穿身",L"追击" };
	//存放技能使用次数
	int skill_flag_sum[7] = { 8,3,1 ,2,1 ,2,1 };
	//现有技能总数
	int skill_sum = 7;
	//不具有生存性技能
	int skill_flag_live[2] = {
		skill_flag_jipao,
		skill_flag_zhuiji
	};

	//技能函数
	int skill_jipao(int flag_player_);
	int skill_luzhang(int flag_player_);
	int skill_chuangsong(int flag_player_);
	int skill_kongzhi(int flag_player);
	int skill_jiaohuan(int flag_player_);
	int skill_chuanshen(int flag_player_);
	int skill_zhuiji(int flag_player_);

	class Map* map;
	class Player* red_player;
	class Player* blue_player;
	class Player* player;
};

#pragma message("Skill is loaded")

#endif // !SKILL_H
