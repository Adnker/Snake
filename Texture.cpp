#include "Texture.h"

Texture::Texture(SDL_Renderer* renderer_)
{
	renderer = renderer_;
}

SDL_Texture* Texture::Loading(const std::string fileName)
{
	std::string way = "Texture\\";
	way += fileName;
	//加载文件
	SDL_Surface* face = IMG_Load(way.c_str());
	if (!face)
	{
		SDL_Log("error is face %s", SDL_GetError());
		return 0;
	}
	//创建纹理图片
	SDL_Texture* texture = SDL_CreateTexture(renderer, 0, 0, 0, 0);
	texture = SDL_CreateTextureFromSurface(renderer, face);
	//释放内存
	SDL_FreeSurface(face);
	if (!texture)
	{
		SDL_Log("error is texture %s", SDL_GetError());
		return 0;
	}
	return texture;
}

int Texture::Draw(const std::string fileName, SDL_Rect* rect1, SDL_Rect* rect2)
{
	SDL_Texture* tex = nullptr;
	//声明迭代器查找需要贴图的文件
	auto iter = texture.find(fileName);
	if (iter != texture.end())
	{
		tex = iter->second;
	}
	else {
		tex = Loading(fileName);
		texture.emplace(fileName, tex);
	}
	if (SDL_RenderCopy(renderer, tex, rect1, rect2) == -1)
	{
		SDL_Log("Map is error %s", SDL_GetError());
		return false;
	}
	return true;
}

int Texture::DrawSkill(const wchar_t* skill_name, SDL_Rect* rect1, SDL_Rect* rect2, int flag_)
{
	SDL_Texture* tex = nullptr;
	auto iter = tex_skill.find(skill_name);
	if (iter != tex_skill.end())
	{
		tex = iter->second;
	}
	if (SDL_RenderCopy(renderer, tex, rect1, rect2) == -1)
	{
		SDL_Log("Map is error %s", SDL_GetError());
		return false;
	}
	if (flag_) {
		iter = tex_skill.find(L"k1");
		if (iter != tex_skill.end())
		{
			tex = iter->second;
		}
		rect2->x -= 2;
		rect2->y -= 2;
		rect2->w += 4;
		rect2->h += 4;
		if (SDL_RenderCopy(renderer, tex, rect1, rect2) == -1)
		{
			SDL_Log("Map is error %s", SDL_GetError());
			return false;
		}
	}
}

int Texture::ChangRenderer(SDL_Renderer* renderer_)
{
	renderer = renderer_;
	texture.clear();
	tex_skill.clear();
	return 0;
}

int Texture::LoadAllSkill()
{
	if (!tex_skill.empty()) { return 0; }
	tex_skill.emplace(L"k1", Loading("k1.png"));
	tex_skill.emplace(L"路障", Loading("luzhang.png"));
	tex_skill.emplace(L"传送", Loading("chuansong.png"));
	tex_skill.emplace(L"穿身", Loading("chuanshen.png"));
	tex_skill.emplace(L"追击", Loading("zhuiji.png"));
	tex_skill.emplace(L"疾跑", Loading("jipao.png"));
	tex_skill.emplace(L"箭行", Loading("jianxing.png"));
	tex_skill.emplace(L"控制", Loading("kongzhi.png"));
	tex_skill.emplace(L"护盾", Loading("hudun.png"));
	tex_skill.emplace(L"交换", Loading("jiaohuan.png"));
	return 0;
}

SDL_Texture* Texture::GetSkillTexture(const wchar_t* name)
{
	auto iter = tex_skill.find(name);
	if (iter != tex_skill.end())
	{
		return  iter->second;
	}
	else {
		return NULL;
	}
}

SDL_Texture* Texture::GetTexture(std::string name)
{
	//声明迭代器查找需要贴图的文件
	auto iter = texture.find(name);
	if (iter != texture.end())
	{
		return iter->second;
	}
	else {
		SDL_Texture* tex = Loading(name);
		texture.emplace(name, tex);
		return tex;
	}
}
