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
	game->DestroyPlay();
	return 0;
}

int Main_Window::GetGameModel()
{
	return model;
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

int Main_Window::CreatWindow(Game* game_)
{
	game = game_;
	input = game->GetInput();
	mouse_window = new Mouse_Window(input, this);
	rander = new Rander();

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
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyWindow(window);
	return 0;
}

int Main_Window::Player_Window(const wchar_t* text_, SDL_Rect rect_, int& flag_window_)
{
	if (flag_window_ != 0) { return false; }
	Window_Msg* temp = new Window_Msg();
	temp->text = text_;
	temp->rect = rect_;
	temp->liveTime = 0;
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
		CreatNewWindow("Snake", 100, 100, 500, 500);
		flagWindow = MainWindow;
	}
	//循环背景色
	SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
	SDL_RenderClear(renderer);

	DrawLineColor(0, 0, 700, 0, BLACK);

	//绘制一条小蛇
	mouse_window->DrawSnake();

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

	//技能模式
	if (model == SkillModel) {
		//技能模式绘制玩家的技能显示
		const vector<int>* skill = red_player->Getskill();
		const wchar_t* skill_name = game->Getskill_name(skill->at(0));
		DrawTTF(skill_name, RED, { 0,700,fontSize * 3,40 });
		DrawTTF(game->Getskill_flag_sum(red_player->Getskill_sum()), RED, { 1,740,40,40 });

		skill = blue_player->Getskill();
		skill_name = game->Getskill_name(skill->at(0));
		DrawTTF(skill_name, BLUE, { 700 - fontSize * 3,700,fontSize * 3,40 });
		DrawTTF(game->Getskill_flag_sum(blue_player->Getskill_sum()), BLUE, { 700 - 41,740,40,40 });
	}
	//竞技模式
	else if(model == FrightModel){
		const vector<int>* skill = red_player->Getskill();
		for (int i = 0; i < 3; i++) {
			const wchar_t* skill_name = game->Getskill_name(skill->at(i));
			int w = fontSize * 3;
			int x = i * w;
			DrawTTF(skill_name, RED, { x,700,w,40 });
			DrawTTF(game->Getskill_flag_sum(red_player->Getskill_num(i)), RED, { x,740,40,40 });
		}
		const vector<int>* hand1 = blue_player->Getskill();
		for (int i = 0; i < 3; i++) {
			const wchar_t* skill_name = game->Getskill_name(hand1->at(i));
			int w = fontSize * 3;
			int x = (i + 1) * w;
			DrawTTF(skill_name, BLUE, { 700 - x,700,w,40 });
			DrawTTF(game->Getskill_flag_sum(blue_player->Getskill_num(i)), BLUE, { 700 - x,740,40,40 });
		}
	}

	//绘制玩家移动
	{
		int jidi_h = 50;
		const vector<Move_point*>* move_point = red_player->GetMove_point();//获取玩家的移动数组
		if (!move_point->empty()) {
			FillRect(move_point->at(0)->point->x, move_point->at(0)->point->y, jidi_h, jidi_h, &RED);//绘制玩家的基地
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);//设置着色器颜色为红色
			DrawMove(move_point, &RED);
		}

		move_point = blue_player->GetMove_point();//获取蓝方移动数组
		if (!move_point->empty()) {//绘制蓝方基地
			FillRect(move_point->at(0)->point->x, move_point->at(0)->point->y, jidi_h, jidi_h, &BLUE);
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);//设置着色器颜色为蓝色
			DrawMove(move_point, &BLUE);
		}
	}

	//绘制玩家预选框
	Point temp;
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
	DrawTTF(L"模式选择", BLACK, { 200,200,100,40 });
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
			game->CreatePlay();//创建玩家
			switch (model) {
			case BaseModel:
				flagWindow = FrightWindow;
				CreatNewWindow("Snake Firght", 200, 40, 700, 800);
				break;
			case SkillModel:
				flagWindow = SkillWindow;
				CreatNewWindow("Player1 chiose skill", 100, 100, 300, 300);
				break;
			case FrightModel:
				flagWindow = FrightWindow;

				CreatNewWindow("Snake Firght", 200, 40, 700, 800);
				break;
			default:
				game->Shutdown();
				break;
			}
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
			flagWindow = ModelWindow;
		}
	}

	return 0;
}

