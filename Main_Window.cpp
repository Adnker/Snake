#include "Main_Window.h"
#include "Game.h"

static SDL_Color WHITE = { 255,255,255,255 };//白色
static SDL_Color BLACK = { 0,0,0,255 };//黑色
static SDL_Color RED = { 255,0,0,255 };//红色
static SDL_Color BLUE = { 0,0,255,255 };//蓝色
static SDL_Color LITTLE_BLACK = { 200,200,200,255 };//灰色


int Main_Window::GameIsEnd(int flag_Player_)
{
	game->gameIsRun = false;
	flag_Player = flag_Player_;
	flagWindow = GameoverWindow;
	SDL_DestroyWindow(window);
	CreatNewWindow("Snake", 300, 300, 200, 200);
	return 0;
}

int Main_Window::CreatNewWindow(const char* title, int x, int y, int w, int h)
{
	if (window) {
		SDL_DestroyWindow(window);
	}
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

int Main_Window::CreatWindow(Game* game_, class Player* red_player_,
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
	SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
	SDL_RenderClear(renderer);

	DrawLineColor(0, 0, 700, 0,BLACK);

	//绘制一条小蛇
	if (!mouse_window) {
		mouse_window = new Mouse_Window(input);
	}
	mouse_window->Updata();//更新鼠标移动
	//绘制鼠标移动线路
	auto point_sum = mouse_window->Getpoint();
	for (int i = 1; i < point_sum.size(); i++) {
		DrawLine(point_sum[i - 1]->x, point_sum[i - 1]->y, point_sum[i]->x, point_sum[i]->y);
	}

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
	}

	//绘制缓冲区
	SDL_RenderPresent(renderer);
	return 0;
}

int Main_Window::Draw_FrightWindow()
{
	flagWindow = FrightWindow;
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
	move_point = red_player->Getmove_point();//获取红方移动数组
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);//设置着色器颜色为红色
	int now = 1;
	//遍历移动数组并绘制
	for (int before = 0; now < move_point.size(); now++) {
		DrawLine(move_point[before]->x, move_point[before]->y,
			move_point[now]->x, move_point[now]->y);
		before++;
	}
	move_point = blue_player->Getmove_point();//获取蓝方移动数组
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);//设置着色器颜色为蓝色
	now = 1;
	//遍历移动数组并绘制
	for (int before = 0; now < move_point.size(); now++) {
		DrawLine(move_point[before]->x, move_point[before]->y,
			move_point[now]->x, move_point[now]->y);
		before++;
	}

	//绘制玩家基地
	//temp.x被初始为0，当x>0时玩家基地被选定
	temp = red_player->Getjidi_point();//获取红方基地坐标
	if (temp.x > 0) { FillRect(temp.x, temp.y, 50, 50, &RED); }
	temp = blue_player->Getjidi_point();//获取蓝方基地坐标
	if (temp.x > 0) { FillRect(temp.x, temp.y, 50, 50, &BLUE); }

	//绘制玩家预选框
	temp = red_player->Getyuxuan_point();//获取红方预选框坐标
	FillRect(temp.x, temp.y, 20, 20, &RED);
	temp = blue_player->Getyuxuan_point();//获取蓝方预选框坐标
	FillRect(temp.x, temp.y, 20, 20, &BLUE);

	//绘制玩家提示窗口
	int size = window_msg.size();
	if (size > 0)
	{
		for (int i = 0; i < size; i++)
		{
			if (window_msg[i]->liveTime > 100) {
				//每个提示框循环绘制99次 绘制完成后将其删除
				window_msg.erase(
					window_msg.begin() + i, window_msg.begin() + i + 1);
				break;//跳出循环
			}
			FillRect(window_msg[i]->rect.x, window_msg[i]->rect.y,
				window_msg[i]->rect.w, window_msg[i]->rect.h, &LITTLE_BLACK);
			DrawRect(window_msg[i]->rect.x, window_msg[i]->rect.y,
				window_msg[i]->rect.w, window_msg[i]->rect.h, &BLACK);
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
	DrawTTF(L"开始游戏", BLACK, { 200,100,100,40 });
	DrawLine(180, 150, 320, 150);
	//DrawRect(200, 200, 100, 50, &BLACK);
	DrawTTF(L"技能介绍", BLACK, { 200,200,100,40 });
	DrawLine(180, 250, 320, 250);
	//获取鼠标坐标
	Point* nowPoint = input->GetNowPoint();
	//判断鼠标是否进入“开始游戏”按钮区
	if (nowPoint->x < 300 && nowPoint->x > 200
		&& nowPoint->y > 100 && nowPoint->y < 150)
	{
		//移动到键上
		FillRect(150, 120, 20, 20, &RED);
		//按下键
		if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down)
		{
			flagWindow = FrightWindow;
			CreatNewWindow("Snake", 100,100,700,800);
			game->CreatePlay();
		}
	}
	else if (nowPoint->x < 300 && nowPoint->x > 200
		&& nowPoint->y > 200 && nowPoint->y < 250)
	{
		//移动到键上
		FillRect(150, 220, 20, 20, &RED);
		//按下键
		if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down)
		{
			flagWindow = FrightWindow;
			CreatNewWindow("Snake", 100, 100, 700, 800);
			game->CreatePlay();
		}
	}

	return 0;
}

int Main_Window::Draw_GameOverWindow()
{
	SDL_Rect rect = { 50,30,100,50 };
	flagWindow = GameoverWindow;
	game->DestroyPlay();
	if (flag_Player == Red_Player) {
		DrawTTF(L"蓝方胜利", BLUE, rect);
	}
	else {
		DrawTTF(L"红方胜利", RED, rect);
	}
	DrawTTF(L"左键回到主页", BLACK, { 20,100,160,50 });
	if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down) {
		CreatNewWindow("Snake", 100, 100, 500, 500);
		flagWindow = MainWindow;
	}
	return 0;
}

void Main_Window::DrawLine(int x1, int y1, int x2, int y2)
{
	//绘制线
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Main_Window::DrawLineColor(int x1, int y1, int x2, int y2, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	DrawLine(x1, y1, x2, y2);
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

void Main_Window::FillRect(int x, int y, int w, int h, SDL_Color* color)
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

void Main_Window::DrawTTF(const wchar_t* text, SDL_Color color, SDL_Rect rect)
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
