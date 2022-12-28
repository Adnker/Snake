#pragma once
#ifndef SKILLER_H
#define SKILLER_H

#include "Player.h"
#include "Map.h"

//技能标识
typedef int SKILL;
const int SKILL_FLAG_JIPAO = 1;
const int SKILL_FLAG_LUZHANG = 2;
const int SKILL_FLAG_CHUANSONG = 3;
const int SKILL_FLAG_CHUANSHEN = 4;
const int SKILL_FLAG_ZHUIJI = 5;
const int SKILL_FLAG_JIANXING = 6;
const int SKILL_FLAG_KONGZHI = 7;
const int SKILL_FLAG_HUDUN = 8;
const int SKILL_FLAG_JIAOHUAN = 9;
static const int SKILLSUM = 10;

class Skiller
{
public:
	int CreateSkiller(class Map* map);
	int Use_Skill(int index_, int player_flag_);//玩家使用技能

	class Player* GetRed_Player();//获取红方玩家
	class Player* GetBlue_Player();//获取蓝方玩家
	int Getskill_sum();//获取现在全部的技能总数
	int GetSkillSum(int index_);//获取技能对应可使用次数
	bool IsLiveSkill(int index_);//判断对应的技能是否是生存性技能
	const wchar_t* GetSkillName(int index_);//获取技能名字
	const wchar_t* Getskill_jieshao(int index);//获取技能介绍
private:
	const wchar_t* skill_name[SKILLSUM] = { L"疾跑", L"路障", L"传送", L"穿身",L"追击",L"箭行",L"控制",L"护盾",L"交换", };
	const int skill_num[SKILLSUM] = { 8,       3,       1,       2,      1,      1,      2 ,     1,      1 };
	int nolifeskill[3] = { SKILL_FLAG_ZHUIJI ,SKILL_FLAG_JIPAO ,SKILL_FLAG_JIANXING };
	int skill_sum = SKILLSUM;

	class Player* player;
	class Map* map;
	class Player* red_player;
	class Player* blue_player;

	const wchar_t* skill_jieshao[1] = { L" 路障，可以阻碍敌人的行动，使敌人的路线受阻" };

	int Skill_luzhang();
	int Skill_chuansong();
	int Skill_chuanshen();
	int Skill_zhuiji();
	int Skill_jipao();
	int Skill_jianxing();
	int Skill_kongzhi();
	int Skill_hudun();
	int Skill_jiaohuan();
};

#endif