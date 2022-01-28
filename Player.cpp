#include "Player.h"
#include "Map.h"
#include "myMath.h"
#pragma message("Loading player.cpp")

const int TOO_LONG = 2;
const int THOUGH = 3;
const int NOPOINT = 4;

void Player::Clear()
{
	quyu_point.clear();
	skill_flag = -1;
	move_num = 1;
	skill_num = 1;
	move_point.clear();
	jidi_point.clear();
	flag_window = 0;
	yuxuan_point = Point_None;
	before_point = Point_None;
}

int Player::CreatePlayer(Main_Window* main_window_, Input* input_, Map* map_, Player* player_,
	Skiller* skiller_, int flag_)
{
	//复制class
	input = input_;
	main_window = main_window_;
	map = map_;
	flag = flag_;
	player = player_;
	Point* temp_point = new Point(0, 0);
	jidi_point.emplace_back(temp_point);
	skiller = skiller_;
	if (main_window->GetGameModel() == FrightModel) {
		CreateSkillSum();
	}

	return 0;
}

int Player::Updata()
{
	if (map->Gethuihe() % 10 != 0) {
		flag_add = false;
	}
	for (int i = 0; i < 3; i++) {
		if (hand_skill_flag->at(i) == -1 && map->Gethuihe() % 10 == 0 && flag_add == false) {
			ChangeHand();
			flag_add = true;
			break;
		}
	}
	if (flag_window > 0) {
		flag_window++;
	}
	if (flag_window >= 100) {
		flag_window = 0;
	}

	//更新玩家操作
	if (map->Gethuihe() > 2 && map->Gethuihe() % 2 == flag) {
		if (IsLife() == DEAD) {
			main_window->GameIsEnd(flag);
			return 0;
		}
	}
	//红色玩家
	if (flag == Red_Player)
	{
		//预选位置向上移动
		if (input->GetKeyState(SDL_SCANCODE_W) == Key_Down)
		{
			yuxuan_point.y--;
		}
		//预选位置向下移动
		else if (input->GetKeyState(SDL_SCANCODE_S) == Key_Down)
		{
			yuxuan_point.y++;
		}
		//预选位置向左移动
		else if (input->GetKeyState(SDL_SCANCODE_A) == Key_Down)
		{

			yuxuan_point.x--;
		}
		//预选位置向右移动
		else if (input->GetKeyState(SDL_SCANCODE_D) == Key_Down)
		{
			yuxuan_point.x++;
		}
		//选择
		//选择结束时记得更新地图
		//移动
		else if (input->GetKeyState(SDL_SCANCODE_G) == Key_Down) { Movetion(); }
		//技能
		else if (input->GetKeyState(SDL_SCANCODE_H) == Key_Down) {
			if (main_window->GetGameModel() == FrightModel) {
				Skill(1);
			}
			else {
				Skill();
			}
		}
		//技能
		else if (input->GetKeyState(SDL_SCANCODE_J) == Key_Down) { Skill(2); }
		//技能
		else if (input->GetKeyState(SDL_SCANCODE_K) == Key_Down) { Skill(3); }

	}
	//蓝色玩家
	else
	{
		//预选位置向上移动
		if (input->GetKeyState(SDL_SCANCODE_UP) == Key_Down)
		{
			yuxuan_point.y--;
		}
		//预选位置向下移动
		else if (input->GetKeyState(SDL_SCANCODE_DOWN) == Key_Down)
		{
			yuxuan_point.y++;
		}
		//预选位置向左移动
		else if (input->GetKeyState(SDL_SCANCODE_LEFT) == Key_Down)
		{
			yuxuan_point.x--;
		}
		//预选位置向右移动
		else if (input->GetKeyState(SDL_SCANCODE_RIGHT) == Key_Down)
		{
			yuxuan_point.x++;
		}
		//投降键
		else if (input->GetKeyState(SDL_SCANCODE_KP_9) == Key_Keep) {
			main_window->GameIsEnd(flag);
			return 0;
		}
		//选择
		//选择结束时记得更新地图
		//移动
		else if (input->GetKeyState(SDL_SCANCODE_KP_0) == Key_Down) { Movetion(); }
		//技能
		else if (input->GetKeyState(SDL_SCANCODE_KP_1) == Key_Down) { 
			if (main_window->GetGameModel() == FrightModel) {
				Skill(1);
			}
			else {
				Skill();
			}
		}
		//技能
		else if (input->GetKeyState(SDL_SCANCODE_KP_2) == Key_Down) { Skill(2); }
		//技能
		else if (input->GetKeyState(SDL_SCANCODE_KP_3) == Key_Down) { Skill(3); }
	}
	//检验预选位置是否超出范围
	if (yuxuan_point.x < 1) { yuxuan_point.x = 1; }
	else if (yuxuan_point.x > 7) { yuxuan_point.x = 7; }
	else if (yuxuan_point.y < 1) { yuxuan_point.y = 1; }
	else if (yuxuan_point.y > 7) { yuxuan_point.y = 7; }

	return 0;
}

