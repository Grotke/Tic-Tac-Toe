#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "screen.h"
#include "button.h"

Screen::Screen()
{
	

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
	background->render(ren);
	for(std::vector<Button>::iterator it = buttons.begin(); it != buttons.end(); ++it)
	{
		it->render(ren);
	}
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
	background->free();
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
