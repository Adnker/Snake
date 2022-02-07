#include "Main_Window.h"
#include "Game.h"

int Main_Window::Draw_FrightWindow()
{
	flagWindow = FrightWindow;//设置窗口标识为rect_Main_Window
	DrawPicture("backgroundFright.png", NULL, { 0,0,rect_Fright_Window.w,rect_Fright_Window.h });//绘制背景图片
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);//设置着色器颜色为黑色

	/*//////////////////////////////////////////////////////////////////////////////////*/
	//绘制战斗窗口的线条
	int i = 0;
	while (i <= 700) {
		//Y
		DrawLine(i, 0, i, 700);
		//X
		DrawLine(0, i, 700, i);
		i += 100;
	}
	DrawLine(350, 700, 350, 800);//最顶上的线条

	/*//////////////////////////////////////////////////////////////////////////////////*/
	//绘制技能
	int h_skill = 720;//技能统一高度
	int w_skill = 50;//技能统一宽度
	int j_skill = 30;//技能统一间距
	////判断选择的模式 不同的模式需要绘制的东西不同
	//if (model == SkillModel) {
	//	//技能模式
	//	DrawSkill(game->Getskill_name(red_player->Getskill()->at(0)), NULL, { 350 - j_skill - w_skill, h_skill, w_skill, w_skill });//绘制红方玩家的技能图标
	//	DrawSkill(game->Getskill_name(blue_player->Getskill()->at(0)), NULL, { 350 + j_skill, h_skill, w_skill, w_skill });//绘制蓝方玩家的技能图标
	//}
	//else if (model == FrightModel) {
	//	//竞技模式
	//	const vector<SKILL>* skill;//保存玩家的技能数组
	//	const wchar_t* skill_name;//保存对应的技能名字

	//	skill = red_player->Getskill();//获取红方玩家的技能数组
	//	//绘制红方玩家三个技能
	//	for (int i = 0; i < 3; i++) {
	//		DrawSkill(game->Getskill_name(skill->at(i)), NULL, { 700 - w_skill - j_skill,h_skill,w_skill,w_skill });
	//		DrawTTF(game->Getskill_flag_sum(red_player->Getskill_num(i)), RED, { i * fontSize * 3,740,40,40 });
	//	}
	//	skill = blue_player->Getskill();//获取蓝方玩家技能数组
	//	//绘制蓝方玩家三个技能
	//	for (int i = 0; i < 3; i++) {
	//		DrawSkill(game->Getskill_name(skill->at(i)), NULL, { 700 - w_skill - j_skill,h_skill,w_skill,w_skill });
	//		DrawTTF(game->Getskill_flag_sum(blue_player->Getskill_num(i)), BLUE, { 700 - (i + 1) * fontSize * 3,740,40,40 });
	//	}
	//}

	/*///////////////////////////////////////////////////////////////////////////////*/
	//绘制玩家行动路线
	int jidi_h = 50;//统一基地边长
	const vector<Move_point*>* move_point;//保存玩家移动数组

	move_point = red_player->GetMove_point();//获取玩家的移动数组
	if (!move_point->empty()) {
		FillRect(move_point->at(0)->point->x * 100 + 25, move_point->at(0)->point->y * 100 + 25, jidi_h, jidi_h, &RED);//绘制玩家的基地
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);//设置着色器颜色为红色
		DrawMove(move_point, &RED);
	}
	move_point = blue_player->GetMove_point();//获取蓝方移动数组
	if (!move_point->empty()) {
		FillRect(move_point->at(0)->point->x * 100 + 25, move_point->at(0)->point->y * 100 + 25, jidi_h, jidi_h, &BLUE);//绘制蓝方基地
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);//设置着色器颜色为蓝色
		DrawMove(move_point, &BLUE);
	}

	/*///////////////////////////////////////////////////////////////////////////////*/
	//绘制玩家预选框
	Point temp;//保存玩家预选框的坐标
	string name;//保存玩家图片名字
	SDL_Rect rect;//保存玩家图片矩形
	int h_yu = 30;//统一预选框的高度
	temp = red_player->Getyuxuan_point();//获取红方预选框坐标
	name = red_player->Getpicture_name();//获取红方图片名字
	rect = { temp.x, temp.y, h_yu, h_yu };
	texture->Draw(name, NULL, &rect);
	temp = blue_player->Getyuxuan_point();//获取蓝方预选框坐标
	name = blue_player->Getpicture_name();//获取蓝方图片名字
	rect = { temp.x, temp.y, h_yu, h_yu };
	texture->Draw(name, NULL, &rect);

	/*/////////////////////////////////////////////////////////////////////////////*/
	//绘制玩家提示窗口
	if (window_msg.size() > 0)
	{
		for (int i = 0; i < window_msg.size(); i++)
		{
			//对每个提示窗口进行判断，如果窗口的显示时间大于提示窗口提示时间，要对窗口进行销毁，反之进行绘制
			if (window_msg.at(i)->liveTime > DeadTime) {
				//销毁窗口
				window_msg.erase(window_msg.begin() + i, window_msg.begin() + i + 1);
			}
			else {
				if (window_msg.at(i)->flag == Red_Player) {
					window_msg.at(i)->rect.x = red_player->Getyuxuan_point().x;
					window_msg.at(i)->rect.y = red_player->Getyuxuan_point().y + window_msg.at(i)->rect.h;
				}
				else {
					window_msg.at(i)->rect.x = blue_player->Getyuxuan_point().x;
					window_msg.at(i)->rect.y = blue_player->Getyuxuan_point().y + window_msg.at(i)->rect.h;
				}
				//绘制窗口
				//判断提示窗口是否超出窗体，超出窗体则对窗口信息进行修正，避免提示框越出窗口
				if (window_msg.at(i)->rect.x + window_msg.at(i)->rect.w > rect_Fright_Window.w) {
					window_msg.at(i)->rect.x = rect_Fright_Window.w - window_msg.at(i)->rect.w;
				}
				DrawPicture("backgroundPlayer.png", NULL, { window_msg.at(i)->rect.x, window_msg.at(i)->rect.y,
					window_msg.at(i)->rect.w, window_msg.at(i)->rect.h });//绘制提示窗口背景
				DrawTTF(window_msg.at(i)->text, LITTLE_BLACK, window_msg.at(i)->rect);//绘制提示窗口提示文字
				window_msg.at(i)->liveTime++;//增加提示窗口显示时间
			}
		}
	}

	if (red_player->SkillNeedShow()) 
	{
		DrawSkill(game->Getskill_name(red_player->ShowSkill_index()), NULL, red_player->ShowSkill_rect());
	}
	if (blue_player->SkillNeedShow())
	{
		DrawSkill(game->Getskill_name(blue_player->ShowSkill_index()), NULL, blue_player->ShowSkill_rect());
	}
	return 0;
}