void Player::UpdataSum()
{
	move_num = 1;
	skill_num = 1;
}

Point Player::Getyuxuan_point()
{
	//将预选位置的左边转化为窗口坐标
	if (flag == Red_Player)
	{
		return { yuxuan_point.x * 100 - 30,yuxuan_point.y * 100 - 30 };
	}
	else
	{
		return { yuxuan_point.x * 100 - 90,yuxuan_point.y * 100 - 30 };
	}
}

const vector<Point*>* Player::Getjidi_point()
{
	return &jidi_point;
}

const vector<Point*>* Player::Getmove_point()
{
	return &move_point;
}

const vector<QuYu*>* Player::Getquyu_point()
{
	return &quyu_point;
}


void Player::Changeskill_flag(int skill_flag_)
{
	skill_flag = skill_flag_;
	skill_flag_num = skiller->Getskill_flag_sum(skill_flag);
}

int Player::Getskill_flag()
{
	return skill_flag;
}

int Player::Getskill_flag_num()
{
	return skill_flag_num;
}

int Player::CreateSkillSum()
{
	int max = skiller->Getskill_sum();
	all_skill_sum = new vector<int>;
	//将技能标识添加进卡牌堆
	for (int i = 1; i < max + 1; i++) {
		all_skill_sum->emplace_back(i);
	}
	hand_skill_flag = new vector<int>;
	hand_skill_num = new vector<int>;

	for (int i = 0; i < 3; i++) {
		int rands = main_window->rander->GetARand(max - i);
		rands--;
		//将对应的技能加入手牌
		hand_skill_flag->emplace_back(all_skill_sum->at(rands));
		hand_skill_num->emplace_back(skiller->Getskill_flag_sum(all_skill_sum->at(rands)));
		//在总的牌堆中删除加入手牌的技能牌
		all_skill_sum->erase(all_skill_sum->begin() + rands, all_skill_sum->begin() + rands + 1);
	}

	return 0;
}

int Player::ChangeHand()
{
	if (map->Gethuihe() % 10 == 0) {
		//判断牌堆中是否还有卡牌
		if (all_skill_sum->size() < 1) { return false; }
		int rands = main_window->rander->GetARand(all_skill_sum->size() - 1);
		rands--;
		int index = 0;
		for (int i = 0; i < 3; i++) {
			if (hand_skill_num->at(i) < 1) { index = i; break; }
		}
		//将对应的技能加入手牌
		int temp_skill = all_skill_sum->at(rands);
		hand_skill_flag->at(index) = temp_skill;
		hand_skill_num->at(index) = skiller->Getskill_flag_sum(temp_skill);
		//在总的牌堆中删除加入手牌的技能牌
		all_skill_sum->erase(all_skill_sum->begin() + rands, all_skill_sum->begin() + rands + 1);
		return true;
	}
	return false;
}

const vector<int>* Player::GetHand()
{
	return hand_skill_flag;
}

int Player::GetHandNum(int index_)
{
	return hand_skill_num->at(index_);
}

