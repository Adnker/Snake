#include "Main_Window.h"
#include "Game.h"

static SDL_Color WHITE = { 255,255,255,255 };//白色
static SDL_Color BLACK = { 0,0,0,255 };//黑色
static SDL_Color RED = { 255,0,0,255 };//红色
static SDL_Color BLUE = { 0,0,255,255 };//蓝色
static SDL_Color LITTLE_BLACK = { 150,150,150,255 };//灰色

int Main_Window::CreatNewWindow(const char* title, int x, int y, int w, int h)
{
	//创建窗口
	window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN);
	//检查
	if (!window) {
		SDL_Log("%s", SDL_GetError());
		return Window_error;
	}
	//获取窗口对应的贴图器
	windowSurface = SDL_GetWindowSurface(window);

	//创建着色器
	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//检查
	if (!renderer) {
		SDL_Log("%s", SDL_GetError());
		return Renderer_error;
	}

	return All_true;
}

int Main_Window::CreatWindow(Game* game_,class Player* red_player_,
	Player* blue_player_)
{
	game = game_;
	input = game->GetInput();
	red_player = red_player_;
	blue_player = blue_player_;

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
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyWindow(window);
	return 0;
}

int Main_Window::Player_Window(const wchar_t* text_, SDL_Rect rect_)
{
	Window_Msg* temp = new Window_Msg();
	temp->text = text_;
	temp->rect = rect_;
	temp->liveTime = 0;
	window_msg.push_back(temp);
	return 0;
}

int Main_Window::Updata()
{
	if (!window) {
		CreatNewWindow("Snake", 100, 100, 500, 500);
		flagWindow = MainWindow;
	}
	//循环背景色
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);

	//黑色
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	DrawLine(0, 0, 900, 0);

	switch (flagWindow)
	{
		//首界面
	case MainWindow:
		Draw_MainWindow();
		break;
		//战斗界面
	case FrightWindow:
		Draw_FrightWindow();
		break;
	}

	//绘制缓冲区
	SDL_RenderPresent(renderer);
	return 0;
}

int Main_Window::Draw_FrightWindow()
{
	flagWindow = FrightWindow;
	if (input->GetKeyState(SDL_SCANCODE_ESCAPE) == Key_Down) {
		//输入ESC则退回到主界面
		flagWindow = MainWindow;//修改窗口标志
		//重新创建窗口
		SDL_DestroyWindow(window);
		CreatNewWindow("Snake", 100, 100, 500, 500);
		//回收为玩家分配的内存
		game->DestroyPlay();
		return 0;
	}
	//黑色
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	//绘制战斗窗口
	int i = 0;
	while (i <= 700) {
		//Y
		DrawLine(i, 0, i, 700);
		//X
		DrawLine(0, i, 700, i);
		i += 100;
	}
	DrawLine(350, 700, 350, 800);

	Point temp;
	vector<Point*> move_point;

	//绘制玩家路线
	move_point = red_player->Getmove_point();
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	int now = 1;
	for (int before = 0; now < move_point.size(); now++) {
		DrawLine(move_point[before]->x, move_point[before]->y,
			move_point[now]->x, move_point[now]->y);
		before++;
	}
	move_point = blue_player->Getmove_point();
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	now = 1;
	for (int before = 0; now < move_point.size(); now++) {
		DrawLine(move_point[before]->x, move_point[before]->y,
			move_point[now]->x, move_point[now]->y);
		before++;
	}

	//绘制玩家基地
	temp = red_player->Getjidi_point();
	if(temp.x > 0){ FillRect(temp.x, temp.y, 50, 50, &RED); }
	temp = blue_player->Getjidi_point();
	if (temp.x > 0) { FillRect(temp.x, temp.y, 50, 50, &BLUE); }

	//绘制玩家预选框
	temp = red_player->Getyuxuan_point();
	FillRect(temp.x, temp.y, 20, 20, &RED);
	temp = blue_player->Getyuxuan_point();
	FillRect(temp.x, temp.y, 20, 20, &BLUE);
	
	//绘制玩家提示窗口
	int size = window_msg.size();
	if (size > 0)
	{
		for (int i = 0; i < size; i++)
		{
			if (window_msg[i]->liveTime > 100) {
				window_msg.erase(
					window_msg.begin() + i, window_msg.begin() + i + 1);
				break;//跳出循环
			}
			FillRect(window_msg[i]->rect.x, window_msg[i]->rect.y,
				window_msg[i]->rect.w, window_msg[i]->rect.h, &LITTLE_BLACK);
			DrawTTF(window_msg[i]->text, BLACK, window_msg[i]->rect);
			window_msg[i]->liveTime++;
		}
	}

	return 0;
}

int Main_Window::Draw_MainWindow()
{
	flagWindow = MainWindow;
	//DrawRect(200, 100, 100, 50, &BLACK);
	DrawTTF(L"开始游戏", BLACK, {200,100,100,50});
	DrawLine(180, 150, 320, 150);
	//DrawRect(200, 200, 100, 50, &BLACK);
	DrawTTF(L"技能介绍", BLACK, { 200,200,100,50 });
	DrawLine(180, 250, 320, 250);
	//获取鼠标坐标
	Point* nowPoint = input->GetNowPoint();
	//判断鼠标是否进入“开始游戏”按钮区
	if (nowPoint->x < 300 && nowPoint->x > 200
		&& nowPoint->y > 100 && nowPoint->y < 150) 
	{
		//移动到键上
		FillRect(100, 100, 50, 50,&RED);
		//按下键
		if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down) 
		{
			flagWindow = FrightWindow;
			SDL_DestroyWindow(window);
			CreatNewWindow("Snake", 100, 50, 700, 800);
			game->CreatePlay();
		}
	}
	else if(nowPoint->x < 300 && nowPoint->x > 200
		&& nowPoint->y > 200 && nowPoint->y < 250)
	{
		//移动到键上
		FillRect(100, 200, 50, 50, &RED);
		//按下键
		if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down)
		{
			flagWindow = FrightWindow;
			SDL_DestroyWindow(window);
			CreatNewWindow("Snake", 100, 50, 700, 800);
			game->CreatePlay();
		}
	}
	
	return 0;
}

void Main_Window::DrawLine(int x1, int y1, int x2, int y2)
{
	//绘制线
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Main_Window::DrawRect(int x, int y, int w, int h, SDL_Color* color)
{
	//设置矩形信息
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	//设置填充颜色
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	//绘制矩形
	SDL_RenderDrawRect(renderer, &rect);
}

void Main_Window::FillRect(int x, int y, int w, int h,SDL_Color* color)
{
	//设置矩形信息
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	//设置填充颜色
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	//绘制矩形
	SDL_RenderFillRect(renderer, &rect);
}

void Main_Window::DrawTTF(const wchar_t * text, SDL_Color color,SDL_Rect rect)
{
	//将wchar_t转化为Uint16
	Uint16* inText = (Uint16*)text;
	//将字体信息转化为贴图器信息
	SDL_Surface* fontSurface = TTF_RenderUNICODE_Solid(font, inText, color);
	//将贴图器信息转化为纹理信息
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, fontSurface);
	//释放贴图器内存
	SDL_FreeSurface(fontSurface);
	//将纹理信息绘制到窗口
	SDL_RenderCopy(renderer, texture, 0, &rect);
}
