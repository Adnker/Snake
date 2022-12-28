#include "Button.h"
#include "Input.h"

#define BUTTON_LEFT_X(i) button.at(i)->rectxy->x
#define BUTTON_LEFT_Y(i) button.at(i)->rectxy->y

int Button::Updata(Input* input)
{
	Point* now_point = input->GetNowPoint();//获取鼠标状态
	//遍历每一个按钮 更新按钮状态
	for (int i = 0; i < button.size(); i++) {
		if (InButtonRect(now_point,i) == true) {
			//左键
			if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Down) {
				button.at(i)->Left_state = Key_Down;
			}
			else if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Up) {
				button.at(i)->Left_state = Key_Up;
			}
			else if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_Keep) {
				button.at(i)->Left_state = Key_Keep;
			}
			else if (input->GetMouseState(SDL_BUTTON_LEFT) == Key_None) {
				button.at(i)->Left_state = Key_Move;
			}
			//右键
			if (input->GetMouseState(SDL_BUTTON_RIGHT) == Key_Down) {
				button.at(i)->Right_state = Key_Down;
			}
			else if (input->GetMouseState(SDL_BUTTON_RIGHT) == Key_Up) {
				button.at(i)->Right_state = Key_Up;
			}
			else if (input->GetMouseState(SDL_BUTTON_RIGHT) == Key_Keep) {
				button.at(i)->Right_state = Key_Keep;
			}
			else if (input->GetMouseState(SDL_BUTTON_RIGHT) == Key_None) {
				button.at(i)->Right_state = Key_Move;
			}
		}
		else {
			button.at(i)->Left_state = Key_None;
			button.at(i)->Right_state = Key_None;
		}
	}
	return true;
}

int Button::DrawButton(SDL_Renderer* renderer_)
{
	for (auto button_ : button) {
		if (button_->drawFlag)
		{
			//绘制背景
			if (button_->tex != NULL) {
				SDL_RenderCopy(renderer_, button_->tex, button_->rect1, button_->rectxy);
			}
			//绘制文字
			if (button_->text != NULL) {
				DrawTTF(button_->text, *button_->color, *button_->recttext, renderer_, button_->font);
			}
		}
	}
	return true;
}

int Button::GetButtonLeftState(BUTTONER index_)
{
	return button.at(index_)->Left_state;
}

int Button::GetButtonRightState(BUTTONER index_)
{
	return button.at(index_)->Right_state;
}

BUTTON* Button::GetButton(BUTTONER index_)
{
	return button.at(index_);
}

int Button::Clear()
{
	button.clear();
	return true;
}

void Button::DrawTTF(const wchar_t* text, SDL_Color color, SDL_Rect rect, SDL_Renderer* renderer_, TTF_Font* font)
{
	//将wchar_t转化为Uint16
	Uint16* inText = (Uint16*)text;
	//将字体信息转化为贴图器信息
	SDL_Surface* fontSurface = TTF_RenderUNICODE_Solid(font, inText, color);
	//将贴图器信息转化为纹理信息
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, fontSurface);
	//释放贴图器内存
	SDL_FreeSurface(fontSurface);
	//将纹理信息绘制到窗口
	SDL_RenderCopy(renderer_, texture, 0, &rect);
}

int Button::AddButton(const wchar_t* text_, SDL_Texture* tex_, SDL_Rect* rect1_, SDL_Rect* rectxy_, SDL_Rect* recttext, TTF_Font* font, SDL_Color* color_)
{
	if (rectxy_->w < 1) { return -1; }
	if (rectxy_->h < 1) { return -1; }
	BUTTON* temp_button = new BUTTON(text_, tex_, rect1_, rectxy_, recttext, font, color_);//创建新的按钮信息
	button.emplace_back(temp_button);//将按钮信息加入到数组中
	return button.size() - 1;//返回此按钮对应的索引作为按钮标识
}

int Button::AddButton(BUTTON* button_)
{
	return AddButton(button_->text, button_->tex, button_->rect1, button_->rectxy, button_->recttext, button_->font, button_->color);
}

int Button::AddButton(const wchar_t* text_, SDL_Texture* tex_, SDL_Rect* rect1_, SDL_Rect rectxy_, SDL_Rect recttext, TTF_Font* font, SDL_Color* color_)
{
	return AddButton(text_, tex_, rect1_, &rectxy_, &recttext, font, color_);
}

bool Button::InButtonRect(Point* now_point, int i)
{
	if (now_point->x > BUTTON_LEFT_X(i) && now_point->x < button.at(i)->rectxy->x + button.at(i)->rectxy->w &&
		now_point->y > BUTTON_LEFT_Y(i) && now_point->y < button.at(i)->rectxy->y + button.at(i)->rectxy->h) {
		return true;
	}
	else {
		return false;
	}
}
