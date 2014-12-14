#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <ctype.h>
#include "timer.h"
#include "ltexture.h"
#include "board.h"
#include "ai.h"
#include "customevents.h"


Board::Board(SDL_Renderer *ren, char humanSymbol)
{
	initializeVariables();
	setUpTimer();
	setUpAI();
	loadTextures(ren);
	loadSounds();
        constructBoard(CELL_WIDTH,CELL_HEIGHT);
        constructAnimationFrames(CELL_WIDTH,CELL_HEIGHT);
  	setUpPlayers('X',humanSymbol);
}

Board::~Board()
{
	freeTextures();
	releaseTimer();	
}

bool Board::loadSounds()
{
	bool success = true;
	xSound = Mix_LoadWAV("../assets/xsound.wav");
	oSound = Mix_LoadWAV("../assets/osound.wav");
	if(!xSound || !oSound)
	{
	   success = false;
	}
	return success;	
}

void Board::resetBoard(char humanSymbol)
{
	initializeVariables();
	constructBoard(CELL_WIDTH, CELL_HEIGHT);
	setUpPlayers('X',humanSymbol);
}

void Board::initializeVariables()
{
	winner = false;
	draw = false;
	oMap = 0;
	xMap = 0;
	winningState = -1;
	renderWinning = true;
	locked = false;
}

void Board::setUpAI()
{
	ai = AI();
}

void Board::setUpPlayers(char firstPlayer, char humanSymbol)
{
	char lowerFirstPlayer = tolower(firstPlayer);
	char lowerHumanSymbol = tolower(humanSymbol);
	if(lowerFirstPlayer == 'x')
	{
	     currentMouseoverTexture = xMouseover;
    	     currentPieceTexture = xTexture;
    	     currentMap = &xMap;
	     currentSound = oSound;
	}
	else
	{
	    currentMouseoverTexture = oMouseover;
	    currentPieceTexture = oTexture;
	    currentMap = &oMap;
	    currentSound = xSound;	
	}
	if(lowerHumanSymbol == 'x')
	{
	    humanPlayer = &xMap;
	    aiPlayer = &oMap;			
	}
	else
	{
	    humanPlayer = &oMap;
	    aiPlayer = &xMap;
	}
}

void Board::setUpTimer()
{
	timer = Timer();
	timer.start();
	aiRenderPingNumber = timer.registerPingNumber();
	winRenderPingNumber = timer.registerPingNumber();
}

void Board::releaseTimer()
{
	timer.releasePingNumber(aiRenderPingNumber);
	timer.releasePingNumber(winRenderPingNumber);	
}

void Board::render(SDL_Renderer *ren)
{
	checkIfAIShouldMove();
	for(int i = 0; i < BOARD_ROWS; i++)
	{
		for(int j = 0; j < BOARD_COLS; j++)
		{ 
	            SDL_RenderSetViewport(ren, &board[i][j]);
		    if(winningState != -1 && ((winStates[winningState] >> (i*BOARD_ROWS+j)) & 0x1))
		    {	if(!timer.isPingTimeSet(winRenderPingNumber))
			{
				timer.startPingTime(300, winRenderPingNumber);
			}
			if(timer.pingTime(winRenderPingNumber))
			{
				renderWinning = !renderWinning;
				timer.startPingTime(300,winRenderPingNumber);	
			}
			if(renderWinning)
			{
				clickState[i][j]->render(ren,&spriteClips[frame[i][j]/10],nullptr);
			}
			
		    }
		    else if(clickState[i][j] != nullptr)
		    {
			clickState[i][j]->render(ren,&spriteClips[frame[i][j]/10],nullptr);
			if(frame[i][j] == 0)
			{
				Mix_PlayChannel(-1,currentSound,0);
			}
			if(frame[i][j]/10 < ANIMATION_FRAMES-1)
			{
				frame[i][j]++;
			}
		    }
		    else if(mousedOver[i][j])
		    {
			currentMouseoverTexture->render(ren);
		    }
		    if(clickState[i][j] != nullptr && frame[i][j]/10 < ANIMATION_FRAMES-1)
		    {
				frame[i][j]++;
		    }
				
		} 
	}
	SDL_RenderSetViewport(ren,NULL);
	boardHatchTexture->render(ren);
}

void Board::handleEvent(SDL_Event *e)
{
     if(!locked)
     {	
	if(currentMap != aiPlayer)
	{
	   if(e->type == SDL_MOUSEMOTION)
	   {
		for(int i = 0; i < BOARD_ROWS; i++)
		{
			for(int j = 0; j < BOARD_COLS; j++)
			{
				if(insideBox(&board[i][j]))
				{
					mousedOver[i][j] = true;
				}
				else
				{
					mousedOver[i][j] = false;
				}
			}
		}
	   }

		if(e->type == SDL_MOUSEBUTTONDOWN)
		{

			for(int i = 0; i < BOARD_ROWS; i++)
			{
				for(int j = 0; j < BOARD_COLS; j++)
				{
					if(insideBox(&board[i][j]) && !clickState[i][j])
					{
						makeMove(i, j);	
					}
				}
			}
		

		   }
	}
      }
}

