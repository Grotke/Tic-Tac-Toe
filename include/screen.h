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
	void addTextRenderDestination(SDL_Rect dest);
	SDL_Rect addText(SDL_Renderer *ren, const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize);
	void setBackgroundAlpha(Uint8 alpha);

    private:
	std::vector<Button> buttons;
	std::vector<LTexture *> messages;
	std::vector<SDL_Rect> textDestinations;
	LTexture *background;
};

#endif
