#include "Player.h"
#include "Map.h"
#include "myFun.h"

const int TOO_LONG = 2;
const int THOUGH = 3;
const int NOPOINT = 4;


/*
* 初始化函数
*/
int Player::CreatePlayer(Main_Window* main_window_, Input* input_, Map* map_, Player* player_,
	Skiller* skiller_, int flag_)
{
	//复制class
	input = input_;
	main_window = main_window_;
	map = map_;
	flag = flag_;
	player = player_;
	skiller = skiller_;
	skill_num = 1;
	move_num = 1;
	if (flag == Red_Player) {
		picture_name = "reddown.png";
	}
	else {
		picture_name = "bluedown.png";
	}
	if (main_window->GetGameModel() == FrightModel) {
		CreateAllSkill();
	}
	return 0;
}


/*
* 重置玩家
*/
int Player::Clear()
{
	move_num = 1;
	skill_num = 1;
	window_time = 0;
	yuxuan_point = { 0,0 };
	return true;
}


/*
* 更新
*/
int Player::Updata()
{
	if (window_time > 0) {
		window_time++;
	}
	if (window_time >= 100) {
		window_time = 0;
	}

	//更新玩家操作
	//判断玩家是否死亡
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
			if (!SkillNeedShow()) {
				yuxuan_point.y--;
				picture_name = "redup.png";
			}
		}
		//预选位置向下移动
		else if (input->GetKeyState(SDL_SCANCODE_S) == Key_Down)
		{
			if (!SkillNeedShow()) {
				yuxuan_point.y++;
				picture_name = "reddown.png";
			}
		}
		//预选位置向左移动
		else if (input->GetKeyState(SDL_SCANCODE_A) == Key_Down)
		{
			if (SkillNeedShow()) {
				Change_skill_state(-1);
			}
			else {
				yuxuan_point.x--;
				picture_name = "redleft.png";
			}
		}
		//预选位置向右移动
		else if (input->GetKeyState(SDL_SCANCODE_D) == Key_Down)
		{
			if (SkillNeedShow()) {
				Change_skill_state(1);
			}
			else {
				yuxuan_point.x++;
				picture_name = "redright.png";
			}
		}
		//选择
		//选择结束时记得更新地图
		//移动
		else if (input->GetKeyState(SDL_SCANCODE_G) == Key_Down)
		{
			if (SkillNeedShow()) {
				Skill(skill_state);
				skill_state = -1;
			}
			else { Movetion(); }
		}
		//技能
		else if (input->GetKeyState(SDL_SCANCODE_H) == Key_Down)
		{
			if (main_window->GetGameModel() != BaseModel) {
				if (SkillNeedShow()) { skill_state = -1; }
				else { skill_state = 0; }
			}
		}
		else if (input->GetKeyState(SDL_SCANCODE_J) == Key_Down)
		{
			Xuhand();
		}

	}
	//蓝色玩家
	else
	{
		//预选位置向上移动
		if (input->GetKeyState(SDL_SCANCODE_UP) == Key_Down)
		{
			if (!SkillNeedShow()) {
				yuxuan_point.y--;
				picture_name = "blueup.png";
			}
		}
		//预选位置向下移动
		else if (input->GetKeyState(SDL_SCANCODE_DOWN) == Key_Down)
		{
			if (!SkillNeedShow()) {
				yuxuan_point.y++;
				picture_name = "bluedown.png";
			}
		}
		//预选位置向左移动
		else if (input->GetKeyState(SDL_SCANCODE_LEFT) == Key_Down)
		{
			if (SkillNeedShow()) {
				Change_skill_state(-1);
			}
			else {
				yuxuan_point.x--;
				picture_name = "blueleft.png";
			}
		}
		//预选位置向右移动
		else if (input->GetKeyState(SDL_SCANCODE_RIGHT) == Key_Down)
		{
			if (SkillNeedShow()) {
				Change_skill_state(1);
			}
			else {
				yuxuan_point.x++;
				picture_name = "blueright.png";
			}
		}
		//选择
		//选择结束时记得更新地图
		//移动
		else if (input->GetKeyState(SDL_SCANCODE_KP_1) == Key_Down)
		{
			if (SkillNeedShow()) {
				Skill(skill_state);
				skill_state = -1;
			}
			else { Movetion(); }
		}
		else if (input->GetKeyState(SDL_SCANCODE_KP_2) == Key_Down)
		{
			if (main_window->GetGameModel() != BaseModel) {
				if (SkillNeedShow()) { skill_state = -1; }
				else { skill_state = 0; }
			}
		}
		else if (input->GetKeyState(SDL_SCANCODE_KP_3) == Key_Down)
		{
			Xuhand();
		}
	}
	//检验预选位置是否超出范围
	if (yuxuan_point.x < 0) { yuxuan_point.x = 0; }
	else if (yuxuan_point.x > 6) { yuxuan_point.x = 6; }
	else if (yuxuan_point.y < 0) { yuxuan_point.y = 0; }
	else if (yuxuan_point.y > 6) { yuxuan_point.y = 6; }

	return 0;
}


