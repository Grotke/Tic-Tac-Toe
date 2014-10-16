#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "customevents.h"
#include "button.h"
#include "ltexture.h"

Button::Button(int x, int y, int width, int height, CustomEvent eventToRegister)
{
    buttonX = x;
    buttonY = y;
    buttonW = width;
    buttonH = height;
    currentState = ButtonState::NORMAL;
    eventOnClick = eventToRegister;
    enabled = true;
    renderable = true;
}

Button::~Button()
{
    free();
}

void Button::setSize(int width, int height)
{
    buttonW = width;
    buttonH = height;
}


void Button::setPosition(int x, int y)
{
    buttonX = x;
    buttonY = y;
}

bool Button::insideButton()
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    bool inside = true;
    if(mouseX < buttonX
       || mouseX > buttonX + buttonW
       || mouseY < buttonY
       || mouseY > buttonY + buttonH)
    {
        inside = false;
    }

    return inside;
}

void Button::render(SDL_Renderer* ren)
{
    if(renderable){
   	 buttonTextures[static_cast<int>(currentState)]->setSize(buttonW,buttonH);
    	buttonTextures[static_cast<int>(currentState)]->render(ren,buttonX,buttonY);
    }
}


bool Button::setTexturesIndivdual(SDL_Renderer* ren, const std::string &normalPath, const std::string &mouseoverPath, const std::string &clickedPath)
{
    bool success = true;

    buttonTextures[static_cast<int>(ButtonState::NORMAL)] = TextureSharedPtr(new LTexture(ren,normalPath));
    buttonTextures[static_cast<int>(ButtonState::MOUSEOVER)] = TextureSharedPtr(new LTexture(ren,mouseoverPath));
    buttonTextures[static_cast<int>(ButtonState::CLICKED)] = TextureSharedPtr(new LTexture(ren,clickedPath));

    for(int i = 0; i < TOTAL_BUTTON_STATES; i++)
    {
        if(!buttonTextures[i]->isTextureSet())
        {
            std::cout << "Error: " << SDL_GetError() << std::endl;
            success = false;
        }
    }
    return success;
    
}

void Button::handleEvent(SDL_Event* e)
{
    if(enabled){
        if(insideButton() && e->type == SDL_MOUSEBUTTONDOWN)
        {
            currentState = ButtonState::CLICKED;

            SDL_Event event;
            SDL_zero(event);
            event.type = SDL_USEREVENT;
            event.user.code = static_cast<int>(eventOnClick);
            SDL_PushEvent(&event);
        }
        else if(e->type == SDL_MOUSEBUTTONUP)
        {
            currentState = ButtonState::NORMAL;
        }
        else if(insideButton() && e->type == SDL_MOUSEMOTION)
        {
            currentState = ButtonState::MOUSEOVER;
        }
        else
        {
            currentState = ButtonState::NORMAL;
        }
    }
}

void Button::free()
{
    renderable = false;
    for(int i = 0; i < TOTAL_BUTTON_STATES; i++)
    {
	buttonTextures[i] = nullptr;
    }
}

void Button::disable()
{
    currentState = ButtonState::NORMAL;
    enabled = false;
}

void Button::enable()
{
    enabled = true;
}

bool Button::isEnabled()
{
    return enabled;
}
