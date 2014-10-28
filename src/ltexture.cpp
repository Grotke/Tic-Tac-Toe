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

void LTexture::render(SDL_Renderer * ren, SDL_Rect *source, SDL_Rect *destination)
{
	SDL_RenderCopy(ren,texture,source,destination);
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
