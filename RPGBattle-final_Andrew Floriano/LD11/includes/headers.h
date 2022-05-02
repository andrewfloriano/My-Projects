//std and SDL headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include <string>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <sstream>

#include "debug.h"
using namespace std;

extern debugObj debug;
extern SDL_Event event;
extern SDL_Surface *screen;
extern SDL_Surface *camera;
extern SDL_Surface *text;
extern SDL_Surface *font;
extern SDL_Surface *gui;
extern SDL_Surface *textSurface;
extern SDL_Surface *background;

#ifndef ENUMS
#define ENUMS
enum actions {nothing, attack, atkMagic, heal, potion};

const int TOTAL_MONSTERS=2;

SDL_Surface * load_image(string filename);
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect * clip=NULL);
SDL_Surface* show_text(const char * strText);
#endif

extern Mix_Chunk * SE[6];
extern SDL_Surface *sprites[TOTAL_MONSTERS];
