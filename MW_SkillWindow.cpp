#include "Main_Window.h"
#include "Game.h"

int Main_Window::Draw_SkillWindow()
{
	flagWindow = SkillWindow;
	//按钮属性
	int button_x = 200;//按钮显示位置
	int button_y = 100;//按钮显示位置
	int button_w = 100;//按钮宽
	int button_h = 40;//按钮高
	SDL_Rect text1 = { 0,420,80,50 };//上一页按钮
	SDL_Rect text2 = { 420,420,80,50 };//下一页按钮
	BUTTONER Button1 = 0;//按钮1标识
	BUTTONER Button2 = 1;//按钮2标识
	BUTTONER Button3 = 2;//按钮3标识
	BUTTONER Button4 = 3;//按钮4标识
	BUTTONER Button5 = 4;//按钮5标识


	if (b_flagWindow != flagWindow) {
		button->Clear();
		button->AddButton(L"无技能", texture->GetTexture("k3.png"), NULL,
			{ button_x - picture_jianju_x,button_y * 1,button_w + picture_jianju_w,button_h },
			{ button_x,button_y * 1,button_w,button_h }, font, &LITTLE_BLACK);
		button->AddButton(L"无技能", texture->GetTexture("k3.png"), NULL,
			{ button_x - picture_jianju_x,button_y * 2,button_w + picture_jianju_w,button_h },
			{ button_x,button_y * 2,button_w,button_h }, font, &LITTLE_BLACK);
		button->AddButton(L"无技能", texture->GetTexture("k3.png"), NULL,
			{ button_x - picture_jianju_x,button_y * 3,button_w + picture_jianju_w,button_h },
			{ button_x,button_y * 3,button_w,button_h }, font, &LITTLE_BLACK);
		button->AddButton(NULL, texture->GetTexture("buttonLeft.png"), NULL, text1, text1, font, &BLACK);
		button->AddButton(NULL, texture->GetTexture("buttonRight.png"), NULL, text2, text2, font, &BLACK);
		button->GetButton(Button4)->drawFlag = false;//一开始的时候上一页不用绘制
	}
	b_flagWindow = flagWindow;
	DrawPicture("background.png", NULL, { 0,0,rect_Main_Window.w,rect_Main_Window.h });//绘制背景



	//index + Button_ = 对应的技能索引
	int Skill1 = index + Button1;//技能1索引
	int Skill2 = index + Button2;//技能2索引
	int Skill3 = index + Button3;//技能3索引
	//修改按钮显示的技能文字
	button->GetButton(Button1)->text = game->Getskill_name(Skill1);
	button->GetButton(Button2)->text = game->Getskill_name(Skill2);
	button->GetButton(Button3)->text = game->Getskill_name(Skill3);
	button->DrawButton(renderer);//绘制全部按钮


	button->Updata(input);//更新全部按钮的状态
	int picture_h = 40;//选中提示图片边长
	int skill_index = -1;//需要显示的技能索引
	int picture_index = -1;//需要显示的提示图片索引
	//第一个按钮
	bool Skill1_index_isTrue = Skill1 <= game->Getskill_sum();
	if (Skill1_index_isTrue) {
		switch (button->GetButtonLeftState(Button1))
		{
		case Key_Down:
			ChangeSkill(Skill1);//修改玩家技能标识
			index = 1;
			break;
		case Key_Move:
			picture_index = Button1;
			skill_index = Skill1;
			break;
		}
	}


	//第二个按钮
	bool Skill2_index_isTrue = Skill2 <= game->Getskill_sum();
	if (Skill2_index_isTrue) {
		switch (button->GetButtonLeftState(Button2))
		{
		case Key_Down:
			ChangeSkill(Skill2);;//修改玩家技能标识
			index = 1;
			break;
		case Key_Move:
			picture_index = Button2;
			skill_index = Skill2;
			break;
		}
	}


	//第三个按钮
	bool Skill3_index_isTrue = Skill3 <= game->Getskill_sum();
	if (Skill3_index_isTrue) {
		switch (button->GetButtonLeftState(Button3))
		{
		case Key_Down:
			ChangeSkill(Skill3);;//修改玩家技能标识
			index = 1;
			break;
		case Key_Move:
			picture_index = Button3;
			skill_index = Skill3;
			break;
		}
	}


	//绘制需要显示的技能
	if (skill_index > -1) {
		int y = button_y * (skill_index % 3);
		if (y == 0) { y = button_y * 3; }
		DrawSkill(game->Getskill_name(skill_index), NULL, { button_x - picture_jianju_x - button_h,y,button_h,button_h });//绘制技能图标提示
	}
	if (picture_index > -1) {
		picture_index++;
		DrawPicture("buttonRight.png", NULL, { button_x - picture_h, button_y * picture_index, picture_h, picture_h });//绘制选中提示图片
	}


	bool index_isTrue;
	bool needToDraw;
	needToDraw = index > 3;
	if (needToDraw) {
		button->GetButton(Button4)->drawFlag = true;
		//上一页 第四个按钮
		int& Button4_x = button->GetButton(Button4)->rectxy->x;//按钮4x坐标
		int& Button4_flag = button->GetButton(Button4)->flag;//按钮4特殊标识
		index_isTrue = index - 3 > 0;
		switch (button->GetButtonLeftState(Button4))
		{
		case Key_Down:
			if (index_isTrue) { index -= 3; }
			break;
		case Key_Move:
			if (Button4_flag == 0) { Button4_x++; if (Button4_x > 30) { Button4_flag = 1; } }
			else { Button4_x--; if (Button4_x < 1) { Button4_flag = 0; } }
			break;
		default:
			Button4_x = text1.x;
			Button4_flag = 0;
			break;
		}
	}
	else {
		button->GetButton(Button4)->drawFlag = false;
	}


	needToDraw = Skill3 < game->Getskill_sum();
	if (needToDraw) {
		button->GetButton(Button5)->drawFlag = true;
		//下一页 第五个按钮
		int& Button5_x = button->GetButton(Button5)->rectxy->x;//按钮5x坐标
		int& Button5_flag = button->GetButton(Button5)->flag;//按钮5特俗标识
		index_isTrue = index + 3 <= game->Getskill_sum();
		switch (button->GetButtonLeftState(Button5))
		{
		case Key_Down:
			if (index_isTrue) { index += 3; }
			break;
		case Key_Move:
			if (Button5_flag == 0) { Button5_x--; if (Button5_x < 500 - text2.w - 30) { Button5_flag = 1; } }
			else { Button5_x++; if (Button5_x > 500 - text2.w) { Button5_flag = 0; } }
			break;
		default:
			Button5_x = text2.x;
			Button5_flag = 0;
			break;
		}
	}
	else {
		button->GetButton(Button5)->drawFlag = false;
	}



	const wchar_t* text;//显示的文本内容
	SDL_Color color;//文本颜色
	std::string name;//图片名字
	if (red_player->Getskill()->empty()) {
		text = L"红方选择技能";
		name = "reddown.png";
		color = RED;
	}
	else {
		text = L"蓝方选择技能";
		name = "bluedown.png";
		color = BLUE;
	}
	DrawTTF(text, color, { 175,25,fontSize * 6,30 });
	SDL_Rect rect = { 140,25,30,30 };
	texture->Draw(name, NULL, &rect);
	return 0;
}