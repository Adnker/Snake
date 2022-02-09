#include "Main_Window.h"
#include "Game.h"


/*
* 初始化函数
*/
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


/*
* 析构函数
*/
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


/*
* 绘制一条线
* 从 x1,y1 画一条线到 x2,y2
* DrawLine是需要自己设定颜色
* DrawLineColoe需要传入颜色值 见DrawLineColor
*/
void Main_Window::DrawLine(int x1, int y1, int x2, int y2)
{
	//绘制线
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}


/*
* 绘制一条线
* 使用color的颜色，从x1,y1 回一条线到 x2,y2
* DrawLine是需要自己设定颜色 见DrawLine
* DrawLineColoe需要传入颜色值
*/
void Main_Window::DrawLineColor(int x1, int y1, int x2, int y2, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	DrawLine(x1, y1, x2, y2);
}


/*
* 绘制一个边框矩形
* 以x,y为矩形左上角顶点，开始绘制一个宽为w，高为h的矩形，线条颜色为color
* DrawRect绘制的是一个边框矩形
* FillRect绘制的是一个填充矩形 见FillRect
*/
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


/*
* 绘制一个填充矩形
* 以x,y为矩形左上角顶点，开始绘制一个宽为w，高为h的矩形，填充颜色为color
* DrawRect绘制的是一个边框矩形 见DrawRect
* FillRect绘制的是一个填充矩形
*/
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


/*
* 绘制文字
* 在rect的位置绘制颜色为color文本为text的文字
*/
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


/*
* 绘制图片
* 调用Texture类的Draw 见Texture类
* 从图片路径为fileName(包括后缀)的图片中截取位置为rect1(NULL时截取全部)的小图片绘制在rect2的位置
* 绘制技能图片时使用专用的函数通道DrawSkill 见DrawSkill
*/
void Main_Window::DrawPicture(const std::string fileName, SDL_Rect* rect1, SDL_Rect rect2)
{
	texture->Draw(fileName, rect1, &rect2);
}


/*
* 绘制技能图片
* 调用Texture类的DrawSkill 见Texture类
* 从图片名字为skill_name的图片中截取位置为rect1(NULL时截取全部)的小图片绘制在rect2的位置
* 绘制非技能图片时使用一般函数通道Draw 见Draw
*/
void Main_Window::DrawSkill(const wchar_t* skill_name, SDL_Rect* rect1, SDL_Rect rect2, int flag_)
{
	texture->DrawSkill(skill_name, rect1, &rect2, flag_);
}


/*
* 游戏结束时调用
* 传入败方的flag_player标识
*/
int Main_Window::GameIsEnd(int flag_Player_)
{
	game->gameIsRun = false;//将游戏运行标识设置为结束
	flag_Player = flag_Player_;//传递失败方的标识
	flagWindow = GameoverWindow;//窗口设置为游戏结束窗口
	game->DestroyPlay();//销毁窗口
	CreatNewWindow(&rect_Main_Window);//创建新的窗口
	return 0;
}


/*
* 获取游戏模式
*/
int Main_Window::GetGameModel()
{
	return model;
}


/*
* 修改玩家的技能
* 传入对应的技能索引index_
*/
void Main_Window::ChangeSkill(int index_)
{
	if (red_player->Getskill()->empty()) {
		red_player->Changeskill(index_);//修改红方玩家的技能选择
	}
	else {
		blue_player->Changeskill(index_);//修改蓝方玩家技能
		//双方都选择完技能，游戏开始

		b_flagWindow = flagWindow;
		flagWindow = FrightWindow;
		CreatNewWindow(&rect_Fright_Window);
		texture->LoadAllSkill();
	}
}


