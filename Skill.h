#pragma once
#ifndef SKILLER_H
#define SKILLER_H

#include "Player.h"
#include "Map.h"

//技能标识
typedef int SKILL;
const int SKILL_FLAG_LUZHANG = 1;
const int SKILL_FLAG_CHUANSONG = 2;
const int SKILL_FLAG_CHUANSHEN = 3;
const int SKILL_FLAG_ZHUIJI = 4;
const int SKILL_FLAG_JIPAO = 5;

class Skiller
{
public:
	int CreateSkiller(class Map* map);
	int GetSkillSum(int index_);//获取技能对应可使用次数
	const wchar_t* GetSkillName(int index_);//获取技能名字
	int Use_Skill(int index_, int player_flag_);//玩家使用技能
	class Player* GetRed_Player();//获取红方玩家
	class Player* GetBlue_Player();//获取蓝方玩家
	int Getskill_sum();//获取现在全部的技能总数
	bool IsLiveSkill(int index_);//判断对应的技能是否是生存性技能
private:
	const wchar_t* skill_name[5] = { L"路障", L"传送", L"穿身",L"追击",L"疾跑" };
	const int skill_num[5] = { 3,1,2,1 ,8 };
	int skill_sum = 5;
	int nolifeskill[2] = { SKILL_FLAG_ZHUIJI ,SKILL_FLAG_JIPAO };

	class Player* player;
	class Map* map;
	class Player* red_player;
	class Player* blue_player;

	int Skill_luzhang();
	int Skill_chuansong();
	int Skill_chuanshen();
	int Skill_zhuiji();
	int Skill_jipao();
};

#endif