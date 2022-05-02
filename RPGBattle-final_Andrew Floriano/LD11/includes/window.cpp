#include "window.h"

Window::Window(int w, int h, int bpp, std::string cap)
{
 	screen = SDL_SetVideoMode(w, h, bpp, SDL_SWSURFACE | SDL_RESIZABLE);

 	if(screen==NULL)
 	{
		error=true;
		return;
	} else {
		error=false;
	}
	SDL_WM_SetCaption(cap.c_str(), NULL);

	//general width, height values
	width=w;
	height=h;
	BPP=bpp;

	caption=cap;
	windowed=true;
	active=true;
	resized=false;

	//full screen values set to default
	full_width=w;
	full_height=h;
	full_BPP=32;
}

void Window::toggle_fullscreen()
{
 	if(windowed)
 	{
		//go full screen
	 	screen = SDL_SetVideoMode(full_width, full_height, full_BPP, SDL_SWSURFACE | SDL_RESIZABLE | SDL_FULLSCREEN);

	 	if(screen==NULL)
	 	{
			error=true;
			return;
		}

		windowed=false;
	} else {
	  	//set to window mode
	  	screen = SDL_SetVideoMode(width, height, BPP, SDL_SWSURFACE | SDL_RESIZABLE );

	  	if(screen==NULL)
	 	{
			error=true;
			return;
		}

		windowed=true;
	}
}

void Window::handle_events()
{
	resized=false;
    //If the window resized
    if(event.type == SDL_VIDEORESIZE)
    {
        width=event.resize.w;
        height=event.resize.h;
        //Resize the screen
        screen = SDL_SetVideoMode(event.resize.w, event.resize.h, 32, SDL_SWSURFACE | SDL_RESIZABLE);

        //If there's an error
        if(screen == NULL)
        {
            error=true;
            return;
        }
        resized=true;
    }
    //If the window focus changed
    if(event.type == SDL_ACTIVEEVENT)
    {
        //If the window was inconified or restored
        if(event.active.state & SDL_APPACTIVE)
        {
            //If the application is no longer active
            if(event.active.gain == 0)
            {
                active=false;
            } else {
                active=true;
            }
        }
    //If the window's screen has been altered
    } else if(event.type == SDL_VIDEOEXPOSE)
    {
        if(SDL_Flip(screen) == -1)
        {
            error = true;
            return;
        }
    }
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
 		{
			case SDLK_f:
				if(SDL_GetModState()&KMOD_SHIFT)
				{
					toggle_fullscreen();
				}
				break;
		}
	}
}

void Window::set_fullsize(int w, int h, int bpp)
{
 	full_width=w;
	full_height=h;
	full_BPP=bpp;
}

//pass value of true to reset the caption, otherwise, it's added to the base caption and displayed there
void Window::set_caption(std::string cap, bool reset=false)
{
	if(!reset)
	{
		cap=caption+cap;
	} else {
		caption=cap;
	}
 	SDL_WM_SetCaption(cap.c_str(), NULL);
}

bool Window::has_error()
{
 	 return error;
}

bool Window::is_active()
{
	return active;
}

bool Window::was_resized()
{
	return resized;
}

SDL_Rect Window::getSize()
{
	SDL_Rect ret;
	ret.x=0;
	ret.y=0;
	ret.w=width;
	ret.h=height;
	return ret;
}
