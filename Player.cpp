#include "Player.h"
#include "Map.h"
#pragma message("Loading player.cpp")

const int TOO_LONG = 2;
const int THOUGH = 3;

void Player::Clear()
{
	skill_num.clear();
	quyu.clear();
	skill = -1;
	move_flag = 1;
	skill_flag = 1;
	move_point.clear();
	jidi_point.clear();
	flag_window = 0;
	yuxuan_point = Point_None;
	before_point = Point_None;
}

int Player::CreatePlayer(Main_Window* main_window_, Input* input_, Map* map_, Player* player_, int flag_)
{
	//复制class
	input = input_;
	main_window = main_window_;
	map = map_;
	flag = flag_;
	player = player_;
	Point* temp_point = new Point(0, 0);
	jidi_point.emplace_back(temp_point);
	return 0;
}

int Player::Updata()
{
	if (flag_window > 0) { flag_window++; }
	if (flag_window >= 150) { flag_window = 0; }

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
		//投降键
		else if (input->GetKeyState(SDL_SCANCODE_Z) == Key_Keep) {
			main_window->GameIsEnd(flag);
			return 0;
		}
		//选择
		//选择结束时记得更新地图
		//移动
		else if (input->GetKeyState(SDL_SCANCODE_G) == Key_Down) { Movetion(); }
		//技能
		else if (input->GetKeyState(SDL_SCANCODE_H) == Key_Down) { Skill(); }

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
		else if (input->GetKeyState(SDL_SCANCODE_KP_9 )== Key_Keep) {
			main_window->GameIsEnd(flag);
			return 0;
		}
		//选择
		//选择结束时记得更新地图
		//移动
		else if (input->GetKeyState(SDL_SCANCODE_KP_1) == Key_Down) { Movetion(); }
		//技能
		else if (input->GetKeyState(SDL_SCANCODE_2) == Key_Down) { Skill(); }
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
	move_flag = 1;
	skill_flag = 1;
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

vector<Point*>* Player::Getjidi_point()
{
	return &jidi_point;
}

vector<Point*>* Player::Getmove_point()
{
	return &move_point;
}


void Player::ChangeSkill(int skill_)
{
	skill = skill_;
}

int Player::Getskill_flag()
{
	return skill;
}

Point* Player::ToMapPoint(Point* point_)
{
	Point* temp = new Point(point_->x * 100 - 50, point_->y * 100 - 50);
	return temp;
}

Point* Player::TojidiPoint(Point* point_)
{
	Point* temp = new Point(yuxuan_point.x * 100 - 75, yuxuan_point.y * 100 - 75);
	return temp;
}

int Player::MoveIsRight(bool flag_, Point point_)
{
	Point* temp;
	if (flag_) {
		if (point_.x < 1 || point_.x > 7 || point_.y < 1 || point_.y > 7) { return THOUGH; }
		temp = &point_;
	}
	else { temp = &yuxuan_point; }

	Point* before = move_point[move_point.size() - 1];//最后一个点位
	Point* now = ToMapPoint(temp);//现在的点位
	//计算两点之间的距离是否是正确的
	int distance = static_cast<int>(
		sqrt((
			(before->x - now->x) * (before->x - now->x) +
			(before->y - now->y) * (before->y - now->y)
			))
		);
	if (distance > 190) { return TOO_LONG; }
	else if (map->IsThoughLine(
		before_point.x - 1, temp->y - 1, temp->x - 1, before_point.y - 1)
		) {
		return THOUGH;
	}
	else { return true; }
}

int Player::Movetion()
{
	//提示窗口大小
	SDL_Rect text_rect = { Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 };
	//判断是否是玩家的回合
	if (map->Gethuihe() % 2 == flag)
	{
		//如果没有移动次数
		if (move_flag < 1) { 
			if (flag_window == 0) {
				flag_window++;
				main_window->Player_Window(L"不可移动", text_rect);
			}
			return 0;
		}
		//地图点位未被占用
		if (map->GetMapState(&yuxuan_point).zhan_Point == NONE)
		{
			//基地还没确定，优先确定基地
			if (!(*jidi_point[0]).x) {
				map->Update(&yuxuan_point, flag);//更新地图
				//将预选点位转化为地图点位，并保存
				jidi_point[0]->x = yuxuan_point.x * 100 - 75;
				jidi_point[0]->y = yuxuan_point.y * 100 - 75;
				before_point = yuxuan_point;
				//复制
				Point* point = new Point(*jidi_point[0]);
				point->x += 25;
				point->y += 25;
				move_point.emplace_back(point);//将点位加入
			}
			else {
				switch (MoveIsRight()) {
				case 1:
					map->Update(&yuxuan_point, flag);//更新地图
					before_point = yuxuan_point;
					move_point.emplace_back(ToMapPoint(&yuxuan_point));//将点位加入
					skill_flag--;
					move_flag--;
					player->UpdataSum();//更新敌人的移动和技能次数
					break;
				case TOO_LONG:
					//提示玩家距离过长
					if (flag_window == 0) {
						flag_window++;
						main_window->Player_Window(L"距离过长", text_rect);
					}
					break;
				case THOUGH:
					//提示玩家禁止穿线
					if (flag_window == 0) {
						flag_window++;
						main_window->Player_Window(L"禁止穿线", text_rect);
					}
					break;
				}
			}
		}
		else
		{
			//点位被占用
			if (flag_window == 0) {
				flag_window++;
				main_window->Player_Window(L"点位被占", text_rect);
			}
		}
	}
	else {
		if (flag_window == 0) {
			flag_window++;
			//轮到敌人
			main_window->Player_Window(L"敌人回合", text_rect);
		}
	}
	return 0;
}

int Player::Skill()
{
	//提示窗口大小
	SDL_Rect text_rect = { Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 };
	if (jidi_point[0]->x == 0) { main_window->Player_Window(L"基地未放", text_rect); }
	else if (skill_flag < 1) { main_window->Player_Window(L"不可使用", text_rect); }
	else {
		
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
			if (map->GetMapStatexy(before_point.x + i, before_point.y + j).zhan_Point == NONE){
				if (MoveIsRight(true, { before_point.x + i,before_point.y + j }) == 1) {
					isLife = LIFE;
				}
			}
		}
	}
	return isLife;
}

#pragma message("player.cpp is loaded")