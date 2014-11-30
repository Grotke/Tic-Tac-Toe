#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#ifndef LTEXTURE_H_
#define LTEXTURE_H_
class LTexture
{
	public:
		LTexture();
		LTexture(SDL_Renderer *ren, const std::string &path);
		~LTexture();
		void setSize(int textureWidth, int textureHeight);
		bool loadFromFile(SDL_Renderer *ren, const std::string &path);
		bool isTextureSet();
		void free();
		void setAlpha(Uint8 alpha);
		void render(SDL_Renderer *ren,SDL_Rect *source = nullptr, SDL_Rect *destination = nullptr);
		void createTextureFromFont(SDL_Renderer *ren,const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize);
		int getWidth() {return width;}
		int getHeight() {return height;}
	private:
		SDL_Texture *texture;
		int width;
		int height;
};


#endif
