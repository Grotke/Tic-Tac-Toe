#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "ltexture.h"
#include "screen.h"
#include "button.h"

Screen::Screen()
{
	background = nullptr;	

}

Screen::~Screen()
{
	deleteScreen();
}

void Screen::addButton(Button button)
{
	buttons.push_back(button);
}

void Screen::render(SDL_Renderer *ren)
{
	if(background)
	{
		background->render(ren,NULL,NULL);
	}
	for(std::vector<Button>::iterator it = buttons.begin(); it != buttons.end(); ++it)
	{
		it->render(ren);
	}
	int destinationIndex = 0;
	for(std::vector<LTexture*>::iterator iter = messages.begin(); iter != messages.end(); ++iter)
	{
		(*iter)->render(ren,NULL,&textDestinations.at(destinationIndex));
		destinationIndex++;
	}
}

SDL_Rect Screen::addText(SDL_Renderer *ren, const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize)
{
	LTexture *messageTexture = new LTexture();
	messageTexture->createTextureFromFont(ren,message,fontFile,color,fontSize);
	messages.push_back(messageTexture);
	SDL_Rect textDimensions = {0,0,messageTexture->getWidth(), messageTexture->getHeight()};
	return textDimensions;
}

void Screen::addTextRenderDestination(SDL_Rect dest)
{
	textDestinations.push_back(dest);
}

void Screen::disableAllButtons()
{
	for(std::vector<Button>::iterator it = buttons.begin(); it != buttons.end(); ++it)
	{
		it->disable();
	}
}

void Screen::enableAllButtons()
{
	for(std::vector<Button>::iterator it = buttons.begin(); it != buttons.end(); ++it)
	{
		it->enable();
	}
}

void Screen::deleteScreen()
{
	if(background)
	{
		background->free();
	}
	for(std::vector<Button>::iterator it = buttons.begin(); it != buttons.end(); ++it)
	{
		it->free();
	}
}

void Screen::handleEvent(SDL_Event *event)
{
	for(std::vector<Button>::iterator it = buttons.begin(); it != buttons.end(); ++it)
	{
		it->handleEvent(event);
	}
}

void Screen::loadBackground(SDL_Renderer *ren,const std::string &path)
{
	background = new LTexture(ren,path);
	if(!background)
	{
		std::cout << "Background failed to load." << std::endl;	
	}	
}

void Screen::setBackgroundAlpha(Uint8 alpha)
{
	background->setAlpha(alpha);

}
