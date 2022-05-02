#include "timer.h"

Timer::Timer()
{
	startTicks=0;
	pausedTicks=0;
	active=false;
	paused=false;
}

void Timer::start()
{
	startTicks=SDL_GetTicks();
	active=true;
	paused=false;
}

void Timer::stop()
{
	active=false;
	paused=false;
}


void Timer::pause()
{
    if((active == true)&&(paused == false))
    {
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    if( paused == true )
    {
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

void Timer::reset()
{
	pausedTicks=0;
	startTicks=0;
}

int Timer::get_time()
{
	if( active == true ) {
	//If the timer is paused
		if( paused == true ) {
			//Return the number of ticks when the the timer was paused
			return pausedTicks;
		} else {
			//Return the current time minus the start time
			return SDL_GetTicks() - startTicks;
		}
	}
	//If the timer isn't running
	return 0;
}

bool Timer::is_active()
{
	return active;
}

bool Timer::is_paused()
{
	return paused;
}
