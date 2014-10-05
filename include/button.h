#include <SDL.h>
#include <string>
#include "customevents.h"

#ifndef BUTTON_H_
#define BUTTON_H_
class Button
{
    public:
        Button(int x, int y, int width, int height, CustomEvent eventToRegister);
        ~Button();
        void free();
        void disable();
        void enable();
        bool isEnabled();
        void setClickAction();
        void handleEvent(SDL_Event* e);
        void setSize(int width, int height);
        void setPosition(int x, int y);
        void render(SDL_Renderer* ren);
        bool setTexturesIndivdual(SDL_Renderer* ren, const std::string &normalPath, const std::string &mouseoverPath, const std::string &clickedPath);

    private:
        bool enabled;
        CustomEvent eventOnClick;
        static const int TOTAL_BUTTON_STATES = 3;
        enum class ButtonState : char {NORMAL = 0,MOUSEOVER = 1,CLICKED = 2};
        int buttonX, buttonY, buttonW, buttonH;
        ButtonState currentState;
        bool insideButton();
        SDL_Texture* buttonTextures[TOTAL_BUTTON_STATES];
};

#endif