Point* Player::ToMapPoint(Point* point_)
{
	Point* temp = new Point(point_->x * 100 - 50, point_->y * 100 - 50);
	return temp;
}

Point* Player::TojidiPoint(Point* point_)
{
	Point* temp = new Point(point_->x * 100 - 75, point_->y * 100 - 75);
	return temp;
}

Point* Player::ToquyuPoint(Point* point_)
{
	Point* temp = new Point(point_->x * 100 - 60, point_->y * 100 - 60);
	return temp;
}

Point Player::MapToIndex(Point* point_)
{
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (i * 100 < point_->x && (i + 1) * 100 > point_->x && j * 100 < point_->y && (j + 1) * 100 > point_->y) {
				return { i + 1,j + 1 };
			}
		}
	}
	return { -1,0 };
}

Point Player::MapToMap(Point* point_)
{
	//将其转化为地图索引+1
	Point temp_point = MapToIndex(point_);
	//转化为中心点位
	temp_point.x = temp_point.x * 100 - 50;
	temp_point.y = temp_point.y * 100 - 50;
	return temp_point;
}

int Player::CanMove()
{
	skill_num--;
	move_num--;
	//还有移动次数时
	if (move_num >= 1) {
		//更新地图 但不更新回合
		map->Updata(&yuxuan_point, flag, ZHAN, false);
		return true;
	}
	//没有移动次数和技能次数时
	else if (move_num < 1 && skill_num < 1) {
		//更新敌人的移动和技能次数
		//更新地图
		player->UpdataSum();
		map->Updata(&yuxuan_point, flag, ZHAN, true);
		return false;
	}
}

int Player::MoveIsRight(bool flag_, Point point_)
{
	Point* temp;
	if (flag_) {
		if (point_.x < 1 || point_.x > 7 || point_.y < 1 || point_.y > 7) { return NOPOINT; }
		temp = &point_;
	}
	else { temp = &yuxuan_point; }

	//最后一个点位 赋值
	int index = move_point.size() - 1;
	Point before = *move_point.at(index);
	//判断标识
	if (before.x == JIDI) {
		before = MapToMap(jidi_point.back());//将基地点位转化为中心点位
	}
	else if (before.x == QUYU) {
		//向前遍历知道找到可使用的点位
		while (index >= 0) {
			index--;
			before = *move_point.at(index);
			if (before.x == JIDI) {
				before = MapToMap(jidi_point.at(before.y));
				break;
			}
			else if (before.x > QUYU) {
				break;
			}
		}
	}
	Point* now = ToMapPoint(temp);//现在的点位
	//计算两点之间的距离是否是正确的
	int distance = static_cast<int>(
		sqrt((
			(before.x - now->x) * (before.x - now->x) +
			(before.y - now->y) * (before.y - now->y)
			))
		);
	if (distance > 199) { return TOO_LONG; }
	//是否穿线
	else if (map->IsThoughLine(
		before_point.x - 1, temp->y - 1, temp->x - 1, before_point.y - 1)
		) {
		return THOUGH;
	}
	else { return true; }
}

