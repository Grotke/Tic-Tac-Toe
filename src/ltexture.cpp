#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include "ltexture.h"

LTexture::LTexture()
{
	texture = nullptr;
	width = 0;
	height = 0;
}

LTexture::LTexture(SDL_Renderer *ren, const std::string &path)
{
	loadFromFile(ren,path);
	width = 0;
	height = 0;
}

LTexture::~LTexture()
{
	free();
}

void LTexture::setSize(int textureWidth, int textureHeight)
{
	width = textureWidth;
	height = textureHeight;	
}

void LTexture::free()
{
	if(texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
		width = 0;
		height = 0;
	}	
}

void LTexture::render(SDL_Renderer * ren, int x, int y)
{
	SDL_Rect renderRect = {x, y, width, height};
	if(x != -1)
	{
		SDL_RenderCopy(ren,texture,nullptr,&renderRect);
	}
	else
	{
		SDL_RenderCopy(ren,texture,nullptr,nullptr);
	}
}

bool LTexture::loadFromFile(SDL_Renderer *ren, const std::string &path)
{
	bool success = true;
	texture = IMG_LoadTexture(ren,path.c_str());
	if(texture == nullptr)
	{
		std::cout << "Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	return success;
}

bool LTexture::isTextureSet()
{
	return texture != nullptr;
}
