#ifndef TIMER_H
#define TIMER_H

#include "headers.h"
//Timer Class
class Timer
{
    private:
	    int startTicks;
	    int pausedTicks;

	    bool active;
	    bool paused;
    
    public:
	    Timer();

	    //The various clock actions
	    void start();
	    void stop();
	    void pause();
	    void unpause();
	    void reset();

	    int get_time();
	    bool is_active();
	    bool is_paused();
};
#endif
