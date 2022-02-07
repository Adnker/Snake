#pragma once
#ifndef MOUSE_WINDOW
#define MOUSE_WINDOW

#include <vector>
#include "Input.h"
#include "Main_Window.h"
using std::vector;

class Mouse_Window {
public:
	Mouse_Window(Input* input_, class Main_Window* main_window);
	//绘制小蛇
	int DrawSnake();
private:
	//捕获频率
	int flag_mouse_time;
	//删除速度
	int erase_time;
	//缓冲区
	vector<Point*> point_sum;

	//class
	class Input* input;
	class Main_Window* main_window;
};
#endif