/*
* 创建一个新的窗口
* 销毁原先的窗口，并创建一个新的窗口，窗口位置为rect
*/
int Main_Window::CreatNewWindow(SDL_Rect* rect)
{
	if (window) {
		SDL_DestroyWindow(window);
	}
	//创建窗口
	window = SDL_CreateWindow("Snake", rect->x, rect->y, rect->w, rect->h, SDL_WINDOW_SHOWN);
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


/*
* 对外提供给Player类
* 将在战斗界面添加一个提示窗口，提示文本为text_ 位置为rect_, 提示时间为window_time_, 玩家标识为flag_
*/
int Main_Window::Player_Window(const wchar_t* text_, SDL_Rect rect_, int& window_time_, int flag_player_)
{
	//检查时间是否合理
	if (window_time_ != 0) { return false; }
	Window_Msg* temp = new Window_Msg(text_, rect_, flag_player_);
	window_msg.push_back(temp);
	window_time_ = 1;//开始计时
	return true;
}


/*
* 获取当前窗口状态
*/
int Main_Window::GetFlag()
{
	return flagWindow;
}


/*
* 更新函数
*/
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


/*
* 获取窗口模式
*/
int Main_Window::GetGameModel()
{
	return model;
}


/*
* 绘制主界面窗口
*/
int Main_Window::Draw_MainWindow()
{
	flagWindow = MainWindow;
	int button_x = 200;
	int button_y = 100;
	int button_w = 100;
	int button_h = 40;
	int jianju = 45;
	int picture_h = 40;
	//首次进入界面需要添加按钮
	if (b_flagWindow != MainWindow) {
		//添加按钮
		button->Clear();
		button->AddButton(L"开始游戏", texture->GetTexture("yun.png"), NULL,
			{ button_x - picture_jianju_x,button_y * 1,button_w + picture_jianju_w,button_h },
			{ button_x,button_y * 1,button_w,button_h }, font, &BLACK);
		button->AddButton(L"模式选择", texture->GetTexture("yun.png"), NULL,
			{ button_x - picture_jianju_x,button_y * 2,button_w + picture_jianju_w,button_h },
			{ button_x,button_y * 2,button_w,button_h }, font, &BLACK);
		button->AddButton(L"技能介绍", texture->GetTexture("yun.png"), NULL,
			{ button_x - picture_jianju_x,button_y * 3,button_w + picture_jianju_w,button_h },
			{ button_x,button_y * 3,button_w,button_h }, font, &BLACK);
	}
	b_flagWindow = flagWindow;
	DrawPicture("background.png", NULL, { 0,0,rect_Main_Window.w,rect_Main_Window.h });//绘制背景
	button->DrawButton(renderer);//绘制全部按钮


	BUTTONER Button1 = 0;
	BUTTONER Button2 = 1;
	BUTTONER Button3 = 2;
	button->Updata(input);//更新全部按钮状态
	//第一个按钮
	switch (button->GetButtonLeftState(Button1))
	{
	case Key_Move:
		DrawPicture("buttonRight.png", NULL, { button_x - jianju, button_y * 1, picture_h, picture_h });//绘制选中提示图片
		break;
	case Key_Down:
		game->CreatePlay();//创建玩家
		switch (model) {
		case BaseModel:
			b_flagWindow = flagWindow;
			flagWindow = FrightWindow;
			CreatNewWindow(&rect_Fright_Window);
			break;
		case SkillModel:
			b_flagWindow = flagWindow;
			flagWindow = SkillWindow;
			texture->LoadAllSkill();//让texture加载全部的技能图片
			break;
		case FrightModel:
			b_flagWindow = flagWindow;
			flagWindow = FrightWindow;
			CreatNewWindow(&rect_Fright_Window);
			texture->LoadAllSkill();//让texture加载全部的技能图片
			break;
		default:
			game->Shutdown();
			break;
		}
		break;
	}
	//第二个按钮
	switch (button->GetButtonLeftState(Button2))
	{
	case Key_Move:
		DrawPicture("buttonRight.png", NULL, { button_x - jianju, button_y * 2, picture_h, picture_h });
		break;
	case Key_Down:
		b_flagWindow = flagWindow;
		flagWindow = ModelWindow;
	}
	//第三个按钮
	switch (button->GetButtonLeftState(Button3))
	{
	case Key_Move:
		DrawPicture("buttonRight.png", NULL, { button_x - jianju, button_y * 3, picture_h, picture_h });
		break;
	case Key_Down:
		b_flagWindow = flagWindow;
		flagWindow = JieshaoWindow;
	}
	DrawTTF(L"主界面", BLACK, { 210,25,fontSize * 3,30 });
	return 0;
}


/*
* 绘制游戏结束界面窗口
*/
int Main_Window::Draw_GameOverWindow()
{
	flagWindow = GameoverWindow;//将窗口标识设置为游戏结束窗口标识
	const wchar_t* text;//显示的文本内容
	SDL_Color color;//文本颜色
	std::string name;//图片名字
	DrawPicture("background.png", NULL, { 0,0,rect_Main_Window.w,rect_Main_Window.h });//绘制背景图片
	//判断哪一方失败 哪一方失败就绘制对手胜利
	if (flag_Player == Red_Player) {
		text = L"蓝方获得胜利";
		name = "bluedown.png";
		color = BLUE;
	}
	else {
		text = L"红方获得胜利";
		name = "reddown.png";
		color = RED;
	}
	DrawTTF(L"左键回到主页", BLACK, { 50,200,160,50 });//提示用户左键返回主窗口
	DrawTTF(text, color, { 175,25,fontSize * 6,25 });
	SDL_Rect rect = { 140,25,25,25 };
	texture->Draw(name, NULL, &rect);
	if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down) {
		b_flagWindow = flagWindow;
		flagWindow = MainWindow;//将窗口标识设置为主窗口标识
	}
	return 0;
}


