#include <SDL.h>
#include <string>

#ifndef BUTTON_H_
class Button
{
    public:
        Button(int x = 0, int y = 0, int width = 0, int height = 0);
        ~Button();
        void free();
        void setClickAction();
        void handleEvent(SDL_Event* e);
        void setSize(int width, int height);
        void setPosition(int x, int y);
        void render(SDL_Renderer* ren);
        bool setTexturesWithSheet(std::string &sheetPath);
        bool setTexturesIndivdual(SDL_Renderer* ren, const std::string &normalPath, const std::string &mouseoverPath, const std::string &clickedPath);

    private:
        static const int TOTAL_BUTTON_STATES = 3;
        enum class ButtonState : char {NORMAL = 0,MOUSEOVER = 1,CLICKED = 2};
        int buttonX, buttonY, buttonW, buttonH;
        ButtonState currentState;
        bool insideButton();
        SDL_Texture* buttonTextures[TOTAL_BUTTON_STATES];
};

#endif
