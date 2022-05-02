#ifndef WINDOW_H
#define WINDOW_H

#include "headers.h"
#include <sstream>
//using namespace std;

//window controls
class Window
{
 	  private:
	  	   	  bool windowed, error, active, resized;
		  	  //windowed variables
		  	  int width, height, BPP;
		  	  //full screen variables
		  	  int full_width, full_height, full_BPP;
		  	  
		  	  string caption;
 	  
 	  public:
	  		 Window(int w, int h, int bpp, string cap);
	  		 
	  		 void toggle_fullscreen();
	  		 void handle_events();
	  		 
	  		 void set_fullsize(int w, int h, int bpp);
	  		 void set_caption(string cap, bool reset);
	  		 
	  		 bool has_error();
	  		 bool is_active();
	  		 bool was_resized();
	  		 SDL_Rect getSize();
};

#endif