/*
* 绘制模式选择界面窗口
*/
int Main_Window::Draw_ModelWindow()
{
	flagWindow = ModelWindow;
	//文本框架
	int x = 200;
	int y = 100;
	int w = 100;
	int h = 40;
	if (b_flagWindow != flagWindow) {
		button->Clear();
		button->AddButton(L"普通训练", texture->GetTexture("yun.png"), NULL,
			{ x - picture_jianju_x,y * 1,w + picture_jianju_w,h },
			{ x,y * 1,w,h }, font, &BLACK);
		button->AddButton(L"技能训练", texture->GetTexture("yun.png"), NULL,
			{ x - picture_jianju_x,y * 2,w + picture_jianju_w,h },
			{ x,y * 2,w,h }, font, &BLACK);
		button->AddButton(L"竞技模式", texture->GetTexture("yun.png"), NULL,
			{ x - picture_jianju_x,y * 3,w + picture_jianju_w,h },
			{ x,y * 3,w,h }, font, &BLACK);
	}
	b_flagWindow = flagWindow;
	DrawPicture("background.png", NULL, { 0,0,rect_Main_Window.w,rect_Main_Window.h });
	button->DrawButton(renderer);
	button->Updata(input);
	for (int flag_model = 1; flag_model <= 3; flag_model++) {
		switch (button->GetButtonLeftState(flag_model - 1))
		{
		case Key_Down:
			b_flagWindow = flagWindow;
			flagWindow = MainWindow;
			model = flag_model;
			break;
		case Key_Move:
			DrawPicture("buttonRight.png", NULL, { x - 45, y * flag_model, 40, 40 });
			break;
		default:
			break;
		}
	}
	DrawTTF(L"选择模式", BLACK, { 195,25,fontSize * 4,30 });
	return 0;
}


/*
* 绘制技能介绍界面窗口
*/
int Main_Window::Draw_JieshaoWindow()
{
	return 0;
}


//将点位转化为普通地图点位
#define MAPXY * 100 + 50
//将点位转化为基地地图点位
#define JIDIXY * 100 + 25
//将点位转化为区域地图点位
#define QUYUXU * 100 + 20


