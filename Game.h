#pragma once
#include <iostream>
#include <SDL.h>
#include "Input.h"
#include "Main_Window.h"
#include "Player.h"
#include "Map.h"

class Game {
public:
	int OpenGame();
	int Updata();
	int Shutdown();
	class Input* GetInput() { return input; }
	bool gameIsRun;//游戏是否结束
	int CreatePlay();//为玩家分配内存
	int DestroyPlay();//回收玩家内存
	const wchar_t* Getskill_name(int index);//获取全技能名称
	const wchar_t* Getskill_flag_sum(int sum);//转化为技能次数的const wchar_t* 格式
	int Getskill_sum();//获取技能总数
	const wchar_t* Getskill_jieshao(int index);//获取技能介绍
private:
	bool isRuning;//退出标志
	Uint32 mTickCout;//游戏时间增加量

	//class
	class Main_Window* main_window;
	class Input* input;
	class Player* red_player;
	class Player* blue_player;
	class Map* map;
	class Skiller* skiller;
};