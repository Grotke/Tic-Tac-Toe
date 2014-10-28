#include <SDL2/SDL.h>
#include <iostream>
#include "timer.h"
#include "ltexture.h"
#include "board.h"

Board::Board(SDL_Renderer *ren)
{
	winner = false;
	draw = false;
	oMap = 0;
	xMap = 0;
	winningState = -1;
	renderWinning = true;
	timer = Timer();
	locked = false;
	timer.start();
	loadTextures(ren);
        constructBoard(CELL_WIDTH,CELL_HEIGHT);
        constructAnimationFrames(CELL_WIDTH,CELL_HEIGHT);
  	currentMouseoverTexture = xMouseover;
    	currentPieceTexture = xTexture;
    	currentMap = &xMap;
}

Board::~Board()
{
	freeTextures();	

}

void Board::renderBoard(SDL_Renderer *ren)
{
	for(int i = 0; i < BOARD_ROWS; i++)
	{
		for(int j = 0; j < BOARD_COLS; j++)
		{ 
	            SDL_RenderSetViewport(ren, &board[i][j]);
		    if(winningState != -1 && ((winStates[winningState] >> (i*BOARD_ROWS+j)) & 0x1))
		    {	if(!timer.isPingTimeSet())
			{
				timer.startPingTime(300);
			}
			if(timer.pingTime())
			{
				renderWinning = !renderWinning;
				timer.startPingTime(300);	
			}
			if(renderWinning)
			{
				clickState[i][j]->render(ren,&spriteClips[frame[i][j]/10],nullptr);
			}
			
		    }
		    else if(clickState[i][j] != nullptr)
		    {
			clickState[i][j]->render(ren,&spriteClips[frame[i][j]/10],nullptr);
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
}

void Board::handleEvent(SDL_Event *e)
{
	if(!locked)
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
					clickState[i][j] = currentPieceTexture;
					*currentMap = (*currentMap) | (0x1 << (i*BOARD_ROWS + j));
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
		}
	

  	   }
	}
}

bool Board::insideBox(SDL_Rect *box)
{
    bool inside = true;
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if(mouseX < box->x
       || mouseX > box->x + box->w
       || mouseY < box->y
       || mouseY > box->y + box->h)
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
	}
	else
	{
		currentMouseoverTexture = xMouseover;
		currentPieceTexture = xTexture;
		currentMap = &xMap;
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
		std::cout << "Draw! Nobody wins." << std::endl;
	}
	else if(winner)
	{
		char win;
		if(currentPieceTexture == xTexture)
		{
			win = 'X';
		}
		else{
			win = 'O';
		}
		
		std::cout << win << " wins!" << std::endl;
	}	
}

void Board::loadTextures(SDL_Renderer *ren)
{
     xMouseover = new LTexture(ren,"../assets/mouseoverred.png"); 
     oMouseover = new LTexture(ren, "../assets/mouseoverblue.png");
     xTexture = new LTexture(ren, "../assets/xanimation.png");
     oTexture = new LTexture(ren, "../assets/circleanimation.png");
}

void Board::freeTextures()
{
	delete xMouseover;
	delete oMouseover;
	delete xTexture;
	delete oTexture;
}
