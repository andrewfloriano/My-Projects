#include "includes/headers.h"
using namespace std;

debugObj debug;
SDL_Event event;

SDL_Surface *screen = NULL;
SDL_Surface *camera = NULL;
SDL_Surface *text = NULL;
//
SDL_Surface *font = NULL;
SDL_Surface *gui = NULL;
SDL_Surface *textSurface = NULL;
SDL_Surface *background = NULL;
SDL_Surface *sprites[TOTAL_MONSTERS];

Mix_Chunk * SE[6];

//custom header files go here
#include "includes/timer.h"
#include "includes/window.h"
#include "includes/gameObj.hpp"

//constants
const int FRAMES_PER_SECOND=30;

void clean_up();
bool init();
bool load_files();

int main(int argc, char* args[])
{
    debug.setState(false);
    for(int i=1; i<argc; i++)
    {
	    if(strcmp(args[i], "-debug:on")==0)
	  	{
	    	debug.setState(true);
		}
	}
	//make sure numbers are random
    srand(time(0));
    
    //general variables
	bool quit = false;
	bool update = true;
	
	//framerate variables
	bool capfps=true;
	Timer fps;

    //Intialize things
    if(!init())
    {
		debug.ErrorOut("With init");
        return 1;
    }
    int wWidth, wHeight;
    wWidth=640;
    wHeight=480;
   
	Window wMain(wWidth, wHeight, 32, "Minimal Battle Simulation");
	text = SDL_CreateRGBSurface(SDL_HWSURFACE&SDL_SRCCOLORKEY,wWidth,130,32,0,0,0,0);
    SDL_SetColorKey(text, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB(text->format, 0xFF, 0, 0xFF));
	
	camera = SDL_CreateRGBSurface(SDL_HWSURFACE&SDL_SRCCOLORKEY,wWidth,wHeight,32,0,0,0,0);
    SDL_SetColorKey(camera, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB(camera->format, 0xFF, 0, 0xFF));

    if(!load_files())
    {
		debug.ErrorOut("loading files");
		return 1;
	}
	
	Game * currentGame;
	currentGame=currentGame->Instance();
	
    debug.Msg("main loop");

    //While the user hasn't quit
    while(!quit)
    {
		//debug.Msg("main loop");
        fps.start();

        //event handling
		if(SDL_PollEvent(&event))
        {
        	currentGame->handle_events(quit);
		 	wMain.handle_events();
		}

		if(!quit)
		{
			bool lose=false;
	        //logic
    	    update=currentGame->logic(lose);
    	    if(lose)
    	    {
				SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
				currentGame->reset();
			}
		}
        
        //UPDATE SCREEN
		if((update) && (wMain.is_active()))
		{
			SDL_FillRect(camera, NULL, SDL_MapRGB(text->format, 0xFF, 0x00, 0xFF));
			currentGame->show();

	        //Update the screen
    	    if(SDL_Flip(screen) == -1)
			{
				debug.ErrorOut("Updating screen");
            	quit=true;
	        }
	        update=false;
		}
		//CAP FPS
		if((capfps == true) && (fps.get_time()<1000/FRAMES_PER_SECOND))
        {
            SDL_Delay((1000/FRAMES_PER_SECOND)-fps.get_time());
        }
        
        if(wMain.has_error())
        {
			debug.ErrorOut("Window Error, quitting");
			quit=true;
		}
	}
	
	delete currentGame;
	
    clean_up();
    
    return 0;
}

//cleans up when the program is closed
void clean_up()
{
    SDL_FreeSurface(screen);
    SDL_FreeSurface(camera);
    SDL_FreeSurface(text);
    SDL_FreeSurface(font);
    SDL_FreeSurface(textSurface);

	for(int i=0; i<TOTAL_MONSTERS; i++)
	{
		SDL_FreeSurface(sprites[i]);
	}

	for(int i=0; i<6; i++)
	{
		Mix_FreeChunk(SE[i]);
		SE[i]=NULL;
	}
    
    Mix_CloseAudio();
    
    SDL_Quit();
}

bool init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
		debug.ErrorOut("SDL Initilization failed");
        return false;
    }
    
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		debug.ErrorOut("Sound and music failed to intilize");
	}
	
    return true;
}

bool load_files()
{

    font = load_image("resources\\images\\text.png");

    //If there was an error in loading the image
    if(font == NULL)
    {
		debug.ErrorOut("Loading Image");
        return false;
    }
    
    gui = load_image("resources\\images\\screen.png");

    //If there was an error in loading the image
    if(gui == NULL)
    {
		debug.ErrorOut("Loading Image");
        return false;
    }
    
    background = load_image("resources\\images\\background.png");

    //If there was an error in loading the image
    if(background == NULL)
    {
		debug.ErrorOut("Loading Image");
        return false;
    }

	for(int i=0; i<TOTAL_MONSTERS; i++)
	{
		sprites[i] = NULL;
	}
	sprites[0] = load_image("resources\\images\\monsters\\slime.png");
	sprites[1] = load_image("resources\\images\\monsters\\bat.png");
	//sprites[0] = load_image("resources\\images\\monsters\\slime.png");
//	sprites[0] = load_image("resources\\images\\monsters\\slime.png");
	//sprites[0] = load_image("resources\\images\\monsters\\slime.png");

	SE[0]=Mix_LoadWAV("resources\\sound\\attack.wav");
	if(SE[0] == NULL)
    {
		debug.ErrorOut("Loading attack.wav: Check Filenames");
    }
	SE[1]=Mix_LoadWAV("resources\\sound\\attack2.wav");
	SE[2]=Mix_LoadWAV("resources\\sound\\magicA.wav");
	SE[3]=Mix_LoadWAV("resources\\sound\\magicB.wav");
	SE[4]=Mix_LoadWAV("resources\\sound\\win.wav");
	SE[5]=Mix_LoadWAV("resources\\sound\\monsterDeath.wav");

    return true;
}

SDL_Surface * load_image(string filename)
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load(filename.c_str());

    if(loadedImage != NULL)
    {
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);

        if(optimizedImage != NULL)
        {
            Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0xFF, 0, 0xFF);
            SDL_SetColorKey(optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey);
        }	else {
			puts("Image not optimized");
		}
    } else {
		puts("image didn't load:");
		puts(filename.c_str());
		puts(SDL_GetError());
	}

    return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect * clip)
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(source, clip, destination, &offset);
}
