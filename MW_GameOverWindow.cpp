#include "Main_Window.h"
#include "Game.h"

int Main_Window::Draw_GameOverWindow()
{
	SDL_Rect rect = { 50,30,100,50 };//文字矩形
	flagWindow = GameoverWindow;//将窗口标识设置为游戏结束窗口标识
	DrawPicture("background.png", NULL, { 0,0,rect_Main_Window.w,rect_Main_Window.h });//绘制背景图片
	//判断哪一方失败 哪一方失败就绘制对手胜利
	if (flag_Player == Red_Player) {
		DrawTTF(L"蓝方胜利", BLUE, rect);
	}
	else {
		DrawTTF(L"红方胜利", RED, rect);
	}
	DrawTTF(L"左键回到主页", BLACK, { 20,100,160,50 });//提示用户左键返回主窗口
	if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down) {
		b_flagWindow = flagWindow;
		flagWindow = MainWindow;//将窗口标识设置为主窗口标识
	}
	return 0;
}