//flag = false
int Player::Movetion(int flag_)
{
	//提示窗口大小
	SDL_Rect text_rect = { Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 };
	//判断是否是玩家的回合
	if (map->Gethuihe() % 2 == flag || flag_)
	{
		//如果没有移动次数
		if (move_num < 1) {
			if (flag_window == 0 && !flag_) {
				main_window->Player_Window(L"不可移动", text_rect, flag_window);
			}
			return false;
		}
		//地图点位未被占用
		if (map->GetMapState(&yuxuan_point).zhan_Point == NONE)
		{
			//基地还没确定，优先确定基地
			if (!(*jidi_point[0]).x) {
				map->Updata(&yuxuan_point, flag, ZHAN, true);//更新地图，回合增加
				//将预选点位转化为地图点位，并保存
				jidi_point[0]->x = yuxuan_point.x * 100 - 75;
				jidi_point[0]->y = yuxuan_point.y * 100 - 75;
				before_point = yuxuan_point;
				//复制
				Point* point = new Point(*jidi_point[0]);
				point->x += 25;
				point->y += 25;
				move_point.emplace_back(point);//将点位加入
				return true;
			}
			else {
				switch (MoveIsRight()) {
				case true:
					before_point = yuxuan_point;
					move_point.emplace_back(ToMapPoint(&yuxuan_point));//将点位加入
					CanMove();
					return true;
				case TOO_LONG:
					//提示玩家距离过长
					if (flag_window == 0 && !flag_) {
						main_window->Player_Window(L"距离过长", text_rect, flag_window);
					}
					return false;
				case THOUGH:
					//提示玩家禁止穿线
					if (flag_window == 0 && !flag_) {
						main_window->Player_Window(L"禁止穿线", text_rect, flag_window);
					}
					return false;
				}
			}
		}
		else
		{
			//点位被占用
			if (flag_window == 0 && !flag_) {
				main_window->Player_Window(L"点位被占", text_rect, flag_window);
			}
			return false;
		}
	}
	else {
		if (flag_window == 0 && !flag_) {
			//轮到敌人
			main_window->Player_Window(L"敌人回合", text_rect, flag_window);
		}
		return false;
	}
}

int Player::Skill(int flag_)
{
	//提示窗口大小
	SDL_Rect text_rect = { Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 };
	//基地还未放置无法使用技能
	if (jidi_point[0]->x == 0) {
		main_window->Player_Window(L"基地未放", text_rect, flag_window);
	}
	//技能使用次数少
	else if (skill_num < 1) {
		main_window->Player_Window(L"不可使用", text_rect, flag_window);
	}
	//敌人的回合
	else if (map->Gethuihe() % 2 != flag) {
		main_window->Player_Window(L"敌人回合", text_rect, flag_window);
	}
	else {
		if (main_window->GetGameModel() != FrightModel && skill_flag_num < 1) {
			main_window->Player_Window(L"使用失败", text_rect, flag_window);
			return false;
		}
		else if (main_window->GetGameModel() == FrightModel && hand_skill_num->at(flag_ - 1) < 1) {
			main_window->Player_Window(L"使用失败", text_rect, flag_window);
			return false;
		}
		//调用技能使用函数
		//是否更新回合在技能使用中已经调用
		int temp_skill_flag = skill_flag;
		if (flag_ > 0) {
			temp_skill_flag = hand_skill_flag->at(flag_ - 1);
		}
		if (skiller->Use_Skill(temp_skill_flag, flag)) { 
			//回合技能数和技能总次数均-1
			skill_num--;
			if (main_window->GetGameModel() == FrightModel) {
				hand_skill_num->at(flag_ - 1)--;
				if (hand_skill_num->at(flag_ - 1) < 1) {
					hand_skill_flag->at(flag_ - 1) = -1;
				}
			}
			else {
				skill_flag_num--;
			}
		}
		else { main_window->Player_Window(L"使用失败", text_rect, flag_window); }
	}
	return 0;
}

/*
* (x-1,y-1)(x,y-1)(x+1,y-1)
* (x-1,y)  (x,y)  (x+1,y)
* (x-1,y+1)(x,y+1)(x+1,y+1)
*/
int Player::IsLife()
{
	bool isLife = DEAD;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (map->GetMapStatexy(before_point.x + i, before_point.y + j).zhan_Point == NONE) {
				if (MoveIsRight(true, { before_point.x + i,before_point.y + j }) == true) {
					isLife = LIFE;
				}
			}
		}
	}
	if (main_window->GetGameModel() == FrightModel) {
		for (int i = 0; i < 3; i++) {
			if (skiller->IsLiveSkill(hand_skill_flag->at(i)) && hand_skill_num->at(i) > 0) {
				isLife = LIFE;
			}
		}
	}
	else {
		if (skiller->IsLiveSkill(skill_flag) && skill_flag_num > 0) {
			isLife = LIFE;
		}
	}
	return isLife;
}

#pragma message("player.cpp is loaded")