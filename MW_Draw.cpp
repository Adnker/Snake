#include "Main_Window.h"

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

void Main_Window::DrawPicture(const std::string fileName, SDL_Rect* rect1, SDL_Rect rect2)
{
	texture->Draw(fileName, rect1, &rect2);
}

void Main_Window::DrawSkill(const wchar_t* skill_name, SDL_Rect* rect1, SDL_Rect rect2, int flag_)
{
	texture->DrawSkill(skill_name, rect1, &rect2, flag_);
}