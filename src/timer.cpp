#include <SDL2/SDL.h>
#include <iostream>
#include "timer.h"

Timer::Timer()
{
	startTime = 0;
	timePassed = 0;
	initializePings();	
	started = false;
	paused = false;
}

Timer::~Timer()
{


}

void Timer::initializePings()
{
	pingsAllocated = 0;
	for(int i = 0; i < MAX_PINGS; i++)
	{	
		isPingAllocated[i] = false;
		timeToWait[i] = 0;
		pingTimeStart[i] = 0;
	}
	isPingAllocated[0] = true;
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
	startTime = SDL_GetTicks();
	timePassed = 0;
	initializePings();
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

void Timer::startPingTime(unsigned int milliseconds, int pingNumber)
{	
	if(validPingNumber(pingNumber))
	{
		timeToWait[pingNumber] = milliseconds;
		pingTimeStart[pingNumber] = getTime();
	}	
}

bool Timer::pingTime(int pingNumber)
{
	unsigned int longEnough = false;
	if(validPingNumber(pingNumber))
	{
		if(getTime() - pingTimeStart[pingNumber] >= timeToWait[pingNumber])
		{
			longEnough = true;
		}
	}
	return longEnough;
}

bool Timer::isPingTimeSet(int pingNumber)
{
	if(validPingNumber(pingNumber))
	{
		if(timeToWait[pingNumber] != 0)
		{
			return true;
		}
	}

	return false;
}

bool Timer::validPingNumber(int pingNumber)
{
	return pingNumber > 0 && pingNumber <= pingsAllocated;
}

int Timer::registerPingNumber()
{
	if(pingsAllocated < MAX_PINGS -1)
	{
		for(int i = 1; i < MAX_PINGS; i++)
		{
			if(!isPingAllocated[i])
			{
				isPingAllocated[i] = true;
				pingsAllocated++;
				return i;
			}
		}		
	}
	
	return 0;
}

void Timer::releasePingNumber(int pingNumber)
{
	if(validPingNumber(pingNumber))
	{
		pingsAllocated--;
		isPingAllocated[pingNumber] = false;
		timeToWait[pingNumber] = 0;
		pingTimeStart[pingNumber] = 0;
	}
}

void Timer::clearPingTime(int pingNumber)
{
	if(validPingNumber(pingNumber))
	{
		timeToWait[pingNumber] = 0;
		pingTimeStart[pingNumber] = 0;
	}
}
