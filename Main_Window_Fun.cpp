#include "Main_Window.h"
#include "Game.h"
#include <Windows.h>

int Main_Window::GameIsEnd(int flag_Player_)
{
	game->gameIsRun = false;//将游戏运行标识设置为结束
	flag_Player = flag_Player_;//传递失败方的标识
	flagWindow = GameoverWindow;//窗口设置为游戏结束窗口
	game->DestroyPlay();//销毁窗口
	CreatNewWindow(&rect_Main_Window);//创建新的窗口
	return 0;
}

int Main_Window::GetGameModel()
{
	return model;
}

void Main_Window::ChangeSkill(int index_)
{
	if (red_player->Getskill()->empty()) {
		red_player->Changeskill(index_);//修改红方玩家的技能选择
	}
	else {
		blue_player->Changeskill(index_);//修改蓝方玩家技能
		b_flagWindow = flagWindow;
		flagWindow = FrightWindow;
		CreatNewWindow(&rect_Fright_Window);
		texture->LoadAllSkill();
	}
}

int Main_Window::CreatNewWindow(SDL_Rect* rect)
{
	SDL_DestroyWindow(window);
	//创建窗口
	const char* name = "Snake";
	window = SDL_CreateWindow(name, rect->x, rect->y, rect->w, rect->h, SDL_WINDOW_SHOWN);
	//检查
	if (!window) {
		SDL_Log("%s", SDL_GetError());
		return Window_error;
	}
	//获取窗口对应的贴图器
	surface = SDL_GetWindowSurface(window);

	//创建着色器
	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//检查
	if (!renderer) {
		SDL_Log("%s", SDL_GetError());
		return Renderer_error;
	}
	texture->ChangRenderer(renderer);
	return All_true;
}

int Main_Window::CreatWindow(Game* game_)
{
	game = game_;
	input = game->GetInput();
	mouse_window = new Mouse_Window(input, this);
	rander = new Rander();
	texture = new Texture(renderer);
	button = new Button();
	b_flagWindow = FrightWindow;


	//初始化TTF文字库
	if (TTF_Init() == -1) {
		SDL_Log("%s", SDL_GetError());
		return TTF_Init_error;
	}
	//加载TTF文字
	font = TTF_OpenFont(fontText, fontSize);
	if (!font) {
		SDL_Log("%s", SDL_GetError());
		return TTF_Open_error;
	}
	return 0;
}

int Main_Window::Shutdown()
{
	delete rander;
	delete button;
	delete texture;
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyWindow(window);
	return 0;
}

int Main_Window::Player_Window(const wchar_t* text_, SDL_Rect rect_, int& flag_window_, int flag_)
{
	if (flag_window_ != 0) { return false; }
	Window_Msg* temp = new Window_Msg(text_, rect_, flag_);
	window_msg.push_back(temp);
	flag_window_ = 1;
	return true;
}

int Main_Window::GetFlag()
{
	return flagWindow;
}

int Main_Window::Updata(class Player* red_player_, class Player* blue_player_)
{
	red_player = red_player_;
	blue_player = blue_player_;
	if (!window) {
		flagWindow = MainWindow;
		CreatNewWindow(&rect_Main_Window);
	}
	//循环背景色
	SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
	SDL_RenderClear(renderer);

	DrawLineColor(0, 0, 700, 0, BLACK);

	switch (flagWindow)
	{
	case MainWindow://首界面
		Draw_MainWindow();
		break;
	case FrightWindow://战斗界面
		Draw_FrightWindow();
		break;
	case GameoverWindow://游戏结束界面
		Draw_GameOverWindow();
		break;
	case SkillWindow://技能选择界面
		Draw_SkillWindow();
		break;
	case ModelWindow://模式选择界面
		Draw_ModelWindow();
		break;
	default:
		DrawTTF(L"错误", RED, { 0,0,100,50 });
		break;
	}

	//绘制一条小蛇
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	mouse_window->DrawSnake();

	//绘制缓冲区
	SDL_RenderPresent(renderer);
	return 0;
}