#include "Main_Window.h"
#include "Game.h"

int Main_Window::Draw_ModelWindow()
{
	flagWindow = ModelWindow;
	//文本框架
	int x = 200;
	int y = 100;
	int w = 100;
	int h = 40;
	if (b_flagWindow != flagWindow) {
		button->Clear();
		button->AddButton(L"普通训练", texture->GetTexture("k3.png"), NULL, {x,y * 1,w,h}, font, &BLACK);
		button->AddButton(L"技能训练", texture->GetTexture("k3.png"), NULL, { x,y * 2,w,h }, font, &BLACK);
		button->AddButton(L"竞技模式", texture->GetTexture("k3.png"), NULL, { x,y * 3,w,h }, font, &BLACK);
	}
	b_flagWindow = flagWindow;
	DrawPicture("background.png", NULL, { 0,0,rect_Main_Window.w,rect_Main_Window.h });
	button->DrawButton(renderer);
	button->Updata(input);
	for (int flag_model = 1; flag_model <= 3; flag_model++) {
		switch (button->GetButtonLeftState(flag_model - 1))
		{
		case Key_Down:
			b_flagWindow = flagWindow;
			flagWindow = MainWindow;
			model = flag_model;
			break;
		case Key_Move:
			DrawPicture("buttonRight.png", NULL, { x - 45, y * flag_model, 40, 40 });
			break;
		default:
			break;
		}
	}
	return 0;
}
