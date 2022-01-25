#pragma once
#include <iostream>
#include <SDL.h>
#include "Input.h"
#include "Main_Window.h"
#include "Player.h"
#include "Map.h"


#pragma message ("Loading Game...")
class Game {
public:
	int OpenGame();
	int Updata();
	int Shutdown();

	//游戏是否结束
	bool gameIsRun;

	//为玩家分配内存
	int CreatePlay();
	int DestroyPlay();
	class Input* GetInput() { return input; }

	//获取全技能名称
	const wchar_t* Getskill_name(int index);
	//获取技能总数
	int Getskill_sum();
private:
	//退出标志
	bool isRuning;
	//游戏时间增加量
	Uint32 mTickCout;
	//主窗口类
	class Main_Window* main_window;
	class Input* input;
	class Player* red_player;
	class Player* blue_player;
	class Map* map;
	class Skiller* skiller;
};
#pragma message ("Game is loaded")