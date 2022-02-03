#pragma once
#ifndef Main_Window_H
#define Main_Window_H

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include "Mouse_Window.h"
#include "myMath.h"
#include "Player.h"


//错误值
const int All_true = 0;
const int Window_error = 1;
const int Renderer_error = 2;
const int Init_error = 3;
const int TTF_Init_error = 4;
const int TTF_Open_error = 5;

//窗口标志
//用于确定现在窗口状态
//主窗口
const int MainWindow = 0;
//战斗窗口
const int FrightWindow = 1;
//游戏结束窗口
const int GameoverWindow = 2;
//技能选择窗口
const int SkillWindow = 4;
//模式选择窗口
const int ModelWindow = 5;

//普通模式
const int BaseModel = 1;
//技能模式
const int SkillModel = 2;
//竞技模式
const int FrightModel = 3;

//加载的字体
static const char* fontText = "simkai.TTF";
const int fontSize = 25;

//用于保存窗口提示的信息
struct Window_Msg {
	const wchar_t* text;
	SDL_Rect rect;
	int liveTime;
};

#pragma message ("Loading Main_Window...")
class Main_Window {
public:
	class Rander* rander;
	//初始化
	int CreatWindow(class Game* game_);
	//更新
	int Updata(class Player* red_player_,class Player* blue_player);
	//关闭
	int Shutdown();

	//添加玩家提示窗口
	//window_time = 0
	int Player_Window(const wchar_t* text_,SDL_Rect rect_,int& flag_window_);
	//获取窗口标志
	int GetFlag();
	//游戏结束
	int GameIsEnd(int flag_Player);
	//获取游戏模式
	int GetGameModel();

	//绘制线
	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawLineColor(int x1, int y1, int x2, int y2, SDL_Color color);
	//绘制边框矩形
	void DrawRect(int x, int y, int w, int h, SDL_Color* color);
	//绘制填充矩形
	void FillRect(int x, int y, int w, int h, SDL_Color* color);
	//绘制文字
	void DrawTTF(const wchar_t* text, SDL_Color color, SDL_Rect rect);
private:
	//创建新的窗口 自动销毁当前窗口
	int CreatNewWindow(const char* title, int x, int y, int w, int h);
	//绘制战斗的界面
	int Draw_FrightWindow();
	//绘制主界面
	int Draw_MainWindow();
	//绘制游戏结束的界面
	int Draw_GameOverWindow();
	//绘制技能选择窗口
	int Draw_SkillWindow();
	//绘制模式选择界面
	int Draw_ModelWindow();
	//绘制玩家行动
	int DrawMove(const vector<struct Move_point*>* move_point,SDL_Color* color_);
	//窗口提示
	std::vector<Window_Msg*> window_msg;
	//核心类
	class Game* game;
	class Input* input;
	class Player* red_player;
	class Player* blue_player;
	//额外类
	class Mouse_Window* mouse_window;
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
	//MainWindow = 0 FrightWindow = 1 GameoverWindow = 2 SkillWinodw = 3
	int flagWindow;
	//用于显示谁获得胜利
	int flag_Player;
	//用于技能选择界面的页面索引
	int index = 1;
	//用于模式选择
	int model = BaseModel;
};
#pragma message ("Main_Window is loaded")
#endif // !Main_Window_H