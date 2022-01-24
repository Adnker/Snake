#include "Skill.h"
#pragma message("Loading skill.cpp")
Skiller::~Skiller()
{
	delete red_player;
	delete blue_player;
}
int Skiller::CreateSkiller(Player* red_player_, Player* blue_player_)
{
	red_player = new Player();
	blue_player = new Player();
	red_player_ = red_player;
	blue_player_ = blue_player;
	return 0;
}

void Skiller::Use_Skill(int skill_flag_,int flag_player_)
{
	switch (skill_flag_) {
	case skill_flag_jipao:
		skill_jipao(flag_player_);
		break;
	case skill_flag_luzhang:
		skill_luzhang(flag_player_);
		break;
	}
}

const wchar_t* Skiller::Getskill_name(int index)
{
	//大于现有技能总数超出索引
	if (index > skill_sum) { return 0; }
	index--;
	return skill_name[index];
}

int Skiller::Getskill_sum()
{
	return skill_sum;
}

void Skiller::PlayerChoise(int flag_player_)
{
	if (flag_player_ == Red_Player) {
		player = red_player;
	}
	else {
		player = blue_player;
	}
}

int Skiller::skill_jipao(int flag_player_)
{
	PlayerChoise(flag_player_);
	player->move_flag++;
	return 0;
}

int Skiller::skill_luzhang(int flag_player_)
{
	PlayerChoise(flag_player_);
	Point* temp_point = player->ToMapPoint(&player->yuxuan_point);
	QuYu* temp_quyu = new QuYu(skill_flag_luzhang, temp_point->x, temp_point->y);
	player->quyu.emplace_back(temp_quyu);
	return 0;
}

int Skiller::skill_chuangsong(int flag_player_)
{
	PlayerChoise(flag_player_);
	Point* temp_point = new Point(0,0);
	player->move_point.emplace_back(temp_point);//将特殊标识加入缓冲区
	//将新的基地位置放入
	player->jidi_point.emplace_back(
		player->TojidiPoint(&player->yuxuan_point)
	);
	return 0;
}
#pragma message("skill.cpp is loaded")