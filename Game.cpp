#include "Game.h"

int Game::OpenGame()
{
	isRuning = true;
	//创建各个类
	input = Input();
	input.CreateInput();
	main_window = Main_Window();
	if (main_window.CreatWindow(this,&red_player,&blue_player) > 0) { isRuning = false; return false; }

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

		
		input.Updata();
		//在战斗界面才更新玩家操作
		if (main_window.GetFlag() == FrightWindow)
		{
			red_player.Updata();
			blue_player.Updata();
		}
		main_window.Updata();

	}
}

int Game::Shutdown()
{
	main_window.Shutdown();
	SDL_Quit();
	return 0;
}

int Game::CreatePlay()
{
	map = Map();
	map.CreateMap();
	red_player = Player();
	red_player.CreatePlayer(&main_window,&input, &map, Red_Player);
	blue_player = Player();
	blue_player.CreatePlayer(&main_window,&input, &map, Blue_Player);
	return 0;
}

int Game::DestroyPlay()
{
	red_player.~Player();
	blue_player.~Player();
	map.~Map();
	return 0;
}
