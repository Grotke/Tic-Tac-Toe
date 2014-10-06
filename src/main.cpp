#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "button.h"
#include "customevents.h"

const int SCREEN_WIDTH = 640;
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
    Uint8 trans = 0xFF;
    int nextScreen = 0;
    Button button = Button(300,200,BUTTON_WIDTH,BUTTON_HEIGHT,CustomEvent::GAMESTARTED);
    button.setTexturesIndivdual(ren,"../assets/normalState.png","../assets/mouseoverState.png","../assets/clickedState.png");

    while(!nextScreen)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_USEREVENT)
            {
                if(e.user.code == (int)CustomEvent::GAMESTARTED)
                {
                    blue = 0;
                    button.disable();
                }
            }
            button.handleEvent(&e);
            if(e.type == SDL_QUIT)
            {
                nextScreen = 1;
            }
            SDL_SetRenderDrawColor(ren, red,green,blue, trans);
            SDL_RenderClear(ren);
            button.render(ren);
            SDL_RenderPresent(ren);

            if(!button.isEnabled())
            {
                SDL_Delay(2000);
                button.enable();
            }
        }
    }
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

