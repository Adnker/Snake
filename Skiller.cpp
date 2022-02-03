#include "Skiller.h"

int Skiller::CreateSkiller(Map* map_)
{
	map = map_;
	red_player = new Player();
	blue_player = new Player();
	return true;
}

int Skiller::GetSkillSum(int index_)
{
	return skill_num[index_];
}

const wchar_t* Skiller::GetSkillName(int index_)
{
	return skill_name[index_];
}

int Skiller::Use_Skill(int index_, int player_flag_)
{
	switch (index_)
	{
	default:
		break;
	}
	return true;
}

bool Skiller::IsLiveSkill(int index_) {
	for (int i : nolifeskill) {
		if (index_ == i) {
			return false;
		}
	}
	return true;
}

class Player* Skiller::GetRed_Player() {
	return red_player;
}

class Player* Skiller::GetBlue_Player() {
	return blue_player;
}
