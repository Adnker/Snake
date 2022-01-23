#include "Player.h"
#include "Map.h"
#include <math.h>

const int TOO_LONG = 2;
const int THOUGH = 3;

int Player::CreatePlayer(Main_Window* main_window_, Input* input_, Map* map_, int flag_)
{
	//复制Input
	input = input_;
	main_window = main_window_;
	map = map_;
	flag = flag_;
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
		//选择
		//选择结束时记得更新地图
		else if (input->GetKeyState(SDL_SCANCODE_G) == Key_Down)
		{
			Movetion();
		}

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
		//选择
		//选择结束时记得更新地图
		else if (input->GetKeyState(SDL_SCANCODE_KP_1) == Key_Down)
		{
			Movetion();
		}
	}
	//检验预选位置是否超出范围
	if (yuxuan_point.x < 1) { yuxuan_point.x = 1; }
	else if (yuxuan_point.x > 7) { yuxuan_point.x = 7; }
	else if (yuxuan_point.y < 1) { yuxuan_point.y = 1; }
	else if (yuxuan_point.y > 7) { yuxuan_point.y = 7; }

	return 0;
}

Point Player::Getyuxuan_point()
{
	//将预选位置的左边转化为窗口坐标
	Point temp;
	if (flag == Red_Player)
	{
		temp.x = yuxuan_point.x * 100 - 30;
		temp.y = yuxuan_point.y * 100 - 30;
	}
	else
	{
		temp.x = yuxuan_point.x * 100 - 90;
		temp.y = yuxuan_point.y * 100 - 30;
	}
	return temp;
}

Point Player::Getjidi_point()
{
	return jidi_point;
}

Point* Player::ToMapPoint(Point* point_)
{
	Point* temp = new Point();
	temp->x = point_->x * 100 - 50;
	temp->y = point_->y * 100 - 50;
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
	//判断是否是玩家的回合
	if (map->Gethuihe() % 2 == flag)
	{
		//地图点位未被占用
		if (map->GetMapState(&yuxuan_point).zhan_Point == NONE)
		{
			//基地还没确定，优先确定基地
			if (!jidi_point.x) {
				map->Update(&yuxuan_point, flag);//更新地图
				//将预选点位转化为地图点位，并保存
				jidi_point.x = yuxuan_point.x * 100 - 75;
				jidi_point.y = yuxuan_point.y * 100 - 75;
				before_point = yuxuan_point;
				//复制
				Point* point = new Point(jidi_point);
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
					break;
				case TOO_LONG:
					//提示玩家距离过长
					if (flag_window == 0) {
						flag_window++;
						main_window->Player_Window(L"距离过长",
							{ Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 });
					}
					break;
				case THOUGH:
					//提示玩家禁止穿线
					if (flag_window == 0) {
						flag_window++;
						main_window->Player_Window(L"禁止穿线",
							{ Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 });
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
				main_window->Player_Window(L"点位被占",
					{ Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 });
			}
		}
	}
	else {
		if (flag_window == 0) {
			flag_window++;
			//轮到敌人
			main_window->Player_Window(L"敌人回合",
				{ Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 });
		}
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
