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
	int DrawSkill(const wchar_t* skill_name, SDL_Rect* rect1, SDL_Rect* rect2,int flag_);//绘制技能图片 flag为是否需要边框
	int ChangRenderer(SDL_Renderer* renderer);//修改着色器
	int LoadAllSkill();//加载全部技能图片
	SDL_Texture* GetSkillTexture(const wchar_t* name);//获取图片
	SDL_Texture* GetTexture(std::string name);//获取图片
private:
	//着色器
	SDL_Renderer* renderer;
	std::unordered_map<std::string, SDL_Texture*> texture;
	std::unordered_map<const wchar_t*, SDL_Texture*> tex_skill;
};

#endif