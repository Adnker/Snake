#include "Input.h"

int Input::CreateInput()
{
	//初始化
	const Uint8* temp = SDL_GetKeyboardState(NULL);
	memcpy(nowKeyState, temp, SDL_NUM_SCANCODES);

	//将前一帧的数组初始化为0
	memset(beforeKeyState, 0, SDL_NUM_SCANCODES);
	return 0;
}

int Input::Updata()
{
	//交换键盘值
	memcpy(beforeKeyState, nowKeyState, SDL_NUM_SCANCODES);

	//获取新的键盘状态
	const Uint8* temp = SDL_GetKeyboardState(NULL);
	memcpy(nowKeyState, temp, SDL_NUM_SCANCODES);
	
	
	//交换鼠标状态
	beforeMouseState = nowMouseState;
	beforePoint = nowPoint;

	//获取新的鼠标状态
	nowMouseState = SDL_GetMouseState(&nowPoint.x, &nowPoint.y);

	return 0;
}

int Input::GetKeyState(SDL_Scancode key)
{
	//判断键盘状态
	if (beforeKeyState[key] == 0)
	{
		if (nowKeyState[key] == 0)
		{
			return Key_None;
		}
		else
		{
			return Key_Down;
		}
	}
	else
	{
		if (nowKeyState[key] == 0)
		{
			return Key_Up;
		}
		else
		{
			return Key_Keep;
		}
	}
}

int Input::GetMouseState(int button)
{
	//判断鼠标状态
	if ((beforeMouseState & SDL_BUTTON(button)) == 0)
	{
		if ((nowMouseState & SDL_BUTTON(button)) == 0)
		{
			return Key_None;
		}
		else
		{
			return Key_Down;
		}
	}
	else
	{
		if ((nowMouseState & SDL_BUTTON(button)) == 0)
		{
			return Key_Up;
		}
		else
		{
			return Key_Keep;
		}
	}
}
