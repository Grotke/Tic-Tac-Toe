#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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
	if(texture != nullptr)
	{
		SDL_QueryTexture(texture,NULL,NULL,&width,&height);	
	}
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

void LTexture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(texture,alpha);
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

void LTexture::createTextureFromFont(SDL_Renderer *ren, const std::string &message,const std::string &fontFile, SDL_Color color, int fontSize)
{
	TTF_Font *font = TTF_OpenFont(fontFile.c_str(),fontSize);
	if(font == nullptr)
	{
		std::cout << "Couldn't load font." << std::endl;
	}
	SDL_Surface *surf = TTF_RenderText_Blended(font,message.c_str(),color);
	if(surf == nullptr)
	{
		TTF_CloseFont(font);
		std::cout << "Couldn't produce font surface." << std::endl;
	}
	
	texture = SDL_CreateTextureFromSurface(ren,surf);
	if(texture == nullptr)
	{
		std::cout << "Couldn't create texture from font." << std::endl;
	}
	else
	{
		SDL_QueryTexture(texture,NULL,NULL,&width,&height);
	}
	SDL_FreeSurface(surf);	
	TTF_CloseFont(font);
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
