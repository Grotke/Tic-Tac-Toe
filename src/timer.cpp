#include <SDL2/SDL.h>
#include "timer.h"

Timer::Timer()
{
	startTime = 0;
	timePassed = 0;
	pingTimeStart = 0;
	timeToWait = 0;	
	started = false;
	paused = false;
}

Timer::~Timer()
{


}

void Timer::start()
{
	if(!started)
	{
	    startTime = SDL_GetTicks();
	    started = true;
	}
	else if(paused)
	{
		startTime = SDL_GetTicks() - timePassed;
		paused = false;
	}
}

unsigned int Timer::getTime()
{
	return SDL_GetTicks() - startTime;
}

void Timer::reset()
{
	startTime = 0;
	timePassed = 0;
	pingTimeStart = 0;
	timeToWait = 0;
	started = true;
	paused = false;
}

void Timer::pause()
{
	if(!paused)
	{
		timePassed = getTime();
		paused = true;
	}
}


void Timer::wait(unsigned int milliseconds)
{
	SDL_Delay(milliseconds);
}

void Timer::startPingTime(unsigned int milliseconds)
{	
	timeToWait = milliseconds;
	pingTimeStart = getTime();	
}

bool Timer::pingTime()
{
	unsigned int longEnough = false;
	if(getTime() - pingTimeStart >= timeToWait)
	{
		longEnough = true;
	}
	return longEnough;
}

bool Timer::isPingTimeSet()
{
	if(timeToWait != 0)
	{
		return true;
	}

	return false;

}
