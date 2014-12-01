#include <SDL2/SDL.h>
#include "screen.h"

#ifndef SCREENGENERATOR_H_
#define SCREENGENERATOR_H_
class ScreenGenerator
{
	public:
		static Screen & createMainMenu(SDL_Renderer *ren);
		static Screen & createGameOver(SDL_Renderer *ren, void * winner);
		static Screen & createSelectScreen(SDL_Renderer *ren);
	private:
		const static int BUTTON_WIDTH = 100;
		const static int BUTTON_HEIGHT = 50;


};

#endif