int Main_Window::Draw_GameOverWindow()
{
	SDL_Rect rect = { 50,30,100,50 };
	flagWindow = GameoverWindow;
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

int Main_Window::Draw_SkillWindow()
{
	flagWindow = SkillWindow;
	//选中正方形的边
	int h = 20;
	SDL_Rect name1 = { 100,20,90,40 };//技能一矩形
	SDL_Rect name2 = { 100,90,90,40 };//技能二矩形
	DrawLine(name1.x, name1.y + name1.h + 10, name1.x + name1.w, name1.y + name1.h + 10);
	DrawLine(name2.x, name2.y + name2.h + 10, name2.x + name2.w, name2.y + name2.h + 10);
	const wchar_t* skill_name = game->Getskill_name(index);
	if (skill_name) { DrawTTF(skill_name, BLACK, name1); }
	skill_name = game->Getskill_name(index + 1);
	if (skill_name) { DrawTTF(skill_name, BLACK, name2); }
	SDL_Rect text1 = { 0,250,fontSize * 3,40 };//文本一矩形
	SDL_Rect text2 = { 300 - fontSize * 3,250,fontSize * 3,40 };//文本二矩形
	DrawLine(text1.x, text1.y + text1.h + 10, text1.x + text1.w, text1.y + text1.h + 10);
	DrawLine(text2.x, text2.y + text2.h + 10, text2.x + text2.w, text2.y + text2.h + 10);
	DrawTTF(L"上一页", BLACK, text1);
	DrawTTF(L"下一页", BLACK, text2);
	//获取鼠标坐标
	Point* nowPoint = input->GetNowPoint();
	//判断鼠标是否进入按钮区
	//第一个技能区
	if (nowPoint->x > name1.x && nowPoint->x < name1.x + name1.w
		&& nowPoint->y > name1.y && nowPoint->y < name1.y + name1.h + 10)
	{
		//移动到键上
		FillRect(name1.x - h * 2, name1.y + 10, h, h, &RED);
		//按下键
		if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down)
		{
			if (red_player->Getskill()->at(0) == -1) {
				//修改玩家一的技能选择
				red_player->Changeskill(index);
				//轮到玩家二选择技能
				flagWindow = SkillWindow;
				index = 1;
				CreatNewWindow("Player2 chiose skill", 100, 100, 300, 300);
			}
			else {
				blue_player->Changeskill(index);
				flagWindow = FrightWindow;
				CreatNewWindow("Snake Firght", 200, 40, 700, 800);
				index = 1;
			}
		}
	}
	//第二个技能区
	else if (nowPoint->x > name2.x && nowPoint->x < name2.x + name2.w
		&& nowPoint->y > name2.y && nowPoint->y < name2.y + name2.h + 10)
	{
		//移动到键上
		FillRect(name2.x - h * 2, name2.y + 10, h, h, &RED);
		//按下键
		if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down)
		{
			if (red_player->Getskill()->at(0) == -1) {
				//修改玩家一的技能选择
				red_player->Changeskill(index + 1);
				//轮到玩家二选择技能
				index = 1;//重置索引
				CreatNewWindow("Player2 chiose skill", 100, 100, 300, 300);
			}
			else {
				blue_player->Changeskill(index + 1);
				flagWindow = FrightWindow;
				CreatNewWindow("Snake Firght", 200, 40, 700, 800);
				index = 1;
			}
		}
	}
	//上一页
	else if (nowPoint->x > text1.x && nowPoint->x < text1.x + text1.w
		&& nowPoint->y > text1.y && nowPoint->y < text1.y + text1.h + 10)
	{
		//移动到键上
		FillRect(text1.x + text1.w + h, text1.y + 10, h, h, &RED);
		//按下键
		if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down)
		{
			if (index > 1) { index -= 2; }
		}
	}
	//下一页
	else if (nowPoint->x > text2.x && nowPoint->x < text2.x + text2.w
		&& nowPoint->y > text2.y && nowPoint->y < text2.y + text2.h + 10)
	{
		//移动到键上
		FillRect(text2.x - h * 2, text2.y + 10, h, h, &RED);
		//按下键
		if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down)
		{
			if (index + 2 <= game->Getskill_sum()) { index += 2; }
		}
	}

	return 0;
}

int Main_Window::Draw_ModelWindow()
{
	flagWindow = ModelWindow;

	//文本框架
	int x = 200;
	int y = 100;
	int w = 100;
	int h = 40;

	//文本1
	DrawTTF(L"普通训练", BLACK, { x,y * 1,w,h });
	DrawLine(180, 150, 320, 150);
	//文本2
	DrawTTF(L"技能训练", BLACK, { x,y * 2,w,h });
	DrawLine(180, 250, 320, 250);
	//文本3
	DrawTTF(L"竞技模式", BLACK, { x,y * 3,w,h });
	DrawLine(180, 350, 320, 350);

	//获取鼠标坐标
	Point* nowPoint = input->GetNowPoint();
	for (int flag_model = 1; flag_model <= 3; flag_model++) {
		//判断鼠标是否进入“开始游戏”按钮区
		if (nowPoint->x < x + w && nowPoint->x > x
			&& nowPoint->y < y * flag_model + 50 + h && nowPoint->y > y * flag_model)
		{
			//移动到键上
			FillRect(x - 50, y * flag_model + 20, 20, 20, &RED);
			//按下键
			if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down)
			{
				flagWindow = MainWindow;
				model = flag_model;
			}
		}
	}
	return 0;
}

int Main_Window::DrawMove(const vector<Move_point*>* move_point, SDL_Color* color_)
{
	int jidi_h = 50;
	int quyu_h = 30;
	int index_now = 1;
	int index_before = 0;
	Point* point_now;
	Point* point_before;
	while (index_now < move_point->size()) {
		if (move_point->at(index_now)->flag == NULL) {
			point_before = move_point->at(index_before)->point;
			if (move_point->at(index_before)->flag == QUYU) {
				int i = index_before - 1;
				while (move_point->at(i)->flag == QUYU) {
					i--;
				}
				point_before = move_point->at(i)->point;
			}
			DrawLine(move_point->at(index_now)->point->x, move_point->at(index_now)->point->y,
				point_before->x,point_before->y);
		}
		else if (move_point->at(index_now)->flag == JIDI) {
			FillRect(move_point->at(index_now)->point->x, move_point->at(index_now)->point->y,
				jidi_h, jidi_h,color_);
		}
		else if (move_point->at(index_now)->flag == QUYU) {
			FillRect(move_point->at(index_now)->point->x, move_point->at(index_now)->point->y,
				quyu_h, quyu_h, color_);
		}
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
