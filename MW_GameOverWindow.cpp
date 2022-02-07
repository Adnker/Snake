#include "Main_Window.h"
#include "Game.h"

int Main_Window::Draw_GameOverWindow()
{
	flagWindow = GameoverWindow;//将窗口标识设置为游戏结束窗口标识
	const wchar_t* text;//显示的文本内容
	SDL_Color color;//文本颜色
	std::string name;//图片名字
	DrawPicture("background.png", NULL, { 0,0,rect_Main_Window.w,rect_Main_Window.h });//绘制背景图片
	//判断哪一方失败 哪一方失败就绘制对手胜利
	if (flag_Player == Red_Player) {
		text = L"蓝方获得胜利";
		name = "bluedown.png";
		color = BLUE;
	}
	else {
		text = L"红方获得胜利";
		name = "reddown.png";
		color = RED;
	}
	DrawTTF(L"左键回到主页", BLACK, { 50,200,160,50 });//提示用户左键返回主窗口
	DrawTTF(text, color, { 175,25,fontSize * 6,25 });
	SDL_Rect rect = { 140,25,25,25 };
	texture->Draw(name, NULL, &rect);
	if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down) {
		b_flagWindow = flagWindow;
		flagWindow = MainWindow;//将窗口标识设置为主窗口标识
	}
	return 0;
}