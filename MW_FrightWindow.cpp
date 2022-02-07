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

	if (model == FrightModel) {
		red_player->AddSkill();
		blue_player->AddSkill();
	}

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

	int skill_sum_h = 20;
	if (red_player->SkillNeedShow()) 
	{
		SDL_Rect rectShow = red_player->ShowSkill_rect();
		if (rectShow.x + rectShow.w * 2 + 5 > rect_Fright_Window.w) {
			rectShow.x = rect_Fright_Window.w - rectShow.w * 2 - 5;
		}
		if (rectShow.y + rectShow.h > rect_Fright_Window.h) {
			rectShow.y = rect_Fright_Window.h - rectShow.h - 30; 
		}
		DrawSkill(game->Getskill_name(red_player->Getskill()->at(red_player->ShowSkill_index())), NULL, rectShow);
		rectShow.x = rectShow.x + rectShow.w - skill_sum_h;
		rectShow.y = rectShow.y + rectShow.h - skill_sum_h;
		rectShow.h = skill_sum_h;
		rectShow.w = skill_sum_h;
		DrawTTF(game->Getskill_flag_sum(red_player->Getskill_sum(red_player->ShowSkill_index())), WHITE, rectShow);
	}
	if (blue_player->SkillNeedShow())
	{
		SDL_Rect rectShow = blue_player->ShowSkill_rect();
		if (rectShow.x + rectShow.w * 2 + 5 > rect_Fright_Window.w) {
			rectShow.x = rect_Fright_Window.w - rectShow.w * 2 - 5;
		}
		if (rectShow.y + rectShow.h > rect_Fright_Window.h) {
			rectShow.y = rect_Fright_Window.h - rectShow.h - 30 ;
		}
		DrawSkill(game->Getskill_name(blue_player->Getskill()->at(blue_player->ShowSkill_index())), NULL, rectShow);
		rectShow.x = rectShow.x + rectShow.w - skill_sum_h;
		rectShow.y = rectShow.y + rectShow.h - skill_sum_h;
		rectShow.h = skill_sum_h;
		rectShow.w = skill_sum_h;
		DrawTTF(game->Getskill_flag_sum(blue_player->Getskill_sum(blue_player->ShowSkill_index())), WHITE, rectShow);
	}
	return 0;
}