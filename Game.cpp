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
	if (main_window->CreatWindow(this, &red_player, &blue_player) > 0) { isRuning = false; return false; }

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
			if (gameIsRun) { red_player.Updata(); }
			if (gameIsRun) { blue_player.Updata(); }
		}
		main_window->Updata();
	}
	return 0;
}

int Game::Shutdown()
{
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
	skiller->CreateSkiller(&red_player, &blue_player);
	red_player.CreatePlayer(main_window, input, map, &blue_player, Red_Player);
	blue_player.CreatePlayer(main_window, input, map, &red_player, Blue_Player);
	gameIsRun = true;
	return 0;
}

int Game::DestroyPlay()
{
	red_player.Clear();
	blue_player.Clear();
	map->Clear();
	return 0;
}

const wchar_t* Game::Getskill_name(int index)
{
	return skiller->Getskill_name(index);
}

int Game::Getskill_sum()
{
	return skiller->Getskill_sum();
}
