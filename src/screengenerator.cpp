#include <SDL2/SDL.h>
#include "screen.h"
#include "button.h"
#include "screengenerator.h"
#include "customevents.h"

Screen & ScreenGenerator::createMainMenu(SDL_Renderer *ren)
{
    Screen *newScreen = new Screen();
    Button startButton = Button(250,300,BUTTON_WIDTH,BUTTON_HEIGHT,CustomEvent::GOTO_SELECTSCREEN);
    startButton.setTexturesIndivdual(ren,"../assets/startNormal.png","../assets/startMouseover.png","../assets/startClicked.png");   

    Button exitButton = Button(250,360,BUTTON_WIDTH,BUTTON_HEIGHT, CustomEvent::QUIT);
    exitButton.setTexturesIndivdual(ren,"../assets/exitNormal.png","../assets/exitMouseover.png","../assets/exitClicked.png");

    newScreen->addButton(startButton);
    newScreen->addButton(exitButton);

    SDL_Color color = {0x00,0x00,0x00,0xFF};
    SDL_Rect textDimensions = newScreen->addText(ren,"Tic-Tac-Toe", "../assets/frankfurt_hollow.ttf", color, 80);
   
    SDL_Rect destination = {0,50,textDimensions.w,textDimensions.h};
    newScreen->addTextRenderDestination(destination); 

    return *newScreen;
}

Screen & ScreenGenerator::createGameOver(SDL_Renderer *ren, void * winner)
{
	Screen *newScreen = new Screen();
	Button yesButton = Button(250,350,BUTTON_WIDTH,BUTTON_HEIGHT,CustomEvent::GAMERESTARTED);
	yesButton.setTexturesIndivdual(ren,"../assets/yesNormal.png","../assets/yesMouseover.png","../assets/yesClicked.png");

	Button noButton = Button(250,410,BUTTON_WIDTH,BUTTON_HEIGHT,CustomEvent::QUIT);
	noButton.setTexturesIndivdual(ren,"../assets/noNormal.png","../assets/noMouseover.png","../assets/noClicked.png");

	newScreen->addButton(yesButton);
	newScreen->addButton(noButton);
	newScreen->loadBackground(ren,"../assets/blackBackground.png");
	newScreen->setBackgroundAlpha(128);
	SDL_Color color = {0xFF,0xFF,0xFF,0xFF};
	std::string winningPhrase;
	if(winner == (void *)0)
	{
		winningPhrase = "Draw!";
	}
	else if(winner == (void *)1)
	{

		winningPhrase = "X Won!";
		color = {0xFF,0x00,0x00,0xFF};
	}
	else
	{
		color = {0x00,0x00,0xFF,0xFF};
		winningPhrase = "O Won!";
	}
	SDL_Rect winTextDimensions = newScreen->addText(ren,winningPhrase,"../assets/frankfurt_hollow.ttf", color, 80);
	color = {0xFF,0xFF,0xFF,0xFF};
	SDL_Rect textDimensions = newScreen->addText(ren,"Play Again?", "../assets/frankfurt_hollow.ttf", color, 80);
	SDL_Rect winDestination = {600/2 - winTextDimensions.w/2,50,winTextDimensions.w,winTextDimensions.h};
	SDL_Rect destination = {0, winTextDimensions.h + 60, textDimensions.w, textDimensions.h};
	newScreen->addTextRenderDestination(winDestination);
	newScreen->addTextRenderDestination(destination);
	return *newScreen;    

}

Screen & ScreenGenerator::createSelectScreen(SDL_Renderer *ren)
{
	Screen *newScreen = new Screen();
    SDL_Color color = {0x00,0x00,0x00,0xFF};
    SDL_Rect textDimensions = newScreen->addText(ren,"X or O?", "../assets/frankfurt_hollow.ttf", color, 80);
     
    SDL_Rect destination = {600/2 - textDimensions.w/2,50,textDimensions.w,textDimensions.h};
    newScreen->addTextRenderDestination(destination); 
	
	SDL_Rect source = {3*200,0,200,160};
	Button xButton = Button(600/2 - textDimensions.w/2,textDimensions.h + 50 + 100,source,"../assets/xanimation.png","../assets/mouseoverred.png",CustomEvent::X_SELECTED,ren);
	Button oButton = Button(600/2 - textDimensions.w/2 + 220,textDimensions.h+50 + 100,source,"../assets/circleanimation.png","../assets/mouseoverblue.png",CustomEvent::O_SELECTED,ren);
	Button backButton = Button(10,470 - BUTTON_HEIGHT,BUTTON_WIDTH,BUTTON_HEIGHT,CustomEvent::GOTO_MAINMENU);
	backButton.setTexturesIndivdual(ren,"../assets/backNormal.png","../assets/backMouseover.png","../assets/backClicked.png");
	newScreen->addButton(xButton);	
	newScreen->addButton(oButton);
	newScreen->addButton(backButton);

	return *newScreen;
}