void Board::checkIfAIShouldMove()
{
	if(currentMap == aiPlayer && !locked)
	{
		if(!timer.isPingTimeSet(aiRenderPingNumber))
		{
			timer.startPingTime(1000,aiRenderPingNumber);
		}
		else if(timer.pingTime(aiRenderPingNumber))
		{
			makeAIMove();
			timer.clearPingTime(aiRenderPingNumber);
		}
	}
}

void Board::makeMove(int row, int col)
{
	if(!clickState[row][col])
	{
		clickState[row][col] = currentPieceTexture;
		*currentMap = (*currentMap) | (0x1 << (row*BOARD_ROWS + col));
		checkForWin();
		if(draw || winner)
		{
			declareWinner();
		}
		else
		{
			toggleTurn();
		}
	}
}

bool Board::insideBox(SDL_Rect *box)
{
    bool inside = true;
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if(mouseX <= box->x
       || mouseX >= box->x + box->w
       || mouseY <= box->y
       || mouseY >= box->y + box->h)
    {
        inside = false;
    }

    return inside;
}

void Board::constructBoard(int width, int height)
{
	for(int i = 0; i < BOARD_ROWS; i++)
	{
		for(int j = 0; j < BOARD_COLS; j++)
		{
			SDL_Rect *boardSlot = &board[i][j];
			boardSlot->x = j*width;
			boardSlot->y = i*height;
			boardSlot->w = width;
			boardSlot->h = height;
			clickState[i][j] = nullptr;
			mousedOver[i][j] = false;
			frame[i][j] = 0;
		}
	}
}

void Board::constructAnimationFrames(int width, int height)
{
    for(int i = 0; i < ANIMATION_FRAMES; i++)
    {
    	spriteClips[i].x = i*width;
    	spriteClips[i].y = 0;
    	spriteClips[i].w = width;
    	spriteClips[i].h = height;
    }
}

void Board::toggleTurn()
{
	if(currentMouseoverTexture == xMouseover)
	{
		currentMouseoverTexture = oMouseover;
		currentPieceTexture = oTexture;
		currentMap = &oMap;
		currentSound = xSound;
	}
	else
	{
		currentMouseoverTexture = xMouseover;
		currentPieceTexture = xTexture;
		currentMap = &xMap;
		currentSound = oSound;
	}
}

void Board::checkForWin()
{
	unsigned int i = 0;
	while((*currentMap & winStates[i])!= winStates[i] && i < sizeof(winStates)/sizeof(*winStates) - 1)
	{
		i++;
	}

	if((*currentMap & winStates[i]) == winStates[i])
	{ 
		winner = true;
		winningState = i;
		locked = true;
	}
	else if((oMap | xMap) == 0x1FF)
	{
		draw = true;
		locked = true;
	}
}

void Board::declareWinner()
{
	if(draw)
	{
		SDL_Event event;
		SDL_zero(event);
		event.type = SDL_USEREVENT;
		event.user.data1 = 0;
		event.user.code = static_cast<int>(CustomEvent::GAMEENDED);
		SDL_PushEvent(&event);			
	}
	else if(winner)
	{
		SDL_Event event;
		SDL_zero(event);
		event.type = SDL_USEREVENT;
		if(currentPieceTexture == xTexture)
		{
			event.user.data1 = (void *)1;
		}
		else
		{
			event.user.data1 = (void *)2;
		}
		event.user.code = static_cast<int>(CustomEvent::GAMEENDED);
		SDL_PushEvent(&event);	
	}
}

void Board::loadTextures(SDL_Renderer *ren)
{
     xMouseover = new LTexture(ren,"../assets/mouseoverred.png"); 
     oMouseover = new LTexture(ren, "../assets/mouseoverblue.png");
     xTexture = new LTexture(ren, "../assets/xanimation.png");
     oTexture = new LTexture(ren, "../assets/circleanimation.png");
     boardHatchTexture = new LTexture(ren, "../assets/boardHatch.png");
}

void Board::freeTextures()
{
	delete xMouseover;
	delete oMouseover;
	delete xTexture;
	delete oTexture;
	delete boardHatchTexture;
	Mix_FreeChunk(xSound);
	Mix_FreeChunk(oSound);
}

void Board::makeAIMove()
{
	int slotToFill = ai.getAIMove(*aiPlayer, *humanPlayer, winStates,sizeof(winStates)/sizeof(*winStates));  	
	int row, col;
	row = slotToFill / BOARD_ROWS;
	col = slotToFill % BOARD_COLS;
	makeMove(row,col);
}