/*
* 绘制战斗界面窗口
*/
int Main_Window::Draw_FrightWindow()
{
	flagWindow = FrightWindow;//设置窗口标识为rect_Main_Window
	DrawPicture("backgroundFright.png", NULL, { 0,0,rect_Fright_Window.w,rect_Fright_Window.h });//绘制背景图片
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);//设置着色器颜色为黑色

	/*//////////////////////////////////////////////////////////////////////////////////*/
	//绘制战斗窗口的线条
	int i = 0;
	while (i <= 700) {
		//Y
		DrawLine(i, 0, i, 700);
		//X
		DrawLine(0, i, 700, i);
		i += 100;
	}
	DrawLine(350, 700, 350, 800);//最顶上的线条

	if (model == FrightModel) {
		red_player->AddSkill();
		blue_player->AddSkill();
	}

	/*///////////////////////////////////////////////////////////////////////////////*/
	//绘制玩家行动路线
	int jidi_h = 50;//统一基地边长
	int quyu_h = 30;
	int index_now = 1;
	int index_before = 0;
	Point* point_before;
	SDL_Color color;
	bool needToDrawMove = true;
	const vector<Move_point*>* red_point;//保存玩家移动数组
	const vector<Move_point*>* blue_point;//保存玩家移动数组

	red_point = red_player->GetMove_point();//获取玩家的移动数组
	blue_point = blue_player->GetMove_point();//获取蓝方移动数组
	if (!red_point->empty()) {
		FillRect(red_point->at(0)->point->x JIDIXY, red_point->at(0)->point->y JIDIXY, jidi_h, jidi_h, &RED);//绘制玩家的基地
	}
	if (!blue_point->empty()) {
		FillRect(blue_point->at(0)->point->x JIDIXY, blue_point->at(0)->point->y JIDIXY, jidi_h, jidi_h, &BLUE);//绘制蓝方基地
	}
	while (needToDrawMove) {
		needToDrawMove = false;
		//红方
		if (index_now < red_point->size()) {
			needToDrawMove = true;
			color = RED;
			//移动路线
			if (red_point->at(index_now)->flag == NULL) {
				point_before = red_point->at(index_before)->point;
				if (red_point->at(index_before)->flag == QUYU || red_point->at(index_before)->flag > 0) {
					int i = index_before - 1;
					while (red_point->at(i)->flag == QUYU || red_point->at(i)->flag > 0) {
						i--;
					}
					point_before = red_point->at(i)->point;
				}
				DrawLineColor(red_point->at(index_now)->point->x MAPXY, red_point->at(index_now)->point->y MAPXY,
					point_before->x MAPXY, point_before->y MAPXY, color);
			}
			//基地
			else if (red_point->at(index_now)->flag == JIDI) {
				FillRect(red_point->at(index_now)->point->x JIDIXY, red_point->at(index_now)->point->y JIDIXY,
					jidi_h, jidi_h, &color);
			}
			//区域
			else if (red_point->at(index_now)->flag == QUYU) {
				FillRect(red_point->at(index_now)->point->x QUYUXU, red_point->at(index_now)->point->y QUYUXU,
					quyu_h, quyu_h, &color);
			}
			//虚路线
			else {
				point_before = red_point->at(red_point->at(index_now)->flag)->point;
				DrawLineColor(red_point->at(index_now)->point->x MAPXY, red_point->at(index_now)->point->y MAPXY,
					point_before->x MAPXY, point_before->y MAPXY, color);
			}
		}
		//蓝方
		if (index_now < blue_point->size()) {
			needToDrawMove = true;
			color = BLUE;
			//普通路线
			if (blue_point->at(index_now)->flag == NULL) {
				point_before = blue_point->at(index_before)->point;
				if (blue_point->at(index_before)->flag == QUYU || blue_point->at(index_before)->flag > 0) {
					int i = index_before - 1;
					while (blue_point->at(i)->flag == QUYU || blue_point->at(i)->flag > 0) {
						i--;
					}
					point_before = blue_point->at(i)->point;
				}
				DrawLineColor(blue_point->at(index_now)->point->x MAPXY, blue_point->at(index_now)->point->y MAPXY,
					point_before->x MAPXY, point_before->y MAPXY, color);
			}
			//基地
			else if (blue_point->at(index_now)->flag == JIDI) {
				FillRect(blue_point->at(index_now)->point->x JIDIXY, blue_point->at(index_now)->point->y JIDIXY,
					jidi_h, jidi_h, &color);
			}
			//区域
			else if (blue_point->at(index_now)->flag == QUYU) {
				FillRect(blue_point->at(index_now)->point->x QUYUXU, blue_point->at(index_now)->point->y QUYUXU,
					quyu_h, quyu_h, &color);
			}
			//虚路线
			else {
				point_before = blue_point->at(blue_point->at(index_now)->flag)->point;
				DrawLineColor(blue_point->at(index_now)->point->x MAPXY, blue_point->at(index_now)->point->y MAPXY,
					point_before->x MAPXY, point_before->y MAPXY, color);
			}
		}
		index_now++;
		index_before++;
	}

	/*///////////////////////////////////////////////////////////////////////////////*/
	//绘制玩家预选框
	Point temp;//保存玩家预选框的坐标
	string name;//保存玩家图片名字
	SDL_Rect rect;//保存玩家图片矩形
	int h_yu = 30;//统一预选框的高度
	temp = red_player->Getyuxuan_point();//获取红方预选框坐标
	name = red_player->Getpicture_name();//获取红方图片名字
	rect = { temp.x, temp.y, h_yu, h_yu };
	texture->Draw(name, NULL, &rect);
	temp = blue_player->Getyuxuan_point();//获取蓝方预选框坐标
	name = blue_player->Getpicture_name();//获取蓝方图片名字
	rect = { temp.x, temp.y, h_yu, h_yu };
	texture->Draw(name, NULL, &rect);

	/*/////////////////////////////////////////////////////////////////////////////*/
	//绘制玩家提示窗口
	if (window_msg.size() > 0)
	{
		for (int i = 0; i < window_msg.size(); i++)
		{
			//对每个提示窗口进行判断，如果窗口的显示时间大于提示窗口提示时间，要对窗口进行销毁，反之进行绘制
			if (window_msg.at(i)->liveTime > DeadTime) {
				//销毁窗口
				window_msg.erase(window_msg.begin() + i, window_msg.begin() + i + 1);
			}
			else {
				if (window_msg.at(i)->flag == Red_Player) {
					window_msg.at(i)->rect.x = red_player->Getyuxuan_point().x;
					window_msg.at(i)->rect.y = red_player->Getyuxuan_point().y + window_msg.at(i)->rect.h;
				}
				else {
					window_msg.at(i)->rect.x = blue_player->Getyuxuan_point().x;
					window_msg.at(i)->rect.y = blue_player->Getyuxuan_point().y + window_msg.at(i)->rect.h;
				}
				//绘制窗口
				//判断提示窗口是否超出窗体，超出窗体则对窗口信息进行修正，避免提示框越出窗口

				if (window_msg.at(i)->rect.x + window_msg.at(i)->rect.w > rect_Fright_Window.w) {
					window_msg.at(i)->rect.x = rect_Fright_Window.w - window_msg.at(i)->rect.w;
				}
				if (window_msg.at(i)->rect.y + window_msg.at(i)->rect.h > rect_Fright_Window.h) {
					window_msg.at(i)->rect.y = rect_Fright_Window.h - window_msg.at(i)->rect.h - 30;
				}

				DrawPicture("backgroundPlayer.png", NULL, { window_msg.at(i)->rect.x, window_msg.at(i)->rect.y,
					window_msg.at(i)->rect.w, window_msg.at(i)->rect.h });//绘制提示窗口背景
				DrawTTF(window_msg.at(i)->text, LITTLE_BLACK, window_msg.at(i)->rect);//绘制提示窗口提示文字
				window_msg.at(i)->liveTime++;//增加提示窗口显示时间
			}
		}
	}

	int skill_sum_h = 25;
	if (red_player->SkillNeedShow())
	{
		SDL_Rect rectShow = red_player->ShowSkill_rect();
		if (rectShow.x + rectShow.w * 2 + 5 > rect_Fright_Window.w) {
			rectShow.x = rect_Fright_Window.w - rectShow.w * 2 - 5;
		}
		if (rectShow.y + rectShow.h > rect_Fright_Window.h) {
			rectShow.y = rect_Fright_Window.h - rectShow.h - 30;
		}
		DrawSkill(game->Getskill_name(red_player->Getskill()->at(red_player->ShowSkill_index())), NULL, rectShow);
		rectShow.x = rectShow.x + rectShow.w - skill_sum_h;
		rectShow.y = rectShow.y + rectShow.h - skill_sum_h;
		rectShow.h = skill_sum_h;
		rectShow.w = skill_sum_h;
		DrawTTF(game->Getskill_flag_sum(red_player->Getskill_sum(red_player->ShowSkill_index())), WHITE, rectShow);
	}
	if (blue_player->SkillNeedShow())
	{
		SDL_Rect rectShow = blue_player->ShowSkill_rect();
		if (rectShow.x + rectShow.w * 2 + 5 > rect_Fright_Window.w) {
			rectShow.x = rect_Fright_Window.w - rectShow.w * 2 - 5;
		}
		if (rectShow.y + rectShow.h > rect_Fright_Window.h) {
			rectShow.y = rect_Fright_Window.h - rectShow.h - 30;
		}
		DrawSkill(game->Getskill_name(blue_player->Getskill()->at(blue_player->ShowSkill_index())), NULL, rectShow);
		rectShow.x = rectShow.x + rectShow.w - skill_sum_h;
		rectShow.y = rectShow.y + rectShow.h - skill_sum_h;
		rectShow.h = skill_sum_h;
		rectShow.w = skill_sum_h;
		DrawTTF(game->Getskill_flag_sum(blue_player->Getskill_sum(blue_player->ShowSkill_index())), WHITE, rectShow);
	}
	return 0;
}


