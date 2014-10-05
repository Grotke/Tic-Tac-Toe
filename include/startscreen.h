#include "screen.h"
#include "button.h"
#include <SDL.h>

class StartScreen : public Screen
{
    public:
        StartScreen();
        virtual void render(SDL_Renderer* ren);
        virtual ~StartScreen();

    private:
        static const int NUM_OF_BUTTONS = 1;
        Button screenButtons[NUM_OF_BUTTONS];
};