/*
* 更新玩家的移动次数，技能可使用次数
* 每次回合更新的时候都需要调用敌人的这个函数
*/
void Player::UpdataSum()
{
	move_num = 1;
	skill_num = 1;
}


/*
* 获取玩家的预选点位
*/
Point Player::Getyuxuan_point()
{
	//将预选位置的左边转化为窗口坐标
	if (flag == Red_Player)
	{
		return { yuxuan_point.x * 100 + 10,yuxuan_point.y * 100 + 70 };
	}
	else
	{
		return { yuxuan_point.x * 100 + 70,yuxuan_point.y * 100 + 70 };
	}
}


/*
* 基地点位转化为普通地图点位
*/
Point Player::JidiToMap(Move_point* point_)
{
	if (point_->flag != JIDI) {
		return { -1,-1 };
	}
	else {
		return { point_->point->x * 100 + 30,point_->point->y * 100 + 30 };
	}
}


/*
* 点位转化为地图点位
*/
Point Player::ToMapPoint(Point* point_)
{
	return { point_->x * 100 + 50,point_->y * 100 + 50 };
}


/*
* 获取玩家技能数组
*/
vector<int>* Player::Getskill()
{
	return &skill;
}


/*
* 获取对应索引index技能的剩余可用次数
*/
int Player::Getskill_sum(int index)
{
	return skill_sum.at(index);
}


/*
* 获取移动数组
*/
vector<Move_point*>* Player::GetMove_point()
{
	return &move_point;
}


/*
* 修改玩家的技能
*/
int Player::Changeskill(int index)
{
	if (skill.empty()) {
		skill.emplace_back(index);
		skill_sum.emplace_back(skiller->GetSkillSum(index));
		return true;
	}
	return false;
}


/*
* 获取玩家这一帧需要显示的图片名字
*/
string Player::Getpicture_name()
{
	return picture_name;
}


/*
* 判断战斗界面是否需要绘制技能
* 返回值为true时 调用ShowSkill_index函数
*/
bool Player::SkillNeedShow()
{
	if (main_window->GetGameModel() == FrightModel) {
		return skill_state > -1 && skill_state < 3;
	}
	else {
		return skill_state > -1 && skill_state < 1;
	}
}


/*
* 需要绘制技能时调用此函数获取需要绘制的技能索引
* SkillNeedShow函数为true时调用
*/
int Player::ShowSkill_index()
{
	return skill_state;
}


/*
* 获取需要绘制技能的矩形
* SkillNeedShow函数为true是调用
*/
SDL_Rect Player::ShowSkill_rect()
{
	return { Getyuxuan_point().x,Getyuxuan_point().y + 30,50,50 };
}


/*
* 竞技模式调用此函数为玩家分配技能
*/
int Player::CreateAllSkill()
{
	for (SKILL i = 1; i < SKILLSUM; i++) {
		skill_all.emplace_back(i);
	}
	while (skill.size() < 3) {
		int rand = main_window->rander->GetARand(skill_all.size() - 1);
		skill.emplace_back(skill_all.at(rand));
		skill_all.erase(skill_all.begin() + rand, skill_all.begin() + rand + 1);
		skill_sum.emplace_back(skiller->GetSkillSum(skill.back()));
	}
	return 0;
}


/*
* 竞技模式每5个来回调用一次这个函数
*/
int Player::AddSkill()
{
	if (map->Gethuihe() % 10 != 0 || map->Gethuihe() < 1) { return false; }
	int index = 0;
	for (int i = 0; i < skill_sum.size(); i++) {
		if (skill_sum.at(i) < 0) {
			index = i;
			break;
		}
	}
	int rand = main_window->rander->GetARand(skill_all.size() - 1);
	skill.at(index) = skill_all.at(rand);
	skill_all.erase(skill_all.begin() + rand, skill_all.begin() + rand + 1);
	skill_sum.at(index) = skiller->GetSkillSum(skill.back());
	return true;
}


