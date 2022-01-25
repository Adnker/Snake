#pragma once
#ifndef SKILL_H
#define SKILL_H
#include "Player.h"

//疾跑技能标识
const int skill_flag_jipao = 0;
//路障技能标识
const int skill_flag_luzhang = 1;
//传送技能标识
const int skill_flag_chuangsong = 2;

#pragma message("Loading skill...")

class Skiller
{
public:
	~Skiller();
	int CreateSkiller(class Player* red_player_, class Player* blue_player_);
	//技能筛选器 使用技能
	void Use_Skill(int skill_flag_,int flag_player);
	//获取技能名字 自动转化为索引
	const wchar_t* Getskill_name(int index);
	//获取技能总数
	int Getskill_sum();
private:
	//筛选 将player设置为对应的玩家
	void PlayerChoise(int flag_player_);
	//技能函数
	int skill_jipao(int flag_player_);
	int skill_luzhang(int flag_player_);
	int skill_chuangsong(int flag_player_);
	//存放技能名字
	const wchar_t* skill_name[3] = { L"疾跑",L"路障",L"传送" };
	//现有技能总数
	int skill_sum = 3;
	class Player* red_player;
	class Player* blue_player;
	class Player* player;
};

#pragma message("Skill is loaded")

#endif // !SKILL_H
