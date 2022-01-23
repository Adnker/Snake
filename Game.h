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
	class Input* GetInput() { return &input; }
private:
	//退出标志
	bool isRuning;
	//游戏时间增加量
	Uint32 mTickCout;
	//主窗口类
	class Main_Window main_window;
	//输入类
	class Input input;
	//玩家类
	class Player red_player;
	class Player blue_player;
	//地图类
	class Map map;
};
#pragma message ("Game is loaded")