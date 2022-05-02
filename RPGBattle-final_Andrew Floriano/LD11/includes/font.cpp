#include "headers.h"

SDL_Surface* show_text(const char * strText)
{
	Uint32 colorkey;
	
	unsigned int w, h, i, len;
	unsigned char chr;
	SDL_Surface * copyTo;
	copyTo=new SDL_Surface();
	SDL_Rect activeClip;
	h=26;
	len=strlen(strText);
	//width: 20 height: 26
	w=len*20;

	copyTo = SDL_CreateRGBSurface(SDL_HWSURFACE&SDL_SRCCOLORKEY,w,h,32,0,0,0,0);
	if(copyTo==NULL)
	{
		debug.ErrorOut("error on creating surface");
		return NULL;
	}
	
	SDL_FillRect(copyTo, NULL, SDL_MapRGB(copyTo->format, 0xFF, 0, 0xFF));
	colorkey = SDL_MapRGB(copyTo->format, 0xFF, 0, 0xFF);
   	SDL_SetColorKey(copyTo, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey);

	activeClip.x=0;
	activeClip.y=0;
	activeClip.h=h;
	activeClip.w=20;
	
	for(i=0; i<len; i++)
	{
		chr=strText[i];
		if(chr!=32)
		{
			activeClip.x=(chr-46)*20;
			if(chr==45)
			{
				activeClip.x=0;
			}
			apply_surface(i*20, 0, font, copyTo, &activeClip);
		}
	}
	return copyTo;
}
