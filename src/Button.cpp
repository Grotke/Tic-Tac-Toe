#include "button.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

Button::Button(int x, int y, int width, int height)
{
    buttonX = x;
    buttonY = y;
    buttonW = width;
    buttonH = height;
    currentState = ButtonState::NORMAL;
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
    SDL_Rect renderRect = {buttonX, buttonY,buttonW,buttonH};
    SDL_RenderCopy(ren,buttonTextures[(int)currentState],nullptr, &renderRect);
}

bool Button::setTexturesWithSheet(std::string &sheetPath)
{
    return true;
}

bool Button::setTexturesIndivdual(SDL_Renderer* ren,const std::string &normalPath, const std::string &mouseoverPath, const std::string &clickedPath)
{
    bool success = true;
    buttonTextures[(int)ButtonState::NORMAL] = IMG_LoadTexture(ren, normalPath.c_str());
    buttonTextures[(int)ButtonState::MOUSEOVER] = IMG_LoadTexture(ren, mouseoverPath.c_str());
    buttonTextures[(int)ButtonState::CLICKED] = IMG_LoadTexture(ren, clickedPath.c_str());
    for(int i = 0; i < TOTAL_BUTTON_STATES; i++)
    {
        if(buttonTextures[i] == nullptr)
        {
            std::cout << "Error: " << SDL_GetError() << std::endl;
            success = false;
        }
    }
    return success;
}

void Button::handleEvent(SDL_Event* e)
{
    if(insideButton() && e->type == SDL_MOUSEBUTTONDOWN)
    {
        currentState = ButtonState::CLICKED;
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

void Button::free()
{
    for(int i = 0; i < TOTAL_BUTTON_STATES; i++)
    {
        if(buttonTextures[i] != nullptr)
        {
            SDL_DestroyTexture(buttonTextures[i]);
        }
    }
}


void Button::setClickAction()
{

}
