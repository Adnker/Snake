#pragma once
#ifndef Main_Window_H
#define Main_Window_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>


const int All_true = 0;
const int Window_error = 1;
const int Renderer_error = 2;
const int Init_error = 3;
const int TTF_Init_error = 4;
const int TTF_Open_error = 5;

//窗口标志
//用于确定现在窗口状态
const int MainWindow = 0;
const int FrightWindow = 1;
const int GameoverWindow = 2;

//

//加载的字体
static const char* fontText = "simkai.TTF";
const int fontSize = 25;

struct Window_Msg {
	const wchar_t* text;
	SDL_Rect rect;
	int liveTime;
};

class Main_Window {
public:
	//初始化
	int CreatWindow(class Game* game_, class Player* player_red,
		Player* player_blue);
	//更新
	int Updata();
	//关闭
	int Shutdown();

	//玩家提示窗口
	int Player_Window(const wchar_t* text_,SDL_Rect rect_);
	//获取窗口标志
	int GetFlag() { return flagWindow; };
	//游戏结束
	int GameIsEnd(int flag_Player);
private:
	//创建新的窗口
	int CreatNewWindow(const char* title, int x, int y, int w, int h);
	//绘制战斗的界面
	int Draw_FrightWindow();
	//绘制主界面
	int Draw_MainWindow();
	//绘制游戏结束的界面
	int Draw_GameOverWindow();
	//绘制线
	void DrawLine(int x1, int y1, int x2, int y2);
	//绘制矩形
	void DrawRect(int x, int y, int w, int h,SDL_Color* color);
	//绘制填充矩形
	void FillRect(int x, int y, int w, int h, SDL_Color* color);
	//绘制文字
	void DrawTTF(const wchar_t* text, SDL_Color color, SDL_Rect rect);
	//窗口提示
	std::vector<Window_Msg*> window_msg;
	//核心类
	class Game* game;
	class Input* input;
	class Player* red_player;
	class Player* blue_player;
	//窗口
	SDL_Window* window;
	//着色器
	SDL_Renderer* renderer;
	//矩形
	SDL_Rect rect;
	//文字
	TTF_Font* font;
	//窗口核心贴图器
	SDL_Surface* windowSurface;
	//窗口标志
	int flagWindow;
	//用于显示谁获得胜利
	int flag_Player;
};
#endif // !Main_Window_H