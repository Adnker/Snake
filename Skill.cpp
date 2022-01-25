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

int Skiller::Use_Skill(int skill_flag_, int flag_player_)
{
	switch (skill_flag_) {
	case skill_flag_jipao:
		return skill_jipao(flag_player_);
	case skill_flag_luzhang:
		return skill_luzhang(flag_player_);
	case skill_flag_chuangsong:
		return skill_chuangsong(flag_player_);
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

Player* Skiller::GetRed_Player()
{
	return red_player;
}

Player* Skiller::GetBlue_Player()
{
	return blue_player;
}

int Skiller::PlayerChoise(int flag_player_)
{
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

int Skiller::skill_jipao(int flag_player_)
{
	PlayerChoise(flag_player_);
	player->move_flag++;
	return true;
}

int Skiller::skill_luzhang(int flag_player_)
{
	//固定操作
	if (!PlayerChoise(flag_player_)) { return false; }
	//声明特殊标识
	Point* temp_point = new Point(QUYU,0);
	player->move_point.emplace_back(temp_point);


	//添加行动
	//将玩家预选技能位置转化为区域格式地图坐标位置
	Point* temp_point1 = player->ToquyuPoint(&player->yuxuan_point);
	//创建新的点位 分配内存
	QuYu* temp_quyu = new QuYu(skill_flag_luzhang, temp_point1->x, temp_point1->y);
	//将点位加入玩家的区域缓冲区
	player->quyu_point.emplace_back(temp_quyu);


	//固定操作
	player->move_flag--;//玩家不可在移动
	map->Update(&player->yuxuan_point, flag_player_, true);//将地图对应的点位设置为区域占用
	player->player->UpdataSum();	//更新敌人移动次数和技能次数
	return true;
}

int Skiller::skill_chuangsong(int flag_player_)
{
	if (!PlayerChoise(flag_player_)) { return false; }
	//声明特殊标识
	Point* temp_point = new Point(JIDI, 0);
	player->move_point.emplace_back(temp_point);//将特殊标识加入缓冲区


	//添加行动
	//将玩家预选技能位置转化为区域格式地图坐标位置
	Point* temp_point1 = player->TojidiPoint(&player->yuxuan_point);
	player->jidi_point.emplace_back(temp_point1);


	//固定操作
	player->move_flag--;//玩家不可在移动
	map->Update(&player->yuxuan_point, flag_player_, true);//将地图对应的点位设置为区域占用
	player->player->UpdataSum();	//更新敌人移动次数和技能次数
	return true;
}
#pragma message("skill.cpp is loaded")