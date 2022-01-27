#include "Game.h"
#include "Input.h"

int Game::OpenGame()
{
	isRuning = true;
	//创建各个类
	input = new Input();
	input->CreateInput();
	main_window = new Main_Window();
	skiller = new Skiller();
	if (main_window->CreatWindow(this) > 0) { isRuning = false; return false; }

	//创建
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		SDL_Log("%s", SDL_GetError());
		return Init_error;
	}

	return 0;
}

int Game::Updata()
{
	while (isRuning) {
		if (!isRuning) { return false; }
		//SDL事件
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRuning = false;
				break;
			}
		}
		//计算增量
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCout + 16))
			;
		float deltaTime = (SDL_GetTicks() - mTickCout) / 1000.0f;
		if (deltaTime > 0.05f)
		{
			deltaTime = 0.05f;
		}


		input->Updata();
		//在战斗界面才更新玩家操作
		if (main_window->GetFlag() == FrightWindow)
		{
			if (gameIsRun) { red_player->Updata(); }
			if (gameIsRun) { blue_player->Updata(); }
		}
		main_window->Updata(red_player,blue_player);
	}
	return 0;
}

int Game::Shutdown()
{
	if (isRuning == true) {
		isRuning = false;
		return 0;
	}
	main_window->Shutdown();
	delete main_window;
	delete input;
	delete map;
	SDL_Quit();
	return 0;
}

int Game::CreatePlay()
{
	map = new Map();
	map->CreateMap();
	skiller->CreateSkiller(map);
	//获取玩家指针
	red_player = skiller->GetRed_Player();
	blue_player = skiller->GetBlue_Player();
	red_player->CreatePlayer(main_window, input, map, blue_player, skiller, Red_Player);
	blue_player->CreatePlayer(main_window, input, map, red_player, skiller, Blue_Player);
	gameIsRun = true;
	return 0;
}

int Game::DestroyPlay()
{
	red_player->Clear();
	blue_player->Clear();
	map->Clear();
	return 0;
}

const wchar_t* Game::Getskill_name(int index)
{
	return skiller->Getskill_name(index);
}

const wchar_t* Game::Getskill_flag_sum(int sum)
{
	switch (sum)
	{
	case 1:
		return L"1";
	case 2:
		return L"2";
	case 3:
		return L"3";
	case 4:
		return L"4";
	case 5:
		return L"5";
	case 6:
		return L"6";
	case 7:
		return L"7";
	case 8:
		return L"8";
	}
	return L"0";
}

int Game::Getskill_sum()
{
	return skiller->Getskill_sum();
}
