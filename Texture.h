#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H
#include "SDL_image.h"
#include <string>
#include <unordered_map>

//图片
/*
* 主要用于加载图片并对外开放图片接口
*/
class Texture
{
public:
	Texture(SDL_Renderer* renderer);//加载基本图片
	SDL_Texture* Loading(const std::string fileName);//加载图片
	int Draw(const std::string fileName, SDL_Rect* rect1, SDL_Rect* rect2);//绘制图片
	int ChangRenderer(SDL_Renderer* renderer);//修改着色器
private:
	//着色器
	SDL_Renderer* renderer;
	std::unordered_map<std::string, SDL_Texture*> texture;
};

#endif