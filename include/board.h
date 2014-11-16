#include <SDL2/SDL.h>
#include "timer.h"
#include "ltexture.h"
#include "ai.h"

#ifndef BOARD_H_
#define BOARD_H_
class Board
{

	public:
		Board(SDL_Renderer *ren);
		~Board();
		void renderBoard(SDL_Renderer *ren);	
		void handleEvent(SDL_Event *event);

	private:
		bool insideBox(SDL_Rect *box);
		void constructBoard(int width, int height);
		void constructAnimationFrames(int width, int height);
		void toggleTurn();
		void checkForWin();
		void declareWinner();
		void loadTextures(SDL_Renderer *ren);
		void freeTextures();
		void makeMove(int row, int col);
		void makeAIMove();
		void checkIfAIShouldMove();
		
		static const int ANIMATION_FRAMES = 4;
		static const int BOARD_ROWS = 3;
		static const int BOARD_COLS = 3;
		static const int CELL_WIDTH = 200;
		static const int CELL_HEIGHT = 160;
		LTexture *currentMouseoverTexture;
		LTexture *currentPieceTexture;
		LTexture *oTexture;
		LTexture *xTexture;
		LTexture *xMouseover;
		LTexture *oMouseover;
		SDL_Rect board[BOARD_ROWS][BOARD_COLS];
		LTexture *clickState[BOARD_ROWS][BOARD_COLS];
		int frame[BOARD_ROWS][BOARD_COLS];
		bool mousedOver[BOARD_ROWS][BOARD_COLS];
		SDL_Rect spriteClips[ANIMATION_FRAMES];
		bool winner;
		bool draw;
		bool renderWinning;
		int winningState;
		int winRenderPingNumber;
		int aiRenderPingNumber;
		unsigned int oMap;
		unsigned int xMap;
		unsigned int *currentMap;
		unsigned int *aiPlayer;
		unsigned int *humanPlayer;
		unsigned int winStates[8] = {0x7,0x38,0x1C0,0x49,0x92,0x124,0x111,0x54};
		Timer timer;
		AI ai;
		bool locked;

};
#endif
