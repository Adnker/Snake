#include "Skiller.h"

int Skiller::CreatSkiller(Player* red_player_, Player* blue_player_)
{
	red_player = red_player_;
	blue_player = blue_player_;
}

int Skiller::GetSkillSum(int index_)
{
	return skill_sum[index_];
}

const wchar_t* Skiller::GetSkillName(int index_)
{
	return skill_name[index_];
}