/*
* 获取上一个基地点位或者普通点位，一般作为绘制路线的依据
* 虚路线点位请调用 GetBeforePointXu
*/
Point* Player::GetBeforePoint()
{
	int index = GetBeforePoint_index();
	auto point = index == -1 ? Point(-1, -1) : *move_point.at(index)->point;
	return &point;
}


/*
* 获取上一个虚路线点位
* 实路线点位请调用 GetBeforePoint
*/
Point* Player::GetBeforePointXu()
{
	int index = GetBeforePointXu_index();
	auto point = index == -1 ? Point(-1, -1) : *move_point.at(index)->point;
	return &point;
}



/*
* 获取上一个基地点位或普通点位的索引
* 虚路线索引请调用 GetBeforePointXu_index
*/
int Player::GetBeforePoint_index()
{
	int index = move_point.size() - 1;
	while (move_point.at(index)->hand != ZHU_HAND) {
		index--;
	}
	return index;
}


/*
* 获取上一个虚路线点位的索引
* 实路线索引请调用 GetBeforePoint_index
*/
int Player::GetBeforePointXu_index()
{
	SDL_Rect text_rect = { Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 };
	int index = move_point.size() - 1;
	if (move_point.empty()) {
		main_window->Player_Window(L"无虚路线", text_rect, window_time, flag);
		return -1;
	}
	while (move_point.at(index)->hand != XU_HAND) {
		index--;
		if (index == -1) {
			return -1;
		}
	}
	return index;
}


/*
* 判断玩家能否继续移动
* 在回合移动后调用检查，将自动完成回合结束工作
*/
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


/*
* 判断移动点位是否符合规范
* flag_ 是否是外来点位
* point_ 外来点位，当flag_为false时此参数被忽略
* xuhand_flag_ 是否是虚路线头
*/
int Player::MoveIsRight(bool flag_, Point point_, bool xuhand_flag_)
{
	Point* temp;
	if (flag_) {
		if (point_.x < 0 || point_.x > 6 || point_.y < 0 || point_.y > 6) { return NOPOINT; }
		temp = &point_;
	}
	else { temp = &yuxuan_point; }

	//最后一个点位 赋值
	int index = move_point.size() - 1;
	Point before = ToMapPoint(xuhand_flag_ ? GetBeforePointXu() : GetBeforePoint());//上一点位
	Point now = ToMapPoint(temp);//现在的点位
	//计算两点之间的距离是否是正确的
	int distance = static_cast<int>(
		sqrt((
			(before.x - now.x) * (before.x - now.x) +
			(before.y - now.y) * (before.y - now.y)
			))
		);
	Point* before_point = move_point.at(move_point.size() - 1)->point;
	if (distance > 199) { return TOO_LONG; }
	//是否穿线
	else if (
		map->IsThoughLine(
			before_point->x, temp->y, temp->x, before_point->y)
		) {
		return THOUGH;
	}
	else { return true; }
}


/*
* 移动函数
* flag_ 是否是强制移动
*/
int Player::Movetion(int flag_)
{
	//提示窗口大小
	SDL_Rect text_rect = { Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 };
	//判断是否是玩家的回合
	if (map->Gethuihe() % 2 == flag || flag_)
	{
		//如果没有移动次数
		if (move_num < 1) {
			if (window_time == 0 && !flag_) {
				main_window->Player_Window(L"不可移动", text_rect, window_time, flag);
			}
			return false;
		}
		//地图点位未被占用
		if (map->GetMapState(&yuxuan_point).zhan_Point == NONE)
		{
			//基地还没确定，优先确定基地
			if (move_point.empty()) {
				map->Updata(&yuxuan_point, flag, ZHAN, true);//更新地图，回合增加
				//创建新的点位并加入行动数组中
				Move_point* temp_point = new Move_point(yuxuan_point, JIDI);
				move_point.emplace_back(temp_point);
				return true;
			}
			else {
				Move_point* point;
				switch (MoveIsRight()) {
				case true:
					point = new Move_point(yuxuan_point, NULL);
					move_point.emplace_back(point);//将点位加入
					CanMove();
					return true;
				case TOO_LONG:
					//提示玩家距离过长
					if (window_time == 0 && !flag_) {
						main_window->Player_Window(L"距离过长", text_rect, window_time, flag);
					}
					return false;
				case THOUGH:
					//提示玩家禁止穿线
					if (window_time == 0 && !flag_) {
						main_window->Player_Window(L"禁止穿线", text_rect, window_time, flag);
					}
					return false;
				}
			}
		}
		else
		{
			//点位被占用
			if (window_time == 0 && !flag_) {
				main_window->Player_Window(L"点位被占", text_rect, window_time, flag);
			}
			return false;
		}
	}
	else {
		if (window_time == 0 && !flag_) {
			//轮到敌人
			main_window->Player_Window(L"敌人回合", text_rect, window_time, flag);
		}
		return false;
	}
}


