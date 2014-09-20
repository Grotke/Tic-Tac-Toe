#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE = 40;
/*Log an SDL error with some error message to the output stream of our choice.
    @param os The output stream to write the message to
    @param msg The error message to write, format will be msg error: SDL_GetError()
*/

void logSDLError(std::ostream &os, const std::string &msg)
{
    os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture * loadTexture(const std::string &file, SDL_Renderer * ren)
{
    SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());

    if(texture == nullptr)
    {
        logSDLError(std::cout, "LoadTexture");
    }
    return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w = -1, int h = -1)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    if(w == -1 || h == -1)
    {
        SDL_QueryTexture(tex, NULL,NULL, &w, &h);
    }

    dst.w = w;
    dst.h = h;

    SDL_RenderCopy(ren, tex, NULL, &dst);
}

int main(int argc, char * argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Lesson 2",100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

    SDL_Texture * background = loadTexture("background1.png", ren);
    SDL_Texture *image = loadTexture("image1.png", ren);
    if (background == nullptr || image == nullptr)
    {
        SDL_DestroyTexture(image);
        SDL_DestroyTexture(background);
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }


    SDL_RenderClear(ren);
    int xTiles = SCREEN_WIDTH /TILE_SIZE;
    int yTiles = SCREEN_HEIGHT /TILE_SIZE;

    for(int i = 0; i < xTiles *yTiles; ++i)
    {
        int x = i % xTiles;
        int y = i /xTiles;
        renderTexture(background, ren, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);

    }

    int iW, iH;
    SDL_QueryTexture(image, NULL,NULL, &iW, &iH);
    int x = SCREEN_WIDTH /2 -iW/2;
    int y = SCREEN_HEIGHT/2 -iH/2;
    renderTexture(image, ren, x, y);
    SDL_RenderPresent(ren);

    SDL_Delay(2000);

    SDL_DestroyTexture(image);
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
