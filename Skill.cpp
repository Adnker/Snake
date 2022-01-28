#include "Skill.h"
#pragma message("Loading skill.cpp")

Skiller::~Skiller()
{
	delete red_player;
	delete blue_player;
}
int Skiller::CreateSkiller(Map* map_)
{
	red_player = new Player();
	blue_player = new Player();
	map = map_;
	return 0;
}

const wchar_t* Skiller::Getskill_name(int index)
{
	if (index == -1) {
		return L"空";
	}
	//大于现有技能总数超出索引
	if (index > skill_sum) { return 0; }
	index--;
	return skill_name[index];
}

int Skiller::Getskill_flag_sum(int index_)
{
	return skill_flag_sum[index_ - 1];
}

int Skiller::Getskill_sum()
{
	return skill_sum;
}

Player* Skiller::GetRed_Player()
{
	return red_player;
}

Player* Skiller::GetBlue_Player()
{
	return blue_player;
}

int Skiller::IsLiveSkill(int skill_flag_)
{
	//遍历生存性技能的数组寻找是否在数组中
	for (int i : skill_flag_live) {
		if (i == skill_flag_) {
			return false;
		}
	}
	return true;
}

int Skiller::PlayerChoise(int flag_player_,bool flag_)
{
	if (flag_) {
		if (flag_player_ == Red_Player) {
			player = blue_player;
		}
		else {
			player = red_player;
		}
		//判断点位是否被占用
		if (map->GetMapState(&player->player->yuxuan_point).zhan_Point == NONE) { return true; }
		else { return false; }
	}
	else {
		if (flag_player_ == Red_Player) {
			player = red_player;
		}
		else {
			player = blue_player;
		}
		//判断点位是否被占用
		if (map->GetMapState(&player->yuxuan_point).zhan_Point == NONE) { return true; }
		else { return false; }
	}
}

#pragma message("skill.cpp is loaded")