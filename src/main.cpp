#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "screengenerator.h"
#include "button.h"
#include "customevents.h"
#include "screen.h"
#include "board.h"
#include "ltexture.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 480;
const int BUTTON_WIDTH = 100;
const int BUTTON_HEIGHT = 50;

void logSDLError(std::ostream &os, const std::string &msg)
{
    os << msg << " error: " << SDL_GetError() << std::endl;
}

int main(int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }
    
    if(TTF_Init() != 0)
    {
	logSDLError(std::cout, "TTF_Init");
	return 1;
    }
    SDL_Window *win = SDL_CreateWindow("Tic-Tac-Toe!",100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == nullptr)
    {
        logSDLError(std::cout, "CreateWindow");
        SDL_Quit();
        return 1;
    }

    SDL_Renderer * ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
    {
        SDL_DestroyWindow(win);
        logSDLError(std::cout, "CreateRenderer");
        SDL_Quit();
        return 1;
    }
    
    Uint8 red = 0xFF;
    Uint8 blue = 0xFF;
    Uint8 green = 0xFF;
    Uint8 trans = 255;
    
    

    int nextScreen = 0;
    Screen *currentScreen = &ScreenGenerator::createMainMenu(ren);
    Board *board = NULL;
    while(!nextScreen)
    {

        SDL_Event e;
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_USEREVENT)
            {
		if(e.user.code == static_cast<int>(CustomEvent::GAMEENDED))
		{
			currentScreen = &ScreenGenerator::createGameOver(ren);
		}
		if(e.user.code == static_cast<int>(CustomEvent::GAMERESTARTED))
		{
			board = NULL;
			currentScreen = &ScreenGenerator::createSelectScreen(ren);
		}
		if(e.user.code == static_cast<int>(CustomEvent::GOTO_MAINMENU))
		{
			currentScreen = &ScreenGenerator::createMainMenu(ren);
		}
		if(e.user.code == static_cast<int>(CustomEvent::GOTO_SELECTSCREEN))
		{
			currentScreen = &ScreenGenerator::createSelectScreen(ren);
		}
		if(e.user.code == static_cast<int>(CustomEvent::X_SELECTED))
		{
			currentScreen = NULL;
			if(board)
			{
				board->resetBoard('X');
			}
			else
			{
				board = new Board(ren, 'X');
			}
		}
		if(e.user.code == static_cast<int>(CustomEvent::O_SELECTED))
		{

			currentScreen = NULL;
			if(board)
			{
				board->resetBoard('O');
			}
			else
			{
				board = new Board(ren, 'O');
			}
		}
		if(e.user.code == static_cast<int>(CustomEvent::QUIT))
		{
			nextScreen = 1;
		}
            }
	    if(board)
	    { 
	    	board->handleEvent(&e);
	    }
	    if(currentScreen)
	    {
		currentScreen->handleEvent(&e);
       	    }
            if(e.type == SDL_QUIT)
            {
                nextScreen = 1;
            }
	}
            SDL_SetRenderDrawColor(ren, red,green,blue, trans);
	    SDL_RenderClear(ren);
	    if(board)
	    {
		board->render(ren);
	    }
	    if(currentScreen)
	    {
	    	currentScreen->render(ren);
	    }
            SDL_RenderPresent(ren);
    }
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

