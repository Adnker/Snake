#pragma once
#ifndef BUTTON_H
#define BUTTON_H
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include "Input.h"

/*用于保存按钮信息
* const wchar_t* text 保存按钮显示的文字
* TTF_Font* font 保存字体
* SDL_Texture* tex 保存按钮的背景图片
* SDL_Rect* rect1 保存按钮显示图片的抠图位置
* SDL_Rect* rectxy 保存按钮显示
* 对应SDL_RenderCopy函数的rect1 和 rect2
* 一般情况rect1设置为NULL
* int Left_state 保存按钮这一帧鼠标左键的状态
* int Right_state 保存按钮这一帧鼠标右键的状态
const int Key_Up = 0;
const int Key_Down = 1;
const int Key_Keep = 2;
const int Key_None = 3;
const int Key_Move = 4;
*int flag 用于动画的特殊标识
*/
struct BUTTON {
	BUTTON(const wchar_t* text_, SDL_Texture* tex_, SDL_Rect* rect1_, SDL_Rect* rectxy_, SDL_Rect* recttext_, TTF_Font* font_, SDL_Color* color_) {
		text = text_;
		font = font_;
		color = color_;
		tex = tex_;
		if (rect1_ == NULL) {
			rect1 = NULL;
		}
		else {
			rect1 = new SDL_Rect(*rect1_);
		}
		if (rectxy_ == NULL) {
			rectxy = NULL;//将绘制不出来
		}
		else {
			rectxy = new SDL_Rect(*rectxy_);
		}
		if (recttext_ == NULL) {
			recttext = NULL;
		}
		else {
			recttext = new SDL_Rect(*recttext_);
		}
	}
	BUTTON(BUTTON* button_) {
		text = button_->text;
		font = button_->font;
		color = button_->color;
		tex = button_->tex;
		rect1 = button_->rect1;
		rectxy = button_->rectxy;
		recttext = button_->recttext;
	}
	const wchar_t* text;
	TTF_Font* font;
	SDL_Color* color;
	SDL_Texture* tex;
	SDL_Rect* rect1;
	SDL_Rect* recttext;
	SDL_Rect* rectxy;
	int Left_state = -1;
	int Right_state = -1;
	int flag = 0;
	int drawFlag = true;
};

/*用对应按钮在数组中的索引作为按钮的标识*/
typedef int BUTTONER;

class Button
{
public:
	int Updata(class Input* input_);//更新每个按钮状态
	int DrawButton(SDL_Renderer* renderer_);//绘制这一帧
	int GetButtonLeftState(BUTTONER index_);//获取按钮左键状态
	int GetButtonRightState(BUTTONER index_);//获取按钮右键状态
	BUTTON* GetButton(BUTTONER index_);//获取按钮信息
	int Clear();//清空按钮

	//绘制文字
	void DrawTTF(const wchar_t* text, SDL_Color color, SDL_Rect rect, SDL_Renderer* renderer, TTF_Font* font);

	BUTTONER AddButton(const wchar_t* text_, SDL_Texture* tex_, SDL_Rect* rect1_, SDL_Rect* rectxy_, SDL_Rect* recttext, TTF_Font* font, SDL_Color* color_);//添加按钮
	BUTTONER AddButton(BUTTON* button_);//添加按钮
	BUTTONER AddButton(const wchar_t* text_, SDL_Texture* tex_, SDL_Rect* rect1_, SDL_Rect rectxy_, SDL_Rect recttext, TTF_Font* font, SDL_Color* color_);//添加按钮
protected:
	bool InButtonRect(Point* now_point,int i);
private:
	std::vector<BUTTON*> button;
};

#endif