/*
* 绘制技能选择界面窗口
*/
int Main_Window::Draw_SkillWindow()
{
	flagWindow = SkillWindow;
	//按钮属性
	int button_x = 200;//按钮显示位置
	int button_y = 100;//按钮显示位置
	int button_w = 100;//按钮宽
	int button_h = 40;//按钮高
	SDL_Rect text1 = { 0,420,80,50 };//上一页按钮
	SDL_Rect text2 = { 420,420,80,50 };//下一页按钮
	BUTTONER Button1 = 0;//按钮1标识
	BUTTONER Button2 = 1;//按钮2标识
	BUTTONER Button3 = 2;//按钮3标识
	BUTTONER Button4 = 3;//按钮4标识
	BUTTONER Button5 = 4;//按钮5标识


	if (b_flagWindow != flagWindow) {
		button->Clear();
		button->AddButton(L"无技能", texture->GetTexture("k3.png"), NULL,
			{ button_x - picture_jianju_x,button_y * 1,button_w + picture_jianju_w,button_h },
			{ button_x,button_y * 1,button_w,button_h }, font, &LITTLE_BLACK);
		button->AddButton(L"无技能", texture->GetTexture("k3.png"), NULL,
			{ button_x - picture_jianju_x,button_y * 2,button_w + picture_jianju_w,button_h },
			{ button_x,button_y * 2,button_w,button_h }, font, &LITTLE_BLACK);
		button->AddButton(L"无技能", texture->GetTexture("k3.png"), NULL,
			{ button_x - picture_jianju_x,button_y * 3,button_w + picture_jianju_w,button_h },
			{ button_x,button_y * 3,button_w,button_h }, font, &LITTLE_BLACK);
		button->AddButton(NULL, texture->GetTexture("buttonLeft.png"), NULL, text1, text1, font, &BLACK);
		button->AddButton(NULL, texture->GetTexture("buttonRight.png"), NULL, text2, text2, font, &BLACK);
		button->GetButton(Button4)->drawFlag = false;//一开始的时候上一页不用绘制
	}
	b_flagWindow = flagWindow;
	DrawPicture("background.png", NULL, { 0,0,rect_Main_Window.w,rect_Main_Window.h });//绘制背景



	//index + Button_ = 对应的技能索引
	int Skill1 = index + Button1;//技能1索引
	int Skill2 = index + Button2;//技能2索引
	int Skill3 = index + Button3;//技能3索引
	//修改按钮显示的技能文字
	button->GetButton(Button1)->text = game->Getskill_name(Skill1);
	button->GetButton(Button2)->text = game->Getskill_name(Skill2);
	button->GetButton(Button3)->text = game->Getskill_name(Skill3);
	button->DrawButton(renderer);//绘制全部按钮


	button->Updata(input);//更新全部按钮的状态
	int picture_h = 40;//选中提示图片边长
	int skill_index = -1;//需要显示的技能索引
	int picture_index = -1;//需要显示的提示图片索引
	//第一个按钮
	bool Skill1_index_isTrue = Skill1 <= game->Getskill_sum();
	if (Skill1_index_isTrue) {
		switch (button->GetButtonLeftState(Button1))
		{
		case Key_Down:
			ChangeSkill(Skill1);//修改玩家技能标识
			index = 1;
			break;
		case Key_Move:
			picture_index = Button1;
			skill_index = Skill1;
			break;
		}
	}


	//第二个按钮
	bool Skill2_index_isTrue = Skill2 <= game->Getskill_sum();
	if (Skill2_index_isTrue) {
		switch (button->GetButtonLeftState(Button2))
		{
		case Key_Down:
			ChangeSkill(Skill2);;//修改玩家技能标识
			index = 1;
			break;
		case Key_Move:
			picture_index = Button2;
			skill_index = Skill2;
			break;
		}
	}


	//第三个按钮
	bool Skill3_index_isTrue = Skill3 <= game->Getskill_sum();
	if (Skill3_index_isTrue) {
		switch (button->GetButtonLeftState(Button3))
		{
		case Key_Down:
			ChangeSkill(Skill3);;//修改玩家技能标识
			index = 1;
			break;
		case Key_Move:
			picture_index = Button3;
			skill_index = Skill3;
			break;
		}
	}


	//绘制需要显示的技能
	if (skill_index > -1) {
		int y = button_y * (skill_index % 3);
		if (y == 0) { y = button_y * 3; }
		DrawSkill(game->Getskill_name(skill_index), NULL, { button_x - picture_jianju_x - button_h,y,button_h,button_h });//绘制技能图标提示
	}
	if (picture_index > -1) {
		picture_index++;
		DrawPicture("buttonRight.png", NULL, { button_x - picture_h, button_y * picture_index, picture_h, picture_h });//绘制选中提示图片
	}


	bool index_isTrue;
	bool needToDraw;
	needToDraw = index > 3;
	if (needToDraw) {
		button->GetButton(Button4)->drawFlag = true;
		//上一页 第四个按钮
		int& Button4_x = button->GetButton(Button4)->rectxy->x;//按钮4x坐标
		int& Button4_flag = button->GetButton(Button4)->flag;//按钮4特殊标识
		index_isTrue = index - 3 > 0;
		switch (button->GetButtonLeftState(Button4))
		{
		case Key_Down:
			if (index_isTrue) { index -= 3; }
			break;
		case Key_Move:
			if (Button4_flag == 0) { Button4_x++; if (Button4_x > 30) { Button4_flag = 1; } }
			else { Button4_x--; if (Button4_x < 1) { Button4_flag = 0; } }
			break;
		default:
			Button4_x = text1.x;
			Button4_flag = 0;
			break;
		}
	}
	else {
		button->GetButton(Button4)->drawFlag = false;
	}


	needToDraw = Skill3 < game->Getskill_sum();
	if (needToDraw) {
		button->GetButton(Button5)->drawFlag = true;
		//下一页 第五个按钮
		int& Button5_x = button->GetButton(Button5)->rectxy->x;//按钮5x坐标
		int& Button5_flag = button->GetButton(Button5)->flag;//按钮5特俗标识
		index_isTrue = index + 3 <= game->Getskill_sum();
		switch (button->GetButtonLeftState(Button5))
		{
		case Key_Down:
			if (index_isTrue) { index += 3; }
			break;
		case Key_Move:
			if (Button5_flag == 0) { Button5_x--; if (Button5_x < 500 - text2.w - 30) { Button5_flag = 1; } }
			else { Button5_x++; if (Button5_x > 500 - text2.w) { Button5_flag = 0; } }
			break;
		default:
			Button5_x = text2.x;
			Button5_flag = 0;
			break;
		}
	}
	else {
		button->GetButton(Button5)->drawFlag = false;
	}



	const wchar_t* text;//显示的文本内容
	SDL_Color color;//文本颜色
	std::string name;//图片名字
	if (red_player->Getskill()->empty()) {
		text = L"红方选择技能";
		name = "reddown.png";
		color = RED;
	}
	else {
		text = L"蓝方选择技能";
		name = "bluedown.png";
		color = BLUE;
	}
	DrawTTF(text, color, { 175,25,fontSize * 6,30 });
	SDL_Rect rect = { 140,25,30,30 };
	texture->Draw(name, NULL, &rect);
	return 0;
}