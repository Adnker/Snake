#include "Skill.h"
#include "Skill_flag.h"
#include "myMath.h"

int Skiller::Use_Skill(int skill_flag_, int flag_player_)
{
	//每个技能函数都要过程完整
	//每个技能函数都要对应是否更新回合
	switch (skill_flag_) {
	case skill_flag_jipao:
		return skill_jipao(flag_player_);
	case skill_flag_luzhang:
		return skill_luzhang(flag_player_);
	case skill_flag_chuangsong:
		return skill_chuangsong(flag_player_);
	case skill_flag_kongzhi:
		return skill_kongzhi(flag_player_);
	case skill_flag_jiaohuan:
		return skill_jiaohuan(flag_player_);
	case skill_flag_chuanshen:
		return skill_chuanshen(flag_player_);
	case skill_flag_zhuiji:
		return skill_zhuiji(flag_player_);
	}
	return 0;
}

int Skiller::skill_jipao(int flag_player_)
{
	PlayerChoise(flag_player_);
	player->move_num++;
	return true;
}

int Skiller::skill_luzhang(int flag_player_)
{
	//固定操作
	if (!PlayerChoise(flag_player_)) { return false; }
	//声明特殊标识
	Point* temp_point = new Point(QUYU, player->quyu_point.size());
	player->move_point.emplace_back(temp_point);


	//添加行动
	//将玩家预选技能位置转化为区域格式地图坐标位置
	Point* temp_point1 = player->ToquyuPoint(&player->yuxuan_point);
	//创建新的点位 分配内存
	QuYu* temp_quyu = new QuYu(skill_flag_luzhang, temp_point1->x, temp_point1->y);
	//在ToquyuPoint()中分配的内存，由此进行回收
	delete temp_point1;
	//将点位加入玩家的区域缓冲区
	player->quyu_point.emplace_back(temp_quyu);


	//固定操作
	player->move_num--;//玩家不可在移动
	map->Updata(&player->yuxuan_point, flag_player_, QUYU_ZHAN, true);//将地图对应的点位设置为区域占用
	player->player->UpdataSum();	//更新敌人移动次数和技能次数
	return true;
}

int Skiller::skill_chuangsong(int flag_player_)
{
	if (!PlayerChoise(flag_player_)) { return false; }
	//声明特殊标识
	Point* temp_point = new Point(JIDI, player->jidi_point.size());
	player->move_point.emplace_back(temp_point);//将特殊标识加入缓冲区


	//添加行动
	//将玩家预选技能位置转化为区域格式地图坐标位置
	Point* temp_point1 = player->TojidiPoint(&player->yuxuan_point);
	player->jidi_point.emplace_back(temp_point1);
	player->before_point = player->MapToIndex(temp_point1);


	//固定操作
	player->move_num--;//玩家不可在移动
	map->Updata(&player->yuxuan_point, flag_player_, ZHAN, true);//将地图对应的点位设置为区域占用
	player->player->UpdataSum();//更新敌人移动次数和技能次数
	return true;
}

int Skiller::skill_kongzhi(int flag_player_)
{
	//获取相反玩家
	if (!PlayerChoise(flag_player_,true)) { return false; }

	//更新相反玩家的移动和技能次数
	player->UpdataSum();
	//修改相反玩家的预选位置
	Point temp_point = player->yuxuan_point;
	player->yuxuan_point = player->player->yuxuan_point;
	//调用相反玩家的移动函数
	if (!player->Movetion(true)) { 
		player->yuxuan_point = temp_point;
		return false;
	}
	player->yuxuan_point = temp_point;

	//固定操作
	player->player->move_num--;//玩家不可在移动
	player->UpdataSum();//更新敌人移动次数和技能次数
	return true;
}

int Skiller::skill_jiaohuan(int flag_player_)
{
	PlayerChoise(flag_player_);

	//将对方的基地数组加入上一步
	Point* temp_point = player->ToMapPoint(&player->player->before_point);
	player->jidi_point.emplace_back(temp_point);
	Point* temp_point1 = player->ToMapPoint(&player->before_point);
	player->player->jidi_point.emplace_back(temp_point1);
	//分别将两个玩家的移动数组加入特殊标识
	Point* temp_point2 = new Point(JIDI, player->jidi_point.size() - 1);
	player->move_point.emplace_back(temp_point2);
	Point* temp_point3 = new Point(JIDI, player->player->jidi_point.size() - 1);
	player->player->move_point.emplace_back(temp_point3);

	//固定操作
	player->move_num--;//玩家不可在移动
	map->Updatahuihe();//更新回合
	player->player->UpdataSum();//更新敌人移动次数和技能次数
	return true;
}

int Skiller::skill_chuanshen(int flag_player_)
{
	PlayerChoise(flag_player_);

	Point* temp_before = player->ToMapPoint(&player->before_point);
	Point* temp_yuxuan = player->ToMapPoint(&player->yuxuan_point);
	//判断预选位置是否在自己位置的半径范围
	//yuxuan_point and before
	if (distance((double)temp_before->x, (double)temp_before->y,
		(double)temp_yuxuan->x, (double)temp_yuxuan->y) > 199) {
		return false;
	}
	delete temp_before;

	//创建新的点位
	Point* temp_point = player->ToMapPoint(&player->yuxuan_point);
	//将点位加入到move_point中
	player->move_point.emplace_back(temp_point);

	//固定操作
	player->move_num--;//玩家不可在移动
	map->Updata(&player->yuxuan_point, flag_player_, ZHAN, true);//更新回合
	player->player->UpdataSum();//更新敌人移动次数和技能次数
	return true;
}

int Skiller::skill_zhuiji(int flag_player_)
{
	if (!PlayerChoise(flag_player_)) { return false; }

	//先获取自己的预选位置并转化为中心点位
	//获取敌人的上一步
	//判断距离是否正确
	Point* temp_before = player->ToMapPoint(&player->player->before_point);
	Point* temp_yuxuan = player->ToMapPoint(&player->yuxuan_point);
	//yuxuan and player->before
	if(distance((double)temp_before->x, (double)temp_before->y,
		(double)temp_yuxuan->x, (double)temp_yuxuan->y) > 199) {
		return false;
	}
	delete temp_before;

	//创建新的点位加入基地数组
	Point* temp_point = new Point(JIDI, player->jidi_point.size());
	player->move_point.emplace_back(temp_point);

	//将对应的点位转化为基地格式并加入基地数组
	Point* temp_point1 = player->TojidiPoint(&player->yuxuan_point);
	player->jidi_point.emplace_back(temp_point1);
	player->before_point = player->MapToIndex(temp_point1);

	//固定操作
	//player->move_num--;//玩家要再移动一次移动
	map->Updata(&player->yuxuan_point, flag_player_, ZHAN,false);
	player->player->UpdataSum();//更新敌人移动次数和技能次数
	return true;
}