/*
* 技能函数
* index_ 使用技能数组那个索引index对应的技能
*/
int Player::Skill(int index_)
{
	//提示窗口大小
	SDL_Rect text_rect = { Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 };
	if (main_window->GetGameModel() == SkillModel) {
		if (index_ > 0) {
			main_window->Player_Window(L"使用失败", text_rect, window_time, flag);
			return 0;
		}
	}
	//基地还未放置无法使用技能
	if (move_point.empty()) {
		main_window->Player_Window(L"基地未放", text_rect, window_time, flag);
	}
	//技能使用次数少
	else if (skill_num < 1) {
		main_window->Player_Window(L"不可使用", text_rect, window_time, flag);
	}
	//敌人的回合
	else if (map->Gethuihe() % 2 != flag) {
		main_window->Player_Window(L"敌人回合", text_rect, window_time, flag);
	}
	//技能对应的使用次数小于1
	else if (skill_sum.at(index_) < 1) {
		main_window->Player_Window(L"使用失败", text_rect, window_time, flag);
	}
	else {
		//调用技能使用函数
		//是否更新回合在技能使用中已经调用
		if (skiller->Use_Skill(skill.at(index_), flag)) {
			//回合技能数和技能总次数均-1
			skill_num--;
			skill_sum.at(index_)--;
			return true;
		}
		else { main_window->Player_Window(L"使用失败", text_rect, window_time, flag); }
	}
	return false;
}


/*
* 虚路线头移动函数
*/
int Player::Xuhand()
{
	SDL_Rect text_rect = { Getyuxuan_point().x,Getyuxuan_point().y + 20,100,30 };
	if (main_window->GetGameModel() == BaseModel)
	{
		return false;
	}
	int index = GetBeforePointXu_index();
	if (index == -1) {
		main_window->Player_Window(L"无虚路线", text_rect, window_time, flag);
		return false;
	}
	switch (MoveIsRight(false, Point(-1, -1), true))
	{
	case NOPOINT:
		return false;
	case TOO_LONG:
		main_window->Player_Window(L"距离过长", text_rect, window_time, flag);
		return false;
	case THOUGH:
		main_window->Player_Window(L"禁止穿线", text_rect, window_time, flag);
		return false;
	default:
		Move_point* point = new Move_point(yuxuan_point, index, XU_HAND);
		move_point.emplace_back(point);
		CanMove();
		return true;
	}
}


/*
* 判断玩家是否死亡
* 每个回合都需要进行一次判断
*/
int Player::IsLife()
{
	bool isLife = DEAD;
	Point* before_point = GetBeforePoint();
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (map->GetMapStatexy(before_point->x + i, before_point->y + j).zhan_Point == NONE) {
				if (MoveIsRight(true, { before_point->x + i,before_point->y + j }) == true) {
					isLife = LIFE;
				}
			}
		}
	}
	if (skill_num < 1 && map->Gethuihe() % 2 == flag) {
		return isLife;
	}
	//判断玩家的技能是否可以使用
	int model = main_window->GetGameModel();
	if (model == FrightModel) {
		for (int i = 0; i < 3; i++) {
			if (skiller->IsLiveSkill(skill.at(i)) && skill.at(i) > 0) {
				isLife = LIFE;
			}
		}
	}
	else if (model == SkillModel) {
		if (skiller->IsLiveSkill(skill.at(0)) && skill_sum.at(0) > 0) {
			isLife = LIFE;
		}
	}
	return isLife;
}


/*
* 修改需要显示的技能的状态
*/
int Player::Change_skill_state(int flag)
{
	if (SkillNeedShow() && main_window->GetGameModel() == FrightModel) {
		if (skill_state + flag > -1 && skill_state + flag < 3) {
			skill_state += flag;
			return true;
		}
	}
	return false;
}