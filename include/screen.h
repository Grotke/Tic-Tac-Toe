#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "button.h"
#include "ltexture.h"

#ifndef SCREEN_H_
#define SCREEN_H_
class Screen
{
    public:
	Screen();
	~Screen();
        void render(SDL_Renderer* ren);
	void loadBackground(SDL_Renderer *ren,const std::string &backgroundPath);
        void clearScreen();
        void deleteScreen();
        void addButton(Button button);
        void disableAllButtons();
        void enableAllButtons();
	void handleEvent(SDL_Event *e);

    private:
	std::vector<Button> buttons;
	LTexture *background;
};

